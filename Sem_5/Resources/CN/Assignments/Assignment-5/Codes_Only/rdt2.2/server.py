import socket
import threading

severSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serverAddress = ('localhost', 9876)
severSocket.bind(serverAddress)
severSocket.listen(5)
print(f"Server is listening on {serverAddress[0]}:{serverAddress[1]}")

clients = {}
data=[""]
sendNo=["0"]

packetNo = 0

def broadcast(message, sender_name):
    for name, client_socket in clients.items():
        if name != sender_name:
            try:
                client_socket.send(message)
            except:
                del clients[name]

def handle_client(client_socket, client_name):
    try:
        while True:
            message = client_socket.recv(1024)
            if message:
                broadcast_message = f"{client_name}: {message.decode('utf-8')}"
                print(broadcast_message)
                ackno = broadcast_message.split("] ")
                ackno = str(ackno[0][-1])
                if sendNo[0] != ackno:
                    if sendNo[0] == "0":
                        sendNo[0] = "1"
                    else:
                        sendNo[0] = "0"
                else:
                    checksum = 0
                    for i in data[0]:
                        checksum += ord(i)
                    checksum = checksum % 256
                    msg=f"[{str(packetNo)}] [{checksum}] {data[0]}" 
                    broadcast((msg).encode('utf-8'), "Sever")
                # broadcast(broadcast_message.encode('utf-8'), client_name)
            else:
                break
    except Exception as e:
        print(f"Error: {str(e)}")
    finally:
        del clients[client_name]
        leave_message = f"{client_name} has left the chat."
        print(leave_message)
        broadcast(leave_message.encode('utf-8'), client_name)
        client_socket.close()

def send_message(client_socket, client_name, packetNo):
    while True:
        message = input()
        try:
            if message:
                if message == ":quit":
                    for name, client_socket in clients.items():
                        client_socket.close()
                    severSocket.close()
                    exit()
                else:
                    data[0]=message
                    checksum = 0
                    for i in message:
                        checksum += ord(i)
                    checksum = checksum % 256
                    if packetNo % 3 == 0:
                        checksum += 1
                    
                    msg=f"[{str(packetNo)}] [{checksum}] {message}"
                    broadcast((msg).encode('utf-8'), "Sever")
                    packetNo+=1

        except Exception as e:
            print(f"Error: {str(e)}")
        
def check_prime(n):
    if n <= 1:
        return False
    for i in range(2, n):
        if n % i == 0:
           return False
    return True

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

        client_handler = threading.Thread(target=handle_client, args=(clientSocket, username))
        client_handler.start()

        send_thread = threading.Thread(target=send_message, args=(clientSocket, username, packetNo))
        send_thread.start()
    except Exception as e:
        print(f"Error: {str(e)}")
        exit(0)




