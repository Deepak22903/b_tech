#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <unistd.h>

using namespace std;

#define PORT 8080

void handle_client(int new_socket) {
  char buffer[1024] = {0};
  read(new_socket, buffer, 1024);
  cout << "Received request:\n" << buffer << endl;

  // Create a simple HTTP response
  string response = "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/html\r\n\r\n"
                    "<html><body><h1>Hello, World!</h1></body></html>";

  send(new_socket, response.c_str(), response.size(), 0);
  close(new_socket);
}

int main() {
  int server_fd, new_socket;
  struct sockaddr_in address;
  int addrlen = sizeof(address);

  // Creating socket file descriptor
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    cerr << "Socket failed" << endl;
    return -1;
  }

  // Forcefully attaching socket to the port 8080
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    cerr << "Bind failed" << endl;
    return -1;
  }

  if (listen(server_fd, 3) < 0) {
    cerr << "Listen failed" << endl;
    return -1;
  }

  cout << "Serving HTTP on port " << PORT << "..." << endl;

  while (true) {
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t *)&addrlen)) < 0) {
      cerr << "Accept failed" << endl;
      return -1;
    }

    handle_client(new_socket);
  }

  return 0;
}
