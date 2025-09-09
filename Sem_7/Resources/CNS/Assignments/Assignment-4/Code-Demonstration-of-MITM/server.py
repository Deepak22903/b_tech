import socket
import threading

serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serverAddress = ('localhost', 9876)
serverSocket.bind(serverAddress)
serverSocket.listen(5)
print(f"Server is listening on {serverAddress[0]}:{serverAddress[1]}")

clients = {}
clients_lock = threading.Lock()


def encrypt(txt):
    lst=[]
    for i in txt:
        v=(bin(ord(i))[2:])+'1'
        nz=8-len(v)
        v="0"*nz+v
        lst.append(v)
    a="".join(lst)
    a=a[13:]+a[:13]
    return a


def decrypt(txt):
    txt=txt[-13:]+txt[:-13]
    lst= [txt[i:i+8] for i in range(0, len(txt), 8)]
    decrypted=""
    for i in lst:
        decrypted+=chr(int(i[:-1],2))
    return decrypted


def broadcast(message, sender_name):
    with clients_lock:
        for name, client_socket in clients.items():
            if name != sender_name:
                try:
                    client_socket.send(message)
                except:
                    client_socket.close()
                    del clients[name]

def handle_client(client_socket, client_name):
    try:
        while True:
            message = client_socket.recv(1024)
            if message:
                broadcast_message = f"{client_name}: {message.decode('utf-8')}"
                print(broadcast_message)
                broadcast(broadcast_message.encode('utf-8'), client_name)
            else:
                break
    except Exception as e:
        print(f"Error: {str(e)}")
    finally:
        with clients_lock:
            del clients[client_name]
        leave_message = f"{client_name} has left the chat."
        print(leave_message)
        broadcast(leave_message.encode('utf-8'), client_name)
        client_socket.close()

def send_message():
    while True:
        message = input()
        if message:
            if message == ":quit":
                with clients_lock:
                    for name, client_socket in clients.items():
                        client_socket.close()
                serverSocket.close()
                exit()
            elif message == ":show":
                print(clients)
            elif message == ":kick":
                kick = input("Who do you want to kick? ")
                with clients_lock:
                    if kick in clients:
                        clients[kick].close()
                        del clients[kick]
                        print(f"{kick} has been kicked.")
                    else:
                        print(f"{kick} is not in the chat.")
            else:
                broadcast(("Server: " + encrypt(message)).encode('utf-8'), "Server")

send_thread = threading.Thread(target=send_message)
send_thread.start()

while True:
    try:
        clientSocket, clientAddress = serverSocket.accept()
        print(f"Accepted connection from {clientAddress[0]}:{clientAddress[1]}")

        username = clientSocket.recv(1024).decode('utf-8')
        print(f"Client's username is {username}.")

        with clients_lock:
            clients[username] = clientSocket

        join_message = f"{username} has joined the chat."
        print(join_message)
        broadcast(join_message.encode('utf-8'), username)

        client_handler = threading.Thread(target=handle_client, args=(clientSocket, username))
        client_handler.start()

    except Exception as e:
        print(f"Error: {str(e)}")
