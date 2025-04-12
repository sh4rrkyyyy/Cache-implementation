#include "cache-constants.h"
#include "cache.h"
#include "translate.h"
#include <array>
#include <bitset>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

int main(int argc, char *argv[]) {
  std::ifstream in;
  std::ofstream out;
  if (argc == 5) {
    if (strcmp(argv[1], "--asm") == 0) {
      in.open(argv[2]);
      out.open(argv[4], std::ios::binary);
    } else {
      in.open(argv[4]);
      out.open(argv[2], std::ios::binary);
    }
  } else if (argc == 3) {
    in.open(argv[2]);
  }
  std::vector<std::string> args;
  std::string str;

  while (std::getline(in, str)) {
    if (!str.empty()) {
      str.erase(0, str.find_first_not_of(" \t\r\n"));
      str.erase(str.find_last_not_of(" \t\r\n") + 1);
      if (str.empty())
        continue;
      char *str_copy = new char[str.size() + 1];
      strcpy(str_copy, str.c_str());
      char *token = strtok(str_copy, " ,");
      while (token != nullptr) {
        if (strlen(token) > 0)
          args.push_back(token);
        token = strtok(nullptr, " ,");
      }
      delete[] str_copy;
    }
  }
  std::vector<std::vector<std::string>> commands;
  std::size_t i = 0;
  while (i < args.size()) {
    if (args[i] == "ecall" || args[i] == "ebreak" || args[i] == "fence.tso" ||
        args[i] == "pause") {
      if (args[i] == "ecall") {
        commands.push_back({args[i], "zero", "zero", "0x0"});
        i++;
      } else if (args[i] == "ebreak") {
        commands.push_back({args[i], "zero", "zero", "0x1"});
        i++;
      } else {
        commands.push_back({args[i]});
        i++;
      }
    } else if (args[i] == "lui" || args[i] == "auipc" || args[i] == "jal" ||
               args[i] == "fence") {
      commands.push_back({args[i], args[i + 1], args[i + 2]});
      i += 3;
    } else {
      commands.push_back({args[i], args[i + 1], args[i + 2], args[i + 3]});
      i += 4;
    }
  }
  
  if (out.is_open()) {
    translate(commands, out);
  }
  
  std::vector<int> registers_lru(32);
  std::vector<int> registers_plru(32);
  std::array<uint8_t, constants::MEM_SIZE> mem_lru;
  std::array<uint8_t, constants::MEM_SIZE> mem_plru;
  auto res_lru = simulate_lru_cache(commands, registers_lru, regs, mem_lru);
  auto res_plru = simulate_plru_cache(commands, registers_plru, regs, mem_plru);
  printf("replacement\thit rate\thit rate (inst)\thit rate (data)\n");
  printf(
      "        LRU\t%3.5f%%\t%3.5f%%\t%3.5f%%\n",
      std::abs((double)(res_lru[2] + res_lru[3]) / (res_lru[0] + res_lru[1])) *
          100,
      std::abs((double)res_lru[2] / res_lru[0]) * 100.0,
      std::abs((double)res_lru[3] / res_lru[1]) * 100);
  printf("       pLRU\t%3.5f%%\t%3.5f%%\t%3.5f%%\n",
         std::abs((double)(res_plru[2] + res_plru[3]) /
                  (res_plru[0] + res_plru[1])) *
             100,
         std::abs((double)res_plru[2] / res_plru[0]) * 100,
         std::abs((double)res_plru[3] / res_plru[1]) * 100);
}
