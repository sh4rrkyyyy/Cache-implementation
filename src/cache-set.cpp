#include "cache-set.h"
#include "cache-constants.h"

CacheSet::CacheSet() : cache_set_(std::vector<CacheLine>(constants::CACHE_WAY)) {}

std::vector<CacheLine>& CacheSet::get_cache_set()  { return cache_set_; }
