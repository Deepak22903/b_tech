import numpy as np
import torch
from transformers import BertTokenizer, BertForSequenceClassification, AdamW
from sklearn.model_selection import train_test_split
import json

# Load intents data from JSON file
with open('intents2.json', 'r') as file:
    intents_data = json.load(file)['intents']

# Extract patterns and tags from intents data
patterns = []
tags = []
for intent in intents_data:
    for pattern in intent['patterns']:
        patterns.append(pattern)
        tags.append(intent['tag'])

# Split data into train and test sets
X_train, X_test, y_train, y_test = train_test_split(patterns, tags, test_size=0.2, random_state=42)

# Load the BERT tokenizer
tokenizer = BertTokenizer.from_pretrained('bert-base-uncased')

# Tokenize input data
def tokenize_data(texts, labels):
    input_ids = []
    attention_masks = []

    # Create a dictionary to map unique labels to numerical values
    label_map = {label: idx for idx, label in enumerate(set(labels))}

    # Convert labels to numerical values using the label map
    encoded_labels = [label_map[label] for label in labels]

    for text in texts:
        encoded_dict = tokenizer.encode_plus(
                            text,
                            add_special_tokens = True,
                            max_length = 64,
                            padding = 'max_length',
                            truncation = True,
                            return_attention_mask = True,
                            return_tensors = 'pt'
                       )

        input_ids.append(encoded_dict['input_ids'])
        attention_masks.append(encoded_dict['attention_mask'])

    input_ids = torch.cat(input_ids, dim=0)
    attention_masks = torch.cat(attention_masks, dim=0)
    labels_tensor = torch.tensor(encoded_labels)

    return input_ids, attention_masks, labels_tensor


# Tokenize training and testing data
train_input_ids, train_attention_masks, train_labels = tokenize_data(X_train, y_train)
test_input_ids, test_attention_masks, test_labels = tokenize_data(X_test, y_test)

# Load pre-trained BERT model for sequence classification
model = BertForSequenceClassification.from_pretrained(
    'bert-base-uncased', 
    num_labels=len(set(tags)), 
    output_attentions=False,
    output_hidden_states=False
)

# Set device to GPU if available
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
model.to(device)

# Define optimizer and learning rate scheduler
optimizer = AdamW(model.parameters(), lr=2e-5, eps=1e-8)

# Define batch size and epochs
batch_size = 32
epochs = 3

# Train the model
for epoch in range(epochs):
    model.train()
    for i in range(0, len(train_input_ids), batch_size):
        inputs = train_input_ids[i:i+batch_size].to(device)
        masks = train_attention_masks[i:i+batch_size].to(device)
        labels = train_labels[i:i+batch_size].to(device)

        optimizer.zero_grad()        
        outputs = model(inputs, attention_mask=masks, labels=labels)
        loss = outputs.loss
        loss.backward()
        optimizer.step()

# Evaluate the model on the test set
model.eval()
with torch.no_grad():
    test_inputs = test_input_ids.to(device)
    test_masks = test_attention_masks.to(device)
    test_labels = test_labels.to(device)

    test_outputs = model(test_inputs, attention_mask=test_masks, labels=test_labels)
    test_loss = test_outputs.loss
    test_preds = np.argmax(test_outputs.logits.detach().cpu().numpy(), axis=1)

    # Calculate accuracy
    test_accuracy = np.mean(test_preds == test_labels.cpu().numpy())
    print(f'Test Accuracy: {test_accuracy}')

# Save the trained model
model_path = 'bert_chatbot_model.pth'
torch.save(model.state_dict(), model_path)

# Testing code
def predict_intent(text):
    model.eval()
    with torch.no_grad():
        inputs = tokenizer.encode_plus(
            text,
            add_special_tokens=True,
            max_length=64,
            padding='max_length',
            truncation=True,
            return_tensors='pt'
        )

        inputs = {key: val.to(device) for key, val in inputs.items()}
        outputs = model(**inputs)
        logits = outputs.logits
        predicted_class = torch.argmax(logits, dim=1).item()
        predicted_intent = list(set(tags))[predicted_class]

        return predicted_intent

# Example usage
question = "Hi there, how can I help you today?"
predicted_intent = predict_intent(question)
print(f'Predicted intent: {predicted_intent}')
