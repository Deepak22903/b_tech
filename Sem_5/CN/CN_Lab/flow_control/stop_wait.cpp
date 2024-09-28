
#include <chrono>
#include <iostream>
#include <thread>

void sendPacket(int packet) {
  std::cout << "Sending packet: " << packet << std::endl;
}

bool receiveAck(int packet) {
  // Simulating an ACK
  std::cout << "Received ACK for packet: " << packet << std::endl;
  return true; // Assuming ACK is always received
}

void stopAndWait() {
  int packet = 1;
  bool ackReceived = false;

  while (packet <= 5) { // Simulating 5 packets
    sendPacket(packet);

    std::this_thread::sleep_for(
        std::chrono::seconds(2)); // Simulating network delay

    ackReceived = receiveAck(packet);

    if (ackReceived) {
      packet++;
    } else {
      std::cout << "Timeout! Resending packet: " << packet << std::endl;
    }
  }
}

int main() {
  stopAndWait();
  return 0;
}
