#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netdb.h>

using namespace std;

int main() {
  string hostname;
  cout << "Enter a domain name: ";
  cin >> hostname;

  struct addrinfo hints, *res;
  int err;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  err = getaddrinfo(hostname.c_str(), nullptr, &hints, &res);
  if (err != 0) {
    cerr << "Error: " << gai_strerror(err) << endl;
    return 1;
  }

  for (struct addrinfo *p = res; p != nullptr; p = p->ai_next) {
    void *addr;
    char ipstr[INET6_ADDRSTRLEN];

    if (p->ai_family == AF_INET) { // IPv4
      struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
      addr = &(ipv4->sin_addr);
    } else { // IPv6
      struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
      addr = &(ipv6->sin6_addr);
    }

    inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
    cout << "IP Address: " << ipstr << endl;
  }

  freeaddrinfo(res);

  return 0;
}
