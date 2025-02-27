import random 
import json
import pickle
import numpy as np

import nltk
from nltk.stem import WordNetLemmatizer

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense,Activation,Dropout
from tensorflow.keras.optimizers import SGD

lematizer = WordNetLemmatizer()

intents = json.loads(open('intents2.json').read())

words = []
classes = []
documents = []
ignore_letters = ['?','!','.',',']

for intent in intents['intents']:
    for pattern in intent['patterns']:
        word_list = nltk.word_tokenize(pattern)
        words.extend(word_list) #words.append(word_list)
        intent['tag'] = intent['tag'].replace(' ', "_")
        documents.append((word_list,intent['tag']))

        if intent['tag'] not in classes:
            classes.append(intent['tag'])


words = [lematizer.lemmatize(word) for word in words if word not in ignore_letters]
words = sorted(set(words))

classes = sorted(set(classes))

pickle.dump(words, open('words.pk','wb'))
pickle.dump(classes, open('classes.pk','wb'))

training_bag = []
training_output_row = []
output_empty = [0] * len(classes)

for document in documents:
   bag = []
   word_patterns = document[0]
   word_patterns = [lematizer.lemmatize(word.lower()) for word in word_patterns]
   for word in words:
      bag.append(1) if word in word_patterns else bag.append(0)

      output_row = list(output_empty)
      output_row[classes.index(document[1])] = 1
      training_bag.append(bag)
      training_output_row.append(output_row)
  
training_bag = np.array(training_bag)
training_output_row = np.array(training_output_row)

from sklearn.utils import shuffle
train_x, train_y = shuffle(training_bag, training_output_row, random_state=0)

print("========================================================================================================")
print(train_x.shape)

model = Sequential()
model.add(Dense(128,input_shape=(len(train_x[0]),), activation='relu'))
model.add(Dropout(0.5))
model.add(Dense(64, activation='relu'))
model.add(Dropout(0.5))
model.add(Dense(len(train_y[0]), activation='softmax'))

sgd = SGD(momentum=0.9,nesterov=True)
model.compile(loss='categorical_crossentropy',optimizer=sgd,metrics=['accuracy'])

#model.fit(np.array(train_x),np.array(train_y),epochs=200,batch_size=5,verbose=1)
#model.save(r'C:\Users\Asus\Documents\Python_Projects\AI_chatbot\chatbot_model.model')
hist = model.fit(np.array(train_x),np.array(train_y),epochs=200,batch_size=5,verbose=1)
model.save(r'chatbotmodel.h5',hist)
print('Done')
