#include "cache-line.h"

#include <cstdint>
#include <vector>
CacheLine::CacheLine()
    : tag_(INT32_MIN), timer_(0), bytes_(std::vector<uint8_t>(64)) {}

int CacheLine::get_tag() const { return tag_; }

int CacheLine::get_timer() const { return timer_; }

std::vector<uint8_t> CacheLine::get_bytes() const { return bytes_; }

void CacheLine::set_tag(int tag) { tag_ = tag; }

void CacheLine::set_timer(int timer) { timer_ = timer; }

void CacheLine::set_bytes(std::vector<uint8_t> &bytes) { bytes_ = bytes; }
