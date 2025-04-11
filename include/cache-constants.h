#pragma once
namespace constants {
constexpr int MEM_SIZE = 1 << 18;
constexpr int ADDR_LEN = 18;
constexpr int CACHE_WAY = 4;
constexpr int CACHE_TAG_LEN = 9;
constexpr int CACHE_INDEX_LEN = 3;
constexpr int CACHE_OFFSET_LEN = 6;
constexpr int CACHE_SIZE = 2048;
constexpr int CACHE_LINE_SIZE = 64;
constexpr int CACHE_LINE_COUNT = 32;
constexpr int CACHE_SETS = 8;
} // namespace constants
