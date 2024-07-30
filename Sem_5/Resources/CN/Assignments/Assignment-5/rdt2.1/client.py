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

while True:
    serverResponse = clientSocket.recv(1024).decode('utf-8')
    msg = serverResponse.split("] ")

    packNo = serverResponse.split("]")
    packNo = packNo[0][1:]

    checkSum = msg[1][1:]
    checkSum = int(checkSum)

    # Check if data is corrupted
    checksum = 0
    for i in msg[2]:
        checksum += ord(i)
    checksum = checksum % 256
    if checksum != checkSum:
        print("Data is corrupted!")
        msg=f"[{str(packNo)}] : NACK"
        clientSocket.send(msg.encode('utf-8'))
    else:
        msg = msg[2]
        print(f"Server: {msg}")

        msg = f"Received by!"
        clientSocket.send(msg.encode('utf-8'))

clientSocket.close()
