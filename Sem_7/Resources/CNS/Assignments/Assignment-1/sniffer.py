import socket
import threading

serverIP = '127.0.0.1'  # Server IP
serverPort = 9876       # Server Port
BUFFER_SIZE = 1024      # Buffer size for data

# Sniffer will listen on a different port
snifferIP = '127.0.0.1'
snifferPort = 9999  # Sniffer port, distinct from server port

def handle_client(client_socket, server_socket):
    while True:
        try:
            data = client_socket.recv(BUFFER_SIZE)
            if not data:
                break
            server_socket.send(data)  # Forward data to server
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
            print(f"[SNIFFED]: {data.decode('utf-8')}")  # Log intercepted data
            client_socket.send(data)  # Forward data back to client
        except:
            break

    client_socket.close()
    server_socket.close()

def start_sniffer():
    # Set up the sniffer
    snifferSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    snifferSocket.bind((snifferIP, snifferPort))
    snifferSocket.listen(5)
    print(f"Sniffer listening on {snifferIP}:{snifferPort}")

    while True:
        # Accept connections from the client
        clientSocket, clientAddress = snifferSocket.accept()
        print(f"Accepted connection from {clientAddress[0]}:{clientAddress[1]}")

        # Establish a connection to the actual server
        serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        serverSocket.connect((serverIP, serverPort))

        # Create threads for bidirectional forwarding
        client_thread = threading.Thread(target=handle_client, args=(clientSocket, serverSocket))
        server_thread = threading.Thread(target=handle_server, args=(serverSocket, clientSocket))

        client_thread.start()
        server_thread.start()

if __name__ == "__main__":
    start_sniffer()
