import socket
import threading
import random

# DH Parameters
g = 5
p = 23

serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serverAddress = ('localhost', 9876)
serverSocket.bind(serverAddress)
serverSocket.listen(5)
print(f"Server is listening on {serverAddress[0]}:{serverAddress[1]}")

clients = {}
shared_keys = {}
clients_lock = threading.Lock()

def encrypt(txt, key):
    return ''.join(chr(ord(c) ^ key) for c in txt)

def decrypt(txt, key):
    return ''.join(chr(ord(c) ^ key) for c in txt)

def broadcast(message, sender_name):
    with clients_lock:
        for name, client_socket in clients.items():
            if name != sender_name:
                try:
                    encrypted_message = encrypt(message, shared_keys[name])
                    client_socket.send(encrypted_message.encode('utf-8'))
                except:
                    client_socket.close()
                    del clients[name]
                    del shared_keys[name]

def handle_client(client_socket, client_name):
    try:
        while True:
            encrypted_message = client_socket.recv(1024).decode('utf-8')
            if encrypted_message:
                decrypted_message = decrypt(encrypted_message, shared_keys[client_name])
                broadcast_message = f"{client_name}: {decrypted_message}"
                print(broadcast_message)
                broadcast(decrypted_message, client_name)
            else:
                break
    except Exception as e:
        print(f"Error: {str(e)}")
    finally:
        with clients_lock:
            del clients[client_name]
            del shared_keys[client_name]
        leave_message = f"{client_name} has left the chat."
        print(leave_message)
        broadcast(leave_message, client_name)
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
                        del shared_keys[kick]
                        print(f"{kick} has been kicked.")
                    else:
                        print(f"{kick} is not in the chat.")
            else:
                with clients_lock:
                    for name in clients.keys():
                        encrypted_message = encrypt(message, shared_keys[name])
                        clients[name].send(encrypted_message.encode('utf-8'))
                print(f"Server: {message}")

send_thread = threading.Thread(target=send_message)
send_thread.start()

while True:
    clientSocket, clientAddress = serverSocket.accept()
    print(f"Accepted connection from {clientAddress[0]}:{clientAddress[1]}")

    # DH Key Exchange
    client_public_key = int(clientSocket.recv(1024).decode('utf-8'))
    private_key = random.randint(1, 100)
    public_key = (g ** private_key) % p
    clientSocket.send(str(public_key).encode('utf-8'))
    shared_key = (client_public_key ** private_key) % p
    print(f"DH Shared Key with {clientAddress}: {shared_key}")

    # Receive and decrypt username
    encrypted_username = clientSocket.recv(1024).decode('utf-8')
    username = decrypt(encrypted_username, shared_key)

    with clients_lock:
        clients[username] = clientSocket
        shared_keys[username] = shared_key

    join_message = f"{username} has joined the chat."
    print(join_message)
    broadcast(join_message, username)

    client_handler = threading.Thread(target=handle_client, args=(clientSocket, username))
    client_handler.start()
