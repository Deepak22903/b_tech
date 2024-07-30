import socket
import sys

def main():
    # Client configuration
    if len(sys.argv) != 3:
        exit(0)

    server_host = sys.argv[1]
    server_port = int(sys.argv[2])

    # Create a client socket
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        client_socket.connect((server_host, server_port))
        print(f"Connected to the server on {server_host} port {server_port}")
    except ConnectionError as e:
        print(f"Error: {e}")
        return

    try:
        while True:
            # Receive data from the server
            data = client_socket.recv(1024).decode()
            if not data:
                break

            print(f"Client received data size: {data}")

            # Simulate an ACK by sending an "ACK" response to the server
            client_socket.send("ACK".encode())

    except ConnectionError as e:
        print(f"Error: {e}")

    client_socket.close()

if __name__ == "__main__":
    main()
