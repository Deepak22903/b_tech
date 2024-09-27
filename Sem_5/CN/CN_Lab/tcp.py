import random

class TCP:
    def __init__(self):
        self.cwnd = 1          # Initial congestion window
        self.ssthresh = 64     # Initial ssthresh
        self.state = "SLOW_START"
        self.max_packets = 100  # Maximum packets to send for simulation
        self.sent_packets = 0   # Counter for sent packets

    def send(self):
        # Simulate sending packets
        print(f"Sending {self.cwnd} packets. State: {self.state}")
        self.sent_packets += 1

    def packet_loss(self):
        # Simulate packet loss with a 30% chance
        return random.random() < 0.3  # 30% chance of packet loss

    def run(self):
        while self.sent_packets < self.max_packets:
            self.send()
            if self.packet_loss():
                print("Packet lost!")
                if self.state == "SLOW_START":
                    self.cwnd = 1  # Reset to 1
                    self.state = "AIMD"
                elif self.state == "AIMD":
                    self.ssthresh = max(self.cwnd // 2, 1)  # Update ssthresh
                    self.cwnd = 1  # Reset cwnd to 1
                    self.state = "SLOW_START"
            else:
                if self.state == "SLOW_START":
                    self.cwnd *= 2  # Exponential increase in Slow Start
                elif self.state == "AIMD":
                    if self.cwnd < self.ssthresh:
                        self.cwnd *= 2  # Continue Slow Start
                    else:
                        self.cwnd += 1  # Linear increase

# Example usage
tcp = TCP()
tcp.run()
