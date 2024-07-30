import socket

serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

serverAddress = ('localhost', 9876)
serverSocket.bind(serverAddress)

serverSocket.listen(1)
print(f"Server is listening on {serverAddress[0]}:{serverAddress[1]}")

clientSocket, clientAddress = serverSocket.accept()
print(f"Accepted connection from {clientAddress[0]}:{clientAddress[1]}")

# Get the username from the client
username = clientSocket.recv(1024).decode('utf-8')
print(f"Client's username is {username}.")

while True:
    clientData = clientSocket.recv(1024).decode('utf-8')
    if not clientData:
        break
    
    print(f"{username}: {clientData}")

    serverResponse = input("Server: ")
    if serverResponse == ":quit":
        break
    clientSocket.send(serverResponse.encode('utf-8'))

clientSocket.close()
serverSocket.close()
