#include <iostream>

class TCP {
protected:
  int cwnd;     // Congestion window size
  int ssthresh; // Slow start threshold
  int ackCount; // Number of acknowledgements received
  bool fastRecovery;

public:
  TCP() : cwnd(1), ssthresh(64), ackCount(0), fastRecovery(false) {}

  virtual void onAckReceived() = 0;
  virtual void onPacketLoss() = 0;

  void printStatus() {
    std::cout << "cwnd: " << cwnd << ", ssthresh: " << ssthresh << std::endl;
  }
};

class TCPSlowStart : public TCP {
public:
  void onAckReceived() override {
    if (cwnd < ssthresh) {
      cwnd *= 2; // Exponential increase
    } else {
      cwnd += 1; // Linear increase (AIMD phase)
    }
    printStatus();
  }

  void onPacketLoss() override {
    ssthresh = cwnd / 2; // Cut threshold in half
    cwnd = 1;            // Reset to Slow Start
    std::cout << "Packet loss detected. Entering Slow Start.\n";
    printStatus();
  }
};

class TCPTahoe : public TCPSlowStart {
public:
  void onPacketLoss() override {
    ssthresh = cwnd / 2; // Cut threshold in half
    cwnd = 1;            // Reset to Slow Start
    std::cout << "Packet loss detected in Tahoe. Entering Slow Start.\n";
    printStatus();
  }
};

class TCPReno : public TCPSlowStart {
public:
  void onAckReceived() override {
    if (fastRecovery) {
      cwnd += 1; // Linear increase during fast recovery
    } else {
      TCPSlowStart::onAckReceived();
    }
    printStatus();
  }

  void onPacketLoss() override {
    if (ackCount < 3) { // Simulating fast recovery detection
      ssthresh = cwnd / 2;
      cwnd = ssthresh + 3; // Fast recovery mode
      fastRecovery = true;
      std::cout << "Entering fast recovery.\n";
    } else {
      ssthresh = cwnd / 2; // Slow start threshold reduction
      cwnd = 1;            // Reset to Slow Start
      fastRecovery = false;
      std::cout << "Packet loss detected in Reno. Entering Slow Start.\n";
    }
    printStatus();
  }

  void onDuplicateAck() {
    ackCount++;
    if (ackCount == 3) {
      onPacketLoss(); // Fast recovery when 3 duplicate ACKs
    }
  }
};

int main() {
  TCPReno tcpReno;
  TCPTahoe tcpTahoe;

  std::cout << "TCP Reno Simulation:\n";
  for (int i = 0; i < 10; i++) {
    tcpReno.onAckReceived(); // Simulating ACK reception
  }
  tcpReno.onPacketLoss(); // Simulate packet loss in Reno

  std::cout << "\nTCP Tahoe Simulation:\n";
  for (int i = 0; i < 10; i++) {
    tcpTahoe.onAckReceived(); // Simulating ACK reception
  }
  tcpTahoe.onPacketLoss(); // Simulate packet loss in Tahoe

  return 0;
}
