
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <unistd.h>

using namespace std;

#define PORT 53 // Standard DNS port

void process_dns_query(int sock, struct sockaddr_in client_addr,
                       socklen_t client_len) {
  unsigned char buffer[512];
  int n = recvfrom(sock, buffer, sizeof(buffer), 0,
                   (struct sockaddr *)&client_addr, &client_len);

  if (n < 0) {
    cerr << "Failed to receive data" << endl;
    return;
  }

  cout << "Received DNS query" << endl;

  // Transaction ID
  unsigned char response[512];
  response[0] = buffer[0]; // Copy transaction ID
  response[1] = buffer[1];

  // Flags
  response[2] = 0x81; // Standard query response, no error
  response[3] = 0x80;

  // Questions
  response[4] = buffer[4]; // Questions count
  response[5] = buffer[5];

  // Answer RRs
  response[6] = 0x00; // Answer count
  response[7] = 0x01;

  // Authority RRs and Additional RRs
  response[8] = 0x00; // Authority count
  response[9] = 0x00;
  response[10] = 0x00; // Additional count
  response[11] = 0x00;

  // Copy the original query name
  int query_name_len = 12; // Starting position of the query name in the request
  int i = 0;
  while (buffer[query_name_len] != 0) {
    response[12 + i] = buffer[query_name_len];
    query_name_len++;
    i++;
  }

  response[12 + i] = 0; // End of query name
  int query_end = 12 + i + 1;

  // Copy query type and class
  response[query_end] = 0x00;
  response[query_end + 1] = 0x01; // Type A
  response[query_end + 2] = 0x00;
  response[query_end + 3] = 0x01; // Class IN

  // Answer Section
  response[query_end + 4] = 0xc0; // Compression pointer
  response[query_end + 5] = 0x0c; // Pointer to the domain name

  // Type and Class
  response[query_end + 6] = 0x00;
  response[query_end + 7] = 0x01; // Type A
  response[query_end + 8] = 0x00;
  response[query_end + 9] = 0x01; // Class IN

  // TTL
  response[query_end + 10] = 0x00;
  response[query_end + 11] = 0x00;
  response[query_end + 12] = 0x00;
  response[query_end + 13] = 0x3c; // 60 seconds

  // Data length
  response[query_end + 14] = 0x00;
  response[query_end + 15] = 0x04; // 4 bytes for IPv4 address

  // IP address (e.g., 93.184.216.34 for example.com)
  response[query_end + 16] = 93;
  response[query_end + 17] = 184;
  response[query_end + 18] = 216;
  response[query_end + 19] = 34;

  int response_size = query_end + 20;

  // Send the response back to the client
  sendto(sock, response, response_size, 0, (struct sockaddr *)&client_addr,
         client_len);
  cout << "Sent DNS response" << endl;
}

int main() {
  int sock;
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_len = sizeof(client_addr);

  // Creating socket file descriptor
  if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    cerr << "Socket creation failed" << endl;
    return -1;
  }

  memset(&server_addr, 0, sizeof(server_addr));
  memset(&client_addr, 0, sizeof(client_addr));

  // Filling server information
  server_addr.sin_family = AF_INET; // IPv4
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);

  // Bind the socket with the server address
  if (bind(sock, (const struct sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    cerr << "Bind failed" << endl;
    close(sock);
    return -1;
  }

  cout << "DNS Server is listening on port " << PORT << endl;

  // Server loop to process incoming queries
  while (true) {
    process_dns_query(sock, client_addr, client_len);
  }

  close(sock);
  return 0;
}
