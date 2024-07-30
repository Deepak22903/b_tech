import socket
import threading

severSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serverAddress = ('localhost', 9876)
severSocket.bind(serverAddress)
severSocket.listen(5)
print(f"Server is listening on {serverAddress[0]}:{serverAddress[1]}")

clients = {}

def broadcast(message, sender_name):
    for name, client_socket in clients.items():
        if name != sender_name:
            try:
                client_socket.send(message)
            except:
                del clients[name]

# def handle_client(client_socket, client_name):
#     try:
#         while True:
#             message = client_socket.recv(1024)
#             if message:
#                 broadcast_message = f"{client_name}: {message.decode('utf-8')}"
#                 print(broadcast_message)
#                 broadcast(broadcast_message.encode('utf-8'), client_name)
#             else:
#                 break
#     except Exception as e:
#         print(f"Error: {str(e)}")
#     finally:
#         del clients[client_name]
#         leave_message = f"{client_name} has left the chat."
#         print(leave_message)
#         broadcast(leave_message.encode('utf-8'), client_name)
#         client_socket.close()

def send_message(client_socket, client_name):
    while True:
        message = input()
        try:
            if message:
                if message == ":quit":
                    for name, client_socket in clients.items():
                        client_socket.close()
                    severSocket.close()
                    exit()
                elif message == ":show":
                    print(clients)
                elif message == ":kick":
                    kick = input("Who do you want to kick? ")
                    if kick in clients:
                        clients[kick].close()
                        del clients[kick]
                        print(f"{kick} has been kicked.")
                    else:
                        print(f"{kick} is not in the chat.")
                else:
                    broadcast(("Server: "+message).encode('utf-8'), "Sever")
        except Exception as e:
            print(f"Error: {str(e)}")
        
while True:
    try:
        clientSocket, clientAddress = severSocket.accept()
        print(f"Accepted connection from {clientAddress[0]}:{clientAddress[1]}")

        username = clientSocket.recv(1024).decode('utf-8')
        print(f"Client's username is {username}.")

        clients[username] = clientSocket

        join_message = f"{username} has joined the chat."
        print(join_message)
        broadcast(join_message.encode('utf-8'), username)

        # client_handler = threading.Thread(target=handle_client, args=(clientSocket, username))
        # client_handler.start()

        send_thread = threading.Thread(target=send_message, args=(clientSocket, username))
        send_thread.start()
    except Exception as e:
        print(f"Error: {str(e)}")
        exit(0)




