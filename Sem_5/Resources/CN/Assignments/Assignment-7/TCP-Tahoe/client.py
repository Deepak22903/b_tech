import socket
import sys

def main():
    # Client configuration
    if len(sys.argv) != 3:
        exit(0)

    server_host = sys.argv[1]
    server_port = int(sys.argv[2])

    try:
        # Create a client socket
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client_socket.connect((server_host, server_port))
        print(f"Connected to the server on {server_host} port {server_port}")

        try:
            out = client_socket.makefile(mode="w")
            in_stream = client_socket.makefile(mode="r")

            while True:
                # Receive data from the server
                data = in_stream.readline()
                if not data:
                    break

                print(f"Client received data till: {data}")

                # Simulate an ACK by sending an "ACK" response to the server
                out.write("ACK\n")
                out.flush()

        except (IOError, ConnectionError) as e:
            print(f"Error: {e}")

        client_socket.close()
    except (IOError, ConnectionError) as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    main()
