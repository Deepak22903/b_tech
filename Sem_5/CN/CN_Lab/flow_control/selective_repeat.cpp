#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>

const int WINDOW_SIZE = 4;
std::vector<int>
    ackStatus(WINDOW_SIZE,
              0); // Tracks ACK status for each packet in the window

void sendPacket(int packet) {
  std::cout << "Sending packet: " << packet << std::endl;
}

bool receiveAck(int packet) {
  // Simulate random ACK loss (50% chance of getting an ACK)
  if (rand() % 2 == 0) {
    std::cout << "Received ACK for packet: " << packet << std::endl;
    return true;
  }
  std::cout << "No ACK for packet: " << packet << std::endl;
  return false;
}

void selectiveRepeat() {
  std::vector<int> packets = {1, 2, 3, 4, 5, 6, 7, 8}; // Total 8 packets
  int base = 0;
  int nextSeqNum = 0;

  srand(time(0)); // Seed random number generator

  while (base < packets.size()) {
    // Send packets within the window
    for (int i = base; i < base + WINDOW_SIZE && i < packets.size(); i++) {
      if (!ackStatus[i - base]) { // Only send packets without ACK
        sendPacket(packets[i]);
        std::this_thread::sleep_for(
            std::chrono::milliseconds(500)); // Simulating delay
      }
    }

    // Check for ACKs for the packets in the window
    for (int i = base; i < base + WINDOW_SIZE && i < packets.size(); i++) {
      if (!ackStatus[i - base]) {
        ackStatus[i - base] = receiveAck(packets[i]); // Update ACK status
      }
    }

    // Slide the window forward if ACKs are received
    while (base < packets.size() && ackStatus[0]) {
      // Shift the window and clear the first slot
      for (int i = 0; i < WINDOW_SIZE - 1; i++) {
        ackStatus[i] = ackStatus[i + 1];
      }
      ackStatus[WINDOW_SIZE - 1] = 0; // New packet enters the window
      base++;                         // Move the base forward
    }

    // Simulate retransmission timeout
    std::this_thread::sleep_for(std::chrono::seconds(2));
  }
}

int main() {
  selectiveRepeat();
  return 0;
}
