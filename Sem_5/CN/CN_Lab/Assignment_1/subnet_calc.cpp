#include <bitset>
#include <iostream>
#include <sstream>

using namespace std;

string ip_to_binary(const string &ip) {
  string binary_ip;
  istringstream iss(ip);
  string octet;
  while (getline(iss, octet, '.')) {
    int octet_int = stoi(octet);
    binary_ip += bitset<8>(octet_int).to_string();
  }
  return binary_ip;
}

string binary_to_ip(const string &binary_ip) {
  string ip;
  for (size_t i = 0; i < binary_ip.size(); i += 8) {
    bitset<8> octet(binary_ip.substr(i, 8));
    ip += to_string(octet.to_ulong()) + ".";
  }
  ip.pop_back(); // Remove the last dot
  return ip;
}

int subnet_mask_to_cidr(const string &subnet_mask) {
  string binary_mask = ip_to_binary(subnet_mask);
  int prefix_length = 0;
  for (char bit : binary_mask) {
    if (bit == '1') {
      prefix_length++;
    } else {
      break;
    }
  }
  return prefix_length;
}

int main() {
  string subnet_mask;
  string ip_address;

  cout << "Enter the subnet mask in decimal : ";
  cin >> subnet_mask;

  cout << "Enter a valid class C IP address : ";
  cin >> ip_address;

  string binary_ip = ip_to_binary(ip_address);

  int prefix_length = subnet_mask_to_cidr(subnet_mask);
  string subnet_mask_binary = ip_to_binary(subnet_mask);

  string network_id_binary =
      binary_ip.substr(0, prefix_length) + string(32 - prefix_length, '0');
  string broadcast_address_binary =
      binary_ip.substr(0, prefix_length) + string(32 - prefix_length, '1');

  string subnet_mask_decimal = binary_to_ip(subnet_mask_binary);
  string network_id = binary_to_ip(network_id_binary);
  string broadcast_address = binary_to_ip(broadcast_address_binary);

  int num_ip_addresses_per_subnet = (1 << (32 - prefix_length)) - 2;

  cout << "Enter the subnet mask in CIDR notation (/24 - /30): /"
       << prefix_length << "\n";
  cout << "Subnet mask in decimal: " << subnet_mask << "\n";
  cout << "Enter valid class C IP address: " << ip_address << "\n";
  cout << "No. of subnets: " << (1 << (prefix_length - 24)) << "\n";
  cout << "No. of IP addresses per subnet: " << num_ip_addresses_per_subnet
       << "\n";
  cout << "Network Id: " << network_id << "\n";
  cout << "Broadcast address: " << broadcast_address << "\n";
  cout << "Usable host address range: " << network_id << " - "
       << broadcast_address << "\n";

  return 0;
}
