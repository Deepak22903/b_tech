import socket
import random

def generate_checksum(message):
    checksum = 0
    for i in message:
        checksum += ord(i)
    checksum = checksum % 256
    return checksum

def main():
    sender_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sender_socket.settimeout(2)
    receiver_address = ('localhost', 9876)
    last_message = None
    q = 0
    prev = 0
    while True:
        if last_message is None:
            q = prev
            message = input("Message: ")
            if message.lower() == ':quit':
                sender_socket.sendto(f"{message}".encode(), receiver_address)
                break
        else:
            message = last_message
            q = prev

        checksum = generate_checksum(message)

        if random.random() < 0.2:
            last_message = message  
            message = 'corrupted' + message

        sender_socket.sendto(f"{checksum}:{message}:{q}".encode(), receiver_address)

        try:
            ack, _ = sender_socket.recvfrom(1024)

            if ack.decode() == str(q):
                print(f"Message sent successfully: {message}")
                last_message = None  # Clear the last message if sent successfully
                if q == 0:
                    prev = 1
                else:
                    prev = 0
            else:
                prev = q
                print("NAK received. Retransmitting...")

        except socket.timeout:
            print("Timeout!")
            continue

    sender_socket.close()

if __name__ == "__main__":
    main()