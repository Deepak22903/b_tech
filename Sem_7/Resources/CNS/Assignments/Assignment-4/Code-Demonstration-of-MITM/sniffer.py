import socket
import threading
import sys

if len(sys.argv) != 3:
    print("Usage: python sniffer.py <server_ip> <server_port>")
    sys.exit(1)

snifferIP = 'localhost'
snifferPort = 9999

serverIP = sys.argv[1]
serverPort = int(sys.argv[2])

BUFFER_SIZE = 1024

def handle_client(client_socket, server_socket):
    while True:
        try:
            data = client_socket.recv(BUFFER_SIZE)
            if not data:
                break
            server_socket.send(data)
        except:
            break

    client_socket.close()
    server_socket.close()

def handle_server(server_socket, client_socket):
    while True:
        try:
            data = server_socket.recv(BUFFER_SIZE)
            if not data:
                break
            print(f"[SNIFFED]: {data.decode('utf-8')}")
            client_socket.send(data)
        except:
            break

    client_socket.close()
    server_socket.close()

def start_sniffer():
    snifferSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    snifferSocket.bind((snifferIP, snifferPort))
    snifferSocket.listen(5)
    print(f"Sniffer listening on {snifferIP}:{snifferPort}")

    while True:
        clientSocket, clientAddress = snifferSocket.accept()
        print(f"Accepted connection from {clientAddress[0]}:{clientAddress[1]}")

        serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        serverSocket.connect((serverIP, serverPort))

        client_thread = threading.Thread(target=handle_client, args=(clientSocket, serverSocket))
        server_thread = threading.Thread(target=handle_server, args=(serverSocket, clientSocket))

        client_thread.start()
        server_thread.start()

if __name__ == "__main__":
    start_sniffer()
