#pragma once
#include <cstdint>
#include <string>
#include <vector>
class CacheLine {
private:
  int tag_;
  int timer_;
  std::vector<uint8_t> bytes_;

public:
  CacheLine();
  int get_tag() const;
  int get_timer() const;
  std::vector<uint8_t> get_bytes() const;
  void set_tag(int tag);
  void set_timer(int timer);
  void set_bytes(std::vector<uint8_t> &bytes);
};
