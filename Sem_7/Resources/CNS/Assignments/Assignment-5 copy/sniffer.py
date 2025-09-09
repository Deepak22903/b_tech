import socket
import threading

serverIP = '127.0.0.1'
serverPort = 9876
snifferIP = '127.0.0.1'
snifferPort = 9999
BUFFER_SIZE = 1024

def handle_client(client_socket, server_socket):
    while True:
        try:
            data = client_socket.recv(BUFFER_SIZE)
            if not data:
                break
            print(f"[SNIFFED CLIENT -> SERVER]: {data.decode('utf-8')}")
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
            print(f"[SNIFFED SERVER -> CLIENT]: {data.decode('utf-8')}")
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

        threading.Thread(target=handle_client, args=(clientSocket, serverSocket)).start()
        threading.Thread(target=handle_server, args=(serverSocket, clientSocket)).start()

if __name__ == "__main__":
    start_sniffer()
