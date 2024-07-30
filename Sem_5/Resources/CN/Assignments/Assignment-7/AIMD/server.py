import socket

def main():
    # Server configuration
    server_host = "127.0.0.1"
    server_port = 9876

    # Create a server socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        server_socket.bind((server_host, server_port))
        server_socket.listen(1)
    except ConnectionError as e:
        print(f"Error: {e}")
        return

    print(f"Server listening on {server_host} port {server_port}")

    # Accept a client connection
    client_socket, client_address = server_socket.accept()
    print(f"Accepted connection from {client_address}")

    # AIMD simulation
    congestion_window = 1
    threshold = 8
    i = 0
    try:
        while i < 20:
            print(f"Server: Congestion window size = {congestion_window}")

            # Send the congestion window value to the client
            client_socket.send(str(congestion_window).encode())

            # Receive ACK from the client
            ack = client_socket.recv(1024).decode()

            if congestion_window >= threshold:
                congestion_window //= 2
            else:
                congestion_window += 1
            i += 1
    except ConnectionError as e:
        print(f"Error: {e}")

    print("Completed!")

    client_socket.close()
    server_socket.close()

if __name__ == "__main__":
    main()
