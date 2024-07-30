import os
import cv2
import numpy as np
import tensorflow as tf
from tensorflow.keras import layers, models

# Function to load and preprocess images
def load_images(folder_path):
    images = []
    labels = []
    class_labels = os.listdir(folder_path)
    for class_label in class_labels:
        class_path = os.path.join(folder_path, class_label)
        if os.path.isdir(class_path):
            for image_name in os.listdir(class_path):
                image_path = os.path.join(class_path, image_name)
                image = cv2.imread(image_path)
                # Preprocess your images as needed (resize, normalize, etc.)
                # Add the processed image to the list
                images.append(image)
                # Add the corresponding label (class index) to the labels list
                labels.append(class_labels.index(class_label))
    return np.array(images), np.array(labels)

# Load and preprocess original images
original_images, original_labels = load_images("Photoss")

# Load and preprocess detected faces
face_images, face_labels = load_images("detected_faces")

# Create a basic CNN model
model = models.Sequential([
    layers.Conv2D(32, (3, 3), activation='relu', input_shape=(height, width, channels)),
    layers.MaxPooling2D((2, 2)),
    layers.Conv2D(64, (3, 3), activation='relu'),
    layers.MaxPooling2D((2, 2)),
    layers.Flatten(),
    layers.Dense(64, activation='relu'),
    layers.Dense(num_classes, activation='softmax')
])

# Compile the model
model.compile(optimizer='adam',
              loss='sparse_categorical_crossentropy',
              metrics=['accuracy'])

# Train the model on original images
model.fit(original_images, original_labels, epochs=10, validation_split=0.2)

# Evaluate the model on face images
test_loss, test_acc = model.evaluate(face_images, face_labels)
print(f"Test accuracy on detected faces: {test_acc}")

