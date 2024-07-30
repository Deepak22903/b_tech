import socket
import time

def main():
    # Server configuration
    server_host = "127.0.0.1"
    server_port = 9876

    try:
        # Create a server socket
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_socket.bind((server_host, server_port))
        server_socket.listen(1)
        print(f"Server listening on {server_host} port {server_port}")

        # Accept a client connection
        client_socket, client_address = server_socket.accept()
        print(f"Accepted connection from {client_address}")

        # Initialize TCP Tahoe parameters
        cwnd = 1
        ssthresh = 64
        no_of_packets_to_send = 1000
        packets_sent = 0

        try:
            out = client_socket.makefile(mode="w")
            in_stream = client_socket.makefile(mode="r")

            while no_of_packets_to_send > packets_sent:
                # Send data to the client
                print(f"Server: Congestion window size = {cwnd} | No of packets to send = {no_of_packets_to_send}")
                out.write(f"{cwnd}\n")
                out.flush()

                # Simulate network delay
                time.sleep(1)

                # Receive acknowledgment from the client
                ack = in_stream.readline().strip()
                no_of_packets_to_send -= cwnd
                if cwnd <= ssthresh:
                    # Slow start phase: Increase cwnd exponentially
                    cwnd *= 2
                else:
                    # Congestion avoidance phase: Increase cwnd linearly
                    cwnd += 1
        except (IOError, ConnectionError) as e:
            print(f"Error: {e}")

        print("Server finished.")
        client_socket.close()
        server_socket.close()
    except (IOError, ConnectionError) as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    main()
