
#include <chrono>
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
  if (packet % 2 == 0) {
    std::cout << "Received ACK for packet: " << packet << std::endl;
    return true;
  }
  return false; // Simulating packet loss
}

void selectiveRepeat() {
  std::vector<int> packets = {1, 2, 3, 4, 5, 6, 7, 8}; // Total 8 packets
  int base = 0;
  int nextSeqNum = 0;

  while (base < packets.size()) {
    for (int i = base; i < base + WINDOW_SIZE && i < packets.size(); i++) {
      if (!ackStatus[i - base]) {
        sendPacket(packets[i]);
        std::this_thread::sleep_for(
            std::chrono::milliseconds(500)); // Simulating delay
      }
    }

    for (int i = base; i < base + WINDOW_SIZE && i < packets.size(); i++) {
      if (!ackStatus[i - base]) {
        ackStatus[i - base] = receiveAck(packets[i]);
      }
    }

    // Slide the window forward if possible
    while (base < packets.size() && ackStatus[0]) {
      for (int i = 0; i < WINDOW_SIZE - 1; i++) {
        ackStatus[i] = ackStatus[i + 1];
      }
      ackStatus[WINDOW_SIZE - 1] = 0;
      base++;
    }
  }
}

int main() {
  selectiveRepeat();
  return 0;
}
