#pragma once
#include "cache-line.h"
#include <vector>
class CacheSet {
private:
  std::vector<CacheLine> cache_set_;

public:
  CacheSet();
  std::vector<CacheLine>& get_cache_set();
};
