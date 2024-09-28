
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

const int WINDOW_SIZE = 3;

void sendPackets(std::vector<int> &packets, int &base, int &nextSeqNum) {
  for (int i = 0; i < WINDOW_SIZE && (base + i) < packets.size(); i++) {
    std::cout << "Sending packet: " << packets[base + i] << std::endl;
    nextSeqNum++;
  }
}

bool receiveAck(int packet) {
  // Simulating ACK for only the first packet (Go-Back-N logic)
  if (packet % 2 == 0) {
    std::cout << "Received ACK for packet: " << packet << std::endl;
    return true;
  }
  return false; // Simulating loss/error
}

void goBackN() {
  std::vector<int> packets = {1, 2, 3, 4, 5, 6, 7, 8}; // Total 8 packets
  int base = 0;
  int nextSeqNum = 0;

  while (base < packets.size()) {
    sendPackets(packets, base, nextSeqNum);

    std::this_thread::sleep_for(
        std::chrono::seconds(2)); // Simulating network delay

    if (receiveAck(packets[base])) {
      base++; // Slide the window if ACK received
    } else {
      std::cout << "Timeout! Resending from packet: " << packets[base]
                << std::endl;
      nextSeqNum = base; // Go back to the base and resend
    }
  }
}

int main() {
  goBackN();
  return 0;
}
