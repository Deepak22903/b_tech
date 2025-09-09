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

key = 42

def encrypt(txt, key):
    lst = []
    for i in txt:
        # XOR the character with the key and convert to binary
        v = bin(ord(i) ^ key)[2:] + '1'
        nz = 8 - len(v)
        v = "0" * nz + v
        lst.append(v)
    a = "".join(lst)
    # Perform circular shift by 13
    a = a[13:] + a[:13]
    return a

def decrypt(txt, key):
    # Reverse the circular shift by 13
    txt = txt[-13:] + txt[:-13]
    lst = [txt[i:i+8] for i in range(0, len(txt), 8)]
    decrypted = ""
    for i in lst:
        # XOR the decoded binary character with the key
        decrypted += chr(int(i[:-1], 2) ^ key)
    return decrypted

def receive_input():
    while True:
        serverResponse = clientSocket.recv(1024).decode('utf-8')
        temp=serverResponse.split(': ')
        decrypted_message=decrypt(temp[1], key)
        print(f"{temp[0]}: {decrypted_message}")

receive_thread = threading.Thread(target=receive_input)
receive_thread.start()

while True:
    userInput = input()
    if userInput == ":quit":
        clientSocket.close()
        receive_input.close()
        exit()
    
    clientSocket.send(userInput.encode('utf-8'))

