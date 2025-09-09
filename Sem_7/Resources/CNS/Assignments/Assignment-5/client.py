import socket
import sys
import threading
import random

# DH Parameters
g = 5
p = 23

if len(sys.argv) != 3:
    sys.exit(1)

serverIP = sys.argv[1]
serverPort = int(sys.argv[2])

clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serverSocket = (serverIP, serverPort)

clientSocket.connect(serverSocket)

username = input("Username: ")
clientSocket.send(username.encode('utf-8'))

# DH Key Exchange
private_key = random.randint(1, 100)
public_key = (g ** private_key) % p
clientSocket.send(str(public_key).encode('utf-8'))
server_public_key = int(clientSocket.recv(1024).decode('utf-8'))
shared_key = (server_public_key ** private_key) % p
print(f"DH Shared Key with server: {shared_key}")

def encrypt(txt, key):
    return ''.join(chr(ord(c) ^ key) for c in txt)

def decrypt(txt, key):
    return ''.join(chr(ord(c) ^ key) for c in txt)

def receive_input():
    while True:
        serverResponse = clientSocket.recv(1024).decode('utf-8')
        decrypted_message = decrypt(serverResponse, shared_key)
        print(f"Server: {decrypted_message}")

receive_thread = threading.Thread(target=receive_input)
receive_thread.start()

while True:
    userInput = input()
    if userInput == ":quit":
        clientSocket.close()
        exit()
    
    encrypted_message = encrypt(userInput, shared_key)
    clientSocket.send(encrypted_message.encode('utf-8'))
