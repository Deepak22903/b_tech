#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <sys/socket.h>

using namespace std;

int main() {
  string hostname;
  cout << "Enter a domain name: ";
  cin >> hostname;

  struct hostent *he = gethostbyname(hostname.c_str());
  if (he == nullptr) {
    cerr << "Error: Unable to resolve hostname" << endl;
    return 1;
  }

  struct in_addr **addr_list = (struct in_addr **)he->h_addr_list;
  for (int i = 0; addr_list[i] != nullptr; i++) {
    char ipstr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, addr_list[i], ipstr, sizeof(ipstr));
    cout << "IP Address: " << ipstr << endl;
  }

  return 0;
}
