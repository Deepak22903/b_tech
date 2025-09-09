import numpy as np
import sympy
import string
import random

dimension = 3
key = np.matrix([[17, 17, 5], [21, 18, 21], [2, 2, 19]])
message = input("Enter plaintext: ")

alphabet = string.ascii_lowercase

encryptedMessage = ""

for index, i in enumerate(message):
    values = []
    if index % dimension == 0:
        for j in range(0, dimension):
            if(index + j < len(message)):
                values.append([alphabet.index(message[index + j])])
            else:
                values.append([random.randint(0, 25)])
        vector = np.matrix(values)
        vector = key * vector
        vector %= 26
        for j in range(0, dimension):
            encryptedMessage += alphabet[vector.item(j)]

print("\nCiphertext: " + encryptedMessage)


def modulo_multiplicative_inverse(A, M):
    for i in range(0, M):
        if (A*i) % M == 1:
            return i
    return -1


encryptedMessage = input("\nEnter ciphertext: ")

matrix = sympy.Matrix([[17, 17, 5], [21, 18, 21], [2, 2, 19]])
adj = (matrix.adjugate() % 26)
mat = np.matrix([[17, 17, 5], [21, 18, 21], [2, 2, 19]])
det = (round(np.linalg.det(mat)) % 26)
mult_inverse = modulo_multiplicative_inverse(det, 26)
inv_m = (mult_inverse*adj) % 26

decryptedMessage = ""

for index, i in enumerate(encryptedMessage):
    values = []
    if index % dimension == 0:
        for j in range(0, dimension):
            if(index + j < len(encryptedMessage)):
                values.append([alphabet.index(encryptedMessage[index + j])])
            else:
                values.append([random.randint(0, 25)])
        vector = np.matrix(values)
        vector = inv_m * vector
        vector %= 26
        for j in range(0, dimension):
            decryptedMessage += alphabet[vector[j]]

print("\nPlaintext: " + decryptedMessage[:])
