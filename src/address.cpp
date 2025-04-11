#include "address.h"

#include <bitset>
#include <string>

Address::Address(int addr) {
  addr_str = std::bitset<18>(addr).to_string();
  tag = std::stoi(addr_str.substr(0, 9), nullptr, 2);
  index = std::stoi(addr_str.substr(9, 3), nullptr, 2);
  offset = std::stoi(addr_str.substr(12), nullptr, 2);
}