#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>
#include <vector>

const int WINDOW_SIZE = 3;

void sendPackets(std::vector<int> &packets, int base, int &nextSeqNum) {
  for (int i = 0; i < WINDOW_SIZE && (base + i) < packets.size(); i++) {
    std::cout << "Sending packet: " << packets[base + i] << std::endl;
    nextSeqNum++;
  }
}

bool receiveAck(int packet) {
  // Simulate packet loss with random ACK reception
  if (rand() % 2 == 0) { // 50% chance of receiving an ACK
    std::cout << "Received ACK for packet: " << packet << std::endl;
    return true;
  } else {
    std::cout << "No ACK for packet: " << packet << std::endl;
    return false;
  }
}

void goBackN() {
  std::vector<int> packets = {1, 2, 3, 4, 5, 6, 7, 8}; // Total 8 packets
  int base = 0;
  int nextSeqNum = 0;
  int ackCount = 0;

  // Seed for random number generation
  srand(time(0));

  while (base < packets.size()) {
    // Send packets within the window
    sendPackets(packets, base, nextSeqNum);

    // Simulate network delay
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Check ACKs for all packets within the window
    for (int i = 0; i < WINDOW_SIZE && (base + i) < packets.size(); i++) {
      if (receiveAck(packets[base + i])) {
        ackCount++;
      } else {
        break; // Stop checking further ACKs, go back to retransmit
      }
    }

    // Slide window based on received ACKs
    if (ackCount > 0) {
      base += ackCount;
      ackCount = 0;
    } else {
      std::cout << "Timeout! Resending from packet: " << packets[base]
                << std::endl;
      nextSeqNum = base; // Go back and resend from the base
    }
  }
}

int main() {
  goBackN();
  return 0;
}
