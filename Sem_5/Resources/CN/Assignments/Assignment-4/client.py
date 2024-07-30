import socket
import sys
import threading

if len(sys.argv) != 3:
    sys.exit(1)

serverIP = sys.argv[1]
serverPort = int(sys.argv[2])

clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serverSocket = (serverIP, serverPort)

clientSocket.connect(serverSocket)

username = input("Username: ")
clientSocket.send(username.encode('utf-8'))

def receive_input():
    while True:
        serverResponse = clientSocket.recv(1024).decode('utf-8')
        print(f"{serverResponse}")

receive_thread = threading.Thread(target=receive_input)
receive_thread.start()

while True:
    userInput = input()
    if userInput == ":quit":
        clientSocket.close()
        receive_input.close()
        exit()
    
    clientSocket.send(userInput.encode('utf-8'))

