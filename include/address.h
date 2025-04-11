#pragma once
#include <string>
struct Address {
  int tag;
  int index;
  int offset;
  std::string addr_str;
  Address(int addr);
};