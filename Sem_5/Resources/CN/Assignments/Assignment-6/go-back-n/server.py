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

data=["A","B","C","D","E","F","G","H","I","J"]
# With Flow Control using Stop and Wait and Pipelining
# Window Size = 3
start=0
end=3
window=data[start:end]

index=0
clientSocket.send(data[index].encode('utf-8'))
index+=1
clientSocket.send(data[index].encode('utf-8'))
index+=1
clientSocket.send(data[index].encode('utf-8'))
print(f"Window: {window}")

start+=3
end+=3
window=data[start:end]

os,oe=start,end
index=0
while True:
    clientData = clientSocket.recv(1024).decode('utf-8')
    if not clientData:
        break
    
    print(f"{username}: {clientData}")
    if clientData=="CorruptReceived!":
        start=os
        end=oe
        index=start
        window=data[start:end]
        print("Resending Window...")

    if window:
        serverResponse = window[0]
        clientSocket.send(serverResponse.encode('utf-8'))
    else:
        serverResponse = "End"
        clientSocket.send(serverResponse.encode('utf-8'))
        break
    
    start+=1
    end+=1
    index+=1
    window=data[start:end]
    print(f"Window: {window}")

    # Update os and oe
    if index==os+3:
        os,oe=start,end


clientSocket.close()
serverSocket.close()
