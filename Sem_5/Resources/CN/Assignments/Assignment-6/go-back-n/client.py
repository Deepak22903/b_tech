import socket
import sys

if len(sys.argv) != 3:
    sys.exit(1)

serverIP = sys.argv[1]
serverPort = int(sys.argv[2])

clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

serverSocket = (serverIP, serverPort)
clientSocket.connect(serverSocket)

username = input("Username: ")
clientSocket.send(username.encode('utf-8'))
c=0

while True:

    clientSocket.send("Received!".encode('utf-8'))
    serverResponse = clientSocket.recv(1024).decode('utf-8')

    if c==4:
        print("Corrupted data sent")
        clientSocket.send("Corrupt".encode('utf-8'))
        c+=1
        continue
    c+=1
    print(f"Server: {serverResponse}")

clientSocket.close()
