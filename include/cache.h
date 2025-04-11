#pragma once
#include <algorithm>
#include <bitset>
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>

#include "address.h"
#include "cache-constants.h"
#include "cache-set.h"
void exec(std::vector<std::string> &args, std::vector<int> &regs,
          std::unordered_map<std::string, std::string> &regs_map, int &addr,
          int &instr);
void store_exec(std::string cmd, int val, Address &address,
                std::vector<CacheLine>::iterator &it);
void replace_line_lru(std::vector<CacheSet> &cache, Address &address,
                      int &timer,
                      std::array<uint8_t, constants::MEM_SIZE> &mem);
void replace_line_plru(std::vector<CacheSet> &cache,
                       std::array<uint8_t, constants::MEM_SIZE> &mem,
                       Address &address);
void exists_line_plru(std::vector<CacheSet> &cache, Address &address,
                      std::vector<CacheLine>::iterator &it);
void exec_lru(std::vector<CacheSet> &cache,
              std::array<uint8_t, constants::MEM_SIZE> &mem, Address &address,
              int &timer, std::string cmd, int val, int &data_hit);
void exec_plru(std::vector<CacheSet> &cache,
               std::array<uint8_t, constants::MEM_SIZE> &mem, Address &address,
               int new_addr, int &timer, std::string cmd, int val,
               int &data_hit);
void data_instructions_exec(
    std::array<uint8_t, constants::MEM_SIZE> &mem,
    std::vector<std::string> &args, std::vector<int> &regs,
    std::unordered_map<std::string, std::string> &regs_map,
    std::vector<CacheSet> &cache, int &timer, int &addr, int &data_hit,
    std::string policy);
std::vector<int>
simulate_lru_cache(std::vector<std::vector<std::string>> &args,
                   std::vector<int> &regs,
                   std::unordered_map<std::string, std::string> &regs_map,
                   std::array<uint8_t, constants::MEM_SIZE> &mem);

std::vector<int>
simulate_plru_cache(std::vector<std::vector<std::string>> &args,
                    std::vector<int> &regs,
                    std::unordered_map<std::string, std::string> &regs_map,
                    std::array<uint8_t, constants::MEM_SIZE> &mem);
