import socket
import time
import random
import sys

def main():
    if len(sys.argv) != 3:
        sys.exit(1)
    
    serverIP=sys.argv[1]
    serverPort=int(sys.argv[2])

    clientSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    receiverAddress = (serverIP, serverPort)
    clientSocket.bind(receiverAddress)

    while True:
        data, sender_address = clientSocket.recvfrom(1024)
        data = data.decode()
        if data.lower() == ':exit':
            break
        sleep_duration = random.random() * 4

        time.sleep(sleep_duration)

        if sleep_duration >= 2:
            continue

        if validate_checksum(data):
            print(f"Received message: {data.split(':')[1]}")
            q = data.split(':')[2]
            clientSocket.sendto(q.encode(), sender_address)
        else:
            q = data.split(':')[2]
            print("Received corrupted message. Sending NAK.")
            if q == '0':
                q = '1'
            else:
                q = '0'
                
            clientSocket.sendto(q.encode(), sender_address)

    clientSocket.close()

def validate_checksum(message):
    parts = message.split(':')
    received_checksum, received_message = int(parts[0]), parts[1]
    calculated_checksum = 0
    for char in received_message:
        calculated_checksum ^= ord(char)
    
    if calculated_checksum == received_checksum:
        return True
    else:
        print(f"Received Corrupted Message: {received_message}")
        return False

if __name__ == "__main__":
    main()