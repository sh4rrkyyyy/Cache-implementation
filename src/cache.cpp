#include "cache.h"
#include "cache-constants.h"

#include <algorithm>
#include <array>
#include <bitset>
#include <csignal>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

void exec(std::vector<std::string> &args, std::vector<int> &regs,
          std::unordered_map<std::string, std::string> &regs_map, int &addr,
          int &instr) {
  if (args[0] == "add") {
    regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
        regs[std::stoi(regs_map[args[2]], nullptr, 2)] +
        regs[std::stoi(regs_map[args[3]], nullptr, 2)];
    regs[0] = 0;
    addr += 4;
    instr++;
  }
  if (args[0] == "sub") {
    regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
        regs[std::stoi(regs_map[args[2]], nullptr, 2)] -
        regs[std::stoi(regs_map[args[3]], nullptr, 2)];
    regs[0] = 0;

    addr += 4;
    instr++;
  }
  if (args[0] == "xor") {
    regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
        regs[std::stoi(regs_map[args[2]], nullptr, 2)] ^
        regs[std::stoi(regs_map[args[3]], nullptr, 2)];
    regs[0] = 0;

    addr += 4;
    instr++;
  }
  if (args[0] == "or") {
    regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
        regs[std::stoi(regs_map[args[2]], nullptr, 2)] |
        regs[std::stoi(regs_map[args[3]], nullptr, 2)];
    regs[0] = 0;

    addr += 4;
    instr++;
  }
  if (args[0] == "and") {
    regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
        regs[std::stoi(regs_map[args[2]], nullptr, 2)] &
        regs[std::stoi(regs_map[args[3]], nullptr, 2)];
    regs[0] = 0;

    addr += 4;
    instr++;
  }
  if (args[0] == "sll") {
    regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
        (uint32_t)regs[std::stoi(regs_map[args[2]], nullptr, 2)]
        << regs[std::stoi(regs_map[args[3]], nullptr, 2)];
    regs[0] = 0;

    addr += 4;
    instr++;
  }
  if (args[0] == "srl") {
    regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
        (uint32_t)regs[std::stoi(regs_map[args[2]], nullptr, 2)] >>
        regs[std::stoi(regs_map[args[3]], nullptr, 2)];
    regs[0] = 0;

    addr += 4;
    instr++;
  }
  if (args[0] == "sra") {
    regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
        regs[std::stoi(regs_map[args[2]], nullptr, 2)] >>
        regs[std::stoi(regs_map[args[3]], nullptr, 2)];
    regs[0] = 0;
    addr += 4;
    instr++;
  }
  if (args[0] == "slt") {
    regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
        (regs[std::stoi(regs_map[args[2]], nullptr, 2)] <
         regs[std::stoi(regs_map[args[3]], nullptr, 2)])
            ? 1
            : 0;
    regs[0] = 0;
    addr += 4;
    instr++;
  }
  if (args[0] == "sltu") {
    regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
        ((uint32_t)regs[std::stoi(regs_map[args[2]], nullptr, 2)] <
         (uint32_t)regs[std::stoi(regs_map[args[3]], nullptr, 2)])
            ? 1
            : 0;
    regs[0] = 0;
    addr += 4;
    instr++;
  }
  if (args[0] == "addi") {
    regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
        regs[std::stoi(regs_map[args[2]], nullptr, 2)] + std::stoi(args[3]);
    regs[0] = 0;
    addr += 4;
    instr++;
  }
  if (args[0] == "xori") {
    regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
        regs[std::stoi(regs_map[args[2]], nullptr, 2)] ^ std::stoi(args[3]);
    regs[0] = 0;
    addr += 4;
    instr++;
  }
  if (args[0] == "ori") {
    regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
        regs[std::stoi(regs_map[args[2]], nullptr, 2)] | std::stoi(args[3]);
    regs[0] = 0;
    addr += 4;
    instr++;
  }
  if (args[0] == "andi") {
    regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
        regs[std::stoi(regs_map[args[2]], nullptr, 2)] & std::stoi(args[3]);
    regs[0] = 0;
    addr += 4;
    instr++;
  }
  if (args[0] == "slli") {
    regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
        (uint32_t)regs[std::stoi(regs_map[args[2]], nullptr, 2)]
        << std::stoi(std::bitset<12>(std::stoi(args[3])).to_string().substr(7), nullptr, 2);
    regs[0] = 0;
    addr += 4;
    instr++;
  }
  if (args[0] == "srli") {
    regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
        (uint32_t)regs[std::stoi(regs_map[args[2]], nullptr, 2)] >>
        std::stoi(std::bitset<12>(std::stoi(args[3])).to_string().substr(7), nullptr, 2);
    
    regs[0] = 0;
    addr += 4;
    instr++;
  }
  if (args[0] == "srai") {
    regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
        regs[std::stoi(regs_map[args[2]], nullptr, 2)] >>
        std::stoi(std::bitset<12>(std::stoi(args[3])).to_string().substr(7), nullptr, 2);
    regs[0] = 0;
    addr += 4;
    instr++;
  }
  if (args[0] == "slti") {
    regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
        (regs[std::stoi(regs_map[args[2]], nullptr, 2)] < std::stoi(args[3]))
            ? 1
            : 0;
    regs[0] = 0;
    addr += 4;
    instr++;
  }
  if (args[0] == "sltiu") {
    regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
        ((uint32_t)regs[std::stoi(regs_map[args[2]], nullptr, 2)] <
         (uint32_t)std::stoi(args[3]))
            ? 1
            : 0;
    regs[0] = 0;
    addr += 4;
    instr++;
  }
  if (args[0] == "beq") {
    if (regs[std::stoi(regs_map[args[1]], nullptr, 2)] ==
        regs[std::stoi(regs_map[args[2]], nullptr, 2)]) {
      addr += std::stoi(args[3]);
      instr += std::stoi(args[3]) / 4;
    } else {
      addr += 4;
      instr++;
    }
  }
  if (args[0] == "bne") {
    if (regs[std::stoi(regs_map[args[1]], nullptr, 2)] !=
        regs[std::stoi(regs_map[args[2]], nullptr, 2)]) {
      addr += std::stoi(args[3]);
      instr += std::stoi(args[3]) / 4;
    } else {
      addr += 4;
      instr++;
    }
  }
  if (args[0] == "blt") {
    if (regs[std::stoi(regs_map[args[1]], nullptr, 2)] <
        regs[std::stoi(regs_map[args[2]], nullptr, 2)]) {
      addr += std::stoi(args[3]);
      instr += std::stoi(args[3]) / 4;
    } else {
      addr += 4;
      instr++;
    }
  }
  if (args[0] == "bge") {
    if (regs[std::stoi(regs_map[args[1]], nullptr, 2)] >=
        regs[std::stoi(regs_map[args[2]], nullptr, 2)]) {
      addr += std::stoi(args[3]);
      instr += std::stoi(args[3]) / 4;
    } else {
      addr += 4;
      instr++;
    }
  }
  if (args[0] == "bltu") {
    if ((uint32_t)regs[std::stoi(regs_map[args[2]], nullptr, 2)] <
        (uint32_t)regs[std::stoi(regs_map[args[2]], nullptr, 2)]) {
      addr += std::stoi(args[3]);
      instr += std::stoi(args[3]) / 4;
    } else {
      addr += 4;
      instr++;
    }
  }
  if (args[0] == "bgeu") {
    if ((uint32_t)regs[std::stoi(regs_map[args[1]], nullptr, 2)] >=
        (uint32_t)regs[std::stoi(regs_map[args[2]], nullptr, 2)]) {
      addr += std::stoi(args[3]);
      instr += std::stoi(args[3]) / 4;
    } else {
      addr += 4;
      instr++;
    }
  }
  if (args[0] == "jal") {
    regs[std::stoi(regs_map[args[1]], nullptr, 2)] = addr + 4;
    regs[0] = 0;
    addr += std::stoi(args[2]);
    instr += std::stoi(args[2]) / 4;
  }
  if (args[0] == "jalr") {
    regs[std::stoi(regs_map[args[1]], nullptr, 2)] = addr + 4;
    regs[0] = 0;
    addr = regs[std::stoi(regs_map[args[2]], nullptr, 2)] + std::stoi(args[3]);
    instr = (addr - 0x10000) / 4;
  }
  if (args[0] == "lui") {
    regs[std::stoi(regs_map[args[1]], nullptr, 2)] = std::stoi(args[2]) << 12;
    regs[0] = 0;
    addr += 4;
    instr++;
  }
  if (args[0] == "auipc") {
    regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
        addr + (std::stoi(args[2]) << 12);
    regs[0] = 0;
    addr += 4;
    instr++;
  }
  if (args[0] == "mul") {
    regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
        regs[std::stoi(regs_map[args[2]], nullptr, 2)] *
        regs[std::stoi(regs_map[args[3]], nullptr, 2)];
    regs[0] = 0;
    addr += 4;
    instr++;
  }
  if (args[0] == "mulh") {
    regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
        ((int64_t)regs[std::stoi(regs_map[args[2]], nullptr, 2)] *
         (int64_t)regs[std::stoi(regs_map[args[3]], nullptr, 2)]) >>
        32;
    regs[0] = 0;
    addr += 4;
    instr++;
  }
  if (args[0] == "mulhsu") {
    regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
        ((int64_t)regs[std::stoi(regs_map[args[2]], nullptr, 2)] *
         (uint64_t)(uint32_t)regs[std::stoi(regs_map[args[3]], nullptr, 2)]) >>
        32;
    regs[0] = 0;
    addr += 4;
    instr++;
  }
  if (args[0] == "mulhu") {
    regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
        ((uint64_t)(uint32_t)regs[std::stoi(regs_map[args[2]], nullptr, 2)] *
         (uint64_t)(uint32_t)regs[std::stoi(regs_map[args[3]], nullptr, 2)]) >>
        32;
    regs[0] = 0;
    addr += 4;
    instr++;
  }
  if (args[0] == "div") {
    if (regs[std::stoi(regs_map[args[3]], nullptr, 2)] == 0)
      regs[std::stoi(regs_map[args[1]], nullptr, 2)] = -1;
    else
      regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
          regs[std::stoi(regs_map[args[2]], nullptr, 2)] /
          regs[std::stoi(regs_map[args[3]], nullptr, 2)];
    regs[0] = 0;
    addr += 4;
    instr++;
  }
  if (args[0] == "divu") {
    if (regs[std::stoi(regs_map[args[3]], nullptr, 2)] == 0)
      regs[std::stoi(regs_map[args[1]], nullptr, 2)] = -1;
    else
      regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
          (uint32_t)regs[std::stoi(regs_map[args[2]], nullptr, 2)] /
          (uint32_t)regs[std::stoi(regs_map[args[3]], nullptr, 2)];
    regs[0] = 0;
    addr += 4;
    instr++;
  }
  if (args[0] == "rem") {
    if (regs[std::stoi(regs_map[args[3]], nullptr, 2)] == 0)
      regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
          regs[std::stoi(regs_map[args[2]], nullptr, 2)];
    else
      regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
          regs[std::stoi(regs_map[args[2]], nullptr, 2)] %
          regs[std::stoi(regs_map[args[3]], nullptr, 2)];
    regs[0] = 0;
    addr += 4;
    instr++;
  }
  if (args[0] == "remu") {
    if (regs[std::stoi(regs_map[args[3]], nullptr, 2)] == 0)
      regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
          regs[std::stoi(regs_map[args[2]], nullptr, 2)];
    else
      regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
          (uint32_t)regs[std::stoi(regs_map[args[2]], nullptr, 2)] %
          (uint32_t)regs[std::stoi(regs_map[args[3]], nullptr, 2)];
    regs[0] = 0;
    addr += 4;
    instr++;
  }
}

void store_exec(std::string cmd, int val, Address &address,
                std::vector<CacheLine>::iterator &it) {
  if (cmd == "sb") {
    std::vector<uint8_t> bytes = it->get_bytes();
    std::string val_str = std::bitset<32>(val).to_string();
    std::vector<uint8_t> new_bytes;
    for (int i = 0; i < 4; ++i) {
      new_bytes.push_back(
          (uint8_t)std::stoi(val_str.substr(8 * i, 8), nullptr, 2));
    }
    bytes[address.offset] = new_bytes[3];
    it->set_bytes(bytes);
  }
  if (cmd == "sh") {
    std::vector<uint8_t> bytes = it->get_bytes();
    std::string val_str = std::bitset<32>(val).to_string();
    std::vector<uint8_t> new_bytes;
    for (int i = 0; i < 4; ++i) {
      new_bytes.push_back(
          (uint8_t)std::stoi(val_str.substr(8 * i, 8), nullptr, 2));
    }
    bytes[address.offset] = new_bytes[3];
    bytes[address.offset + 1] = new_bytes[2];
    it->set_bytes(bytes);
  }
  if (cmd == "sw") {
    std::vector<uint8_t> bytes = it->get_bytes();
    std::string val_str = std::bitset<32>(val).to_string();
    std::vector<uint8_t> new_bytes;
    for (int i = 0; i < 4; ++i) {
      new_bytes.push_back(
          (uint8_t)std::stoi(val_str.substr(8 * i, 8), nullptr, 2));
    }
    for (int i = 0; i < 4; ++i)
      bytes[address.offset + i] = new_bytes[3 - i];
    it->set_bytes(bytes);
  }
}
void replace_line_lru(std::vector<CacheSet> &cache, Address &address,
                      int &timer,
                      std::array<uint8_t, constants::MEM_SIZE> &mem) {
  auto it =
      std::min_element(cache[address.index].get_cache_set().begin(),
                       cache[address.index].get_cache_set().end(),
                       [](const CacheLine &first, const CacheLine &second) {
                         return first.get_timer() < second.get_timer();
                       });
  it->set_timer(++timer);
  std::string first_bits =
      std::bitset<constants::CACHE_TAG_LEN>(it->get_tag()).to_string() +
      std::bitset<constants::CACHE_INDEX_LEN>(address.index).to_string();
  for (int i = 0; i < constants::CACHE_LINE_SIZE; ++i)
    mem[std::stoi(first_bits +
                      std::bitset<constants::CACHE_OFFSET_LEN>(i).to_string(),
                  nullptr, 2)] = it->get_bytes()[i];
  it->set_tag(address.tag);
  std::vector<uint8_t> copy_bytes;
  int start_addr = std::stoi(
      std::bitset<constants::CACHE_TAG_LEN>(address.tag).to_string() +
          std::bitset<constants::CACHE_INDEX_LEN>(address.index).to_string() +
          std::bitset<constants::CACHE_OFFSET_LEN>(0).to_string(),
      nullptr, 2);
  for (int i = 0; i < constants::CACHE_LINE_SIZE; ++i)
    copy_bytes.push_back(mem[start_addr + i]);
  it->set_bytes(copy_bytes);
}
void exec_lru(std::vector<CacheSet> &cache,
              std::array<uint8_t, constants::MEM_SIZE> &mem, Address &address,
              int &timer, std::string cmd, int val, int &data_hit) {
  auto it = std::find_if(cache[address.index].get_cache_set().begin(),
                         cache[address.index].get_cache_set().end(),
                         [&address](const CacheLine &cur) {
                           return cur.get_tag() == address.tag;
                         });
  if (it == cache[address.index].get_cache_set().end()) {
    replace_line_lru(cache, address, timer, mem);
    auto it = std::find_if(cache[address.index].get_cache_set().begin(),
                           cache[address.index].get_cache_set().end(),
                           [&address](const CacheLine &cur) {
                             return cur.get_tag() == address.tag;
                           });
    store_exec(cmd, val, address, it);
  } else {
    it->set_timer(++timer);
    data_hit++;
    store_exec(cmd, val, address, it);
  }
}

void replace_line_plru(std::vector<CacheSet> &cache,
                       std::array<uint8_t, constants::MEM_SIZE> &mem,
                       Address &address) {
  auto it = std::find_if(
      cache[address.index].get_cache_set().begin(),
      cache[address.index].get_cache_set().end(),
      [&address](const CacheLine &cl) { return cl.get_timer() == 0; });
  if (it != cache[address.index].get_cache_set().end()) {
    std::string first_bits =
        std::bitset<constants::CACHE_TAG_LEN>(it->get_tag()).to_string() +
        std::bitset<constants::CACHE_INDEX_LEN>(address.index).to_string();
    for (int i = 0; i < constants::CACHE_LINE_SIZE; ++i)
      mem[std::stoi(first_bits +
                        std::bitset<constants::CACHE_OFFSET_LEN>(i).to_string(),
                    nullptr, 2)] = it->get_bytes()[i];
    it->set_tag(address.tag);
    std::vector<uint8_t> copy_bytes;
    int start_addr = std::stoi(
        std::bitset<constants::CACHE_TAG_LEN>(address.tag).to_string() +
            std::bitset<constants::CACHE_INDEX_LEN>(address.index).to_string() +
            std::bitset<constants::CACHE_OFFSET_LEN>(0).to_string(),
        nullptr, 2);
    for (int i = 0; i < constants::CACHE_LINE_SIZE; ++i)
      copy_bytes.push_back(mem[start_addr + i]);
    it->set_bytes(copy_bytes);
  }
  auto cnt_bits = std::count_if(
      cache[address.index].get_cache_set().begin(),
      cache[address.index].get_cache_set().end(),
      [&address](const CacheLine &cl) { return cl.get_timer() == 1; });
  if (cnt_bits == constants::CACHE_WAY - 1) {
    std::transform(cache[address.index].get_cache_set().begin(),
                   cache[address.index].get_cache_set().end(),
                   cache[address.index].get_cache_set().begin(),
                   [&address](CacheLine &cl) {
                     if (cl.get_timer() == 1) {
                       cl.set_timer(0);
                       return cl;
                     } else {
                       cl.set_timer(1);
                       return cl;
                     }
                   });
  } else {
    it->set_timer(1);
  }
}

void exists_line_plru(std::vector<CacheSet> &cache, Address &address,
                      std::vector<CacheLine>::iterator &it) {
  if (it->get_timer() == 0) {
    auto cnt_bits = std::count_if(
        cache[address.index].get_cache_set().begin(),
        cache[address.index].get_cache_set().end(),
        [&address](const CacheLine &cl) { return cl.get_timer() == 1; });
    if (cnt_bits == constants::CACHE_WAY - 1) {
      std::transform(cache[address.index].get_cache_set().begin(),
                     cache[address.index].get_cache_set().end(),
                     cache[address.index].get_cache_set().begin(),
                     [](CacheLine &cl) {
                       if (cl.get_timer() == 1) {
                         cl.set_timer(0);
                         return cl;
                       } else {
                         cl.set_timer(1);
                         return cl;
                       }
                     });
    } else {
      it->set_timer(1);
    }
  }
}
void exec_plru(std::vector<CacheSet> &cache,
               std::array<uint8_t, constants::MEM_SIZE> &mem, Address &address,
               int new_addr, int &timer, std::string cmd, int val,
               int &data_hit) {
  auto it = std::find_if(
      cache[address.index].get_cache_set().begin(),
      cache[address.index].get_cache_set().end(),
      [&address](const CacheLine &cl) { return cl.get_tag() == address.tag; });
  if (it == cache[address.index].get_cache_set().end()) {
    replace_line_plru(cache, mem, address);
    auto it = std::find_if(cache[address.index].get_cache_set().begin(),
                           cache[address.index].get_cache_set().end(),
                           [&address](const CacheLine &cur) {
                             return cur.get_tag() == address.tag;
                           });
    store_exec(cmd, val, address, it);
  } else {
    data_hit++;
    exists_line_plru(cache, address, it);
    store_exec(cmd, val, address, it);
  }
}
void data_instructions_exec(
    std::array<uint8_t, constants::MEM_SIZE> &mem,
    std::vector<std::string> &args, std::vector<int> &regs,
    std::unordered_map<std::string, std::string> &regs_map,
    std::vector<CacheSet> &cache, int &timer, int &addr, int &data_hit,
    std::string policy) {
  if (args[0] == "lb") {
    int new_addr =
        regs[std::stoi(regs_map[args[3]], nullptr, 2)] + std::stoi(args[2]);
    Address address = Address(new_addr);
    if (policy == "lru")
      exec_lru(cache, mem, address, timer, args[0], 0, data_hit);
    else
      exec_plru(cache, mem, address, new_addr, timer, args[0], 0, data_hit);
    auto it = std::find_if(cache[address.index].get_cache_set().begin(),
                           cache[address.index].get_cache_set().end(),
                           [&address](const CacheLine &cl) {
                             return cl.get_tag() == address.tag;
                           });

    if (it != cache[address.index].get_cache_set().end()) {
      regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
          (int8_t)it->get_bytes()[address.offset];
    }

    addr += 4;
  }
  if (args[0] == "lh") {
    int new_addr =
        regs[std::stoi(regs_map[args[3]], nullptr, 2)] + std::stoi(args[2]);
    Address address = Address(new_addr);
    if (policy == "lru")
      exec_lru(cache, mem, address, timer, args[0], 0, data_hit);
    else
      exec_plru(cache, mem, address, new_addr, timer, args[0], 0, data_hit);
    auto it = std::find_if(cache[address.index].get_cache_set().begin(),
                           cache[address.index].get_cache_set().end(),
                           [&address](const CacheLine &cl) {
                             return cl.get_tag() == address.tag;
                           });

    if (it != cache[address.index].get_cache_set().end()) {
      std::string val_str;

      val_str +=
          std::bitset<8>(it->get_bytes()[address.offset + 1]).to_string() +
          std::bitset<8>(it->get_bytes()[address.offset]).to_string();
      regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
          (int16_t)std::stoll(val_str, nullptr, 16);
    }
    addr += 4;
  }
  if (args[0] == "lw") {
    int new_addr =
        regs[std::stoi(regs_map[args[3]], nullptr, 2)] + std::stoi(args[2]);
    Address address = Address(new_addr);
    if (policy == "lru")
      exec_lru(cache, mem, address, timer, args[0], 0, data_hit);
    else
      exec_plru(cache, mem, address, new_addr, timer, args[0], 0, data_hit);
    auto it = std::find_if(cache[address.index].get_cache_set().begin(),
                           cache[address.index].get_cache_set().end(),
                           [&address](const CacheLine &cl) {
                             return cl.get_tag() == address.tag;
                           });

    if (it != cache[address.index].get_cache_set().end()) {
      std::string val_str;
      for (int i = 3; i >= 0; --i)
        val_str +=
            std::bitset<8>(it->get_bytes()[address.offset + i]).to_string();
      regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
          (int32_t)std::stoll(val_str, nullptr, 2);
    }
    addr += 4;
  }
  if (args[0] == "lbu") {
    int new_addr =
        regs[std::stoi(regs_map[args[3]], nullptr, 2)] + std::stoi(args[2]);
    Address address = Address(new_addr);
    if (policy == "lru")
      exec_lru(cache, mem, address, timer, args[0], 0, data_hit);
    else
      exec_plru(cache, mem, address, new_addr, timer, args[0], 0, data_hit);
    auto it = std::find_if(cache[address.index].get_cache_set().begin(),
                           cache[address.index].get_cache_set().end(),
                           [&address](const CacheLine &cl) {
                             return cl.get_tag() == address.tag;
                           });

    if (it != cache[address.index].get_cache_set().end()) {
      regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
          (int8_t)it->get_bytes()[address.offset];
    }
    addr += 4;
  }
  if (args[0] == "lhu") {
    int new_addr =
        regs[std::stoi(regs_map[args[3]], nullptr, 2)] + std::stoi(args[2]);
    Address address = Address(new_addr);
    if (policy == "lru")
      exec_lru(cache, mem, address, timer, args[0], 0, data_hit);
    else
      exec_plru(cache, mem, address, new_addr, timer, args[0], 0, data_hit);
    auto it = std::find_if(cache[address.index].get_cache_set().begin(),
                           cache[address.index].get_cache_set().end(),
                           [&address](const CacheLine &cl) {
                             return cl.get_tag() == address.tag;
                           });

    if (it != cache[address.index].get_cache_set().end()) {
      std::string val_str;

      val_str +=
          std::bitset<8>(it->get_bytes()[address.offset + 1]).to_string() +
          std::bitset<8>(it->get_bytes()[address.offset]).to_string();
      regs[std::stoi(regs_map[args[1]], nullptr, 2)] =
          (int16_t)std::stoll(val_str, nullptr, 16);
    }
    addr += 4;
  }
  if (args[0] == "sb" || args[0] == "sh" || args[0] == "sw") {
    int new_addr =
        regs[std::stoi(regs_map[args[3]], nullptr, 2)] + std::stoi(args[2]);
    Address address = Address(new_addr);
    if (policy == "lru")
      exec_lru(cache, mem, address, timer, args[0],
               regs[std::stoi(regs_map[args[1]], nullptr, 2)], data_hit);
    else
      exec_plru(cache, mem, address, new_addr, timer, args[0],
                regs[std::stoi(regs_map[args[1]], nullptr, 2)], data_hit);

    addr += 4;
  }
}

std::vector<int>
simulate_lru_cache(std::vector<std::vector<std::string>> &args,
                   std::vector<int> &regs,
                   std::unordered_map<std::string, std::string> &regs_map,
                   std::array<uint8_t, constants::MEM_SIZE> &mem) {
  std::vector<CacheSet> cache = std::vector<CacheSet>(constants::CACHE_SETS);
  int i = 0;
  int addr = 0x10000;
  int timer = 0;
  int instr_cnt = 0, data_cnt = 0;
  int instr_hit = 0, data_hit = 0;
  std::fill(mem.begin(), mem.end(), 0);

  while (addr < 0x10000 + 4 * args.size() && addr >= 0x10000) {
    instr_cnt++;
    Address address = Address(addr);

  
    auto it = std::find_if(cache[address.index].get_cache_set().begin(),
                           cache[address.index].get_cache_set().end(),
                           [&address](const CacheLine &cur) {
                             return cur.get_tag() == address.tag;
                           });
    if (it == cache[address.index].get_cache_set().end()) {
      auto it =
          std::min_element(cache[address.index].get_cache_set().begin(),
                           cache[address.index].get_cache_set().end(),
                           [](const CacheLine &first, const CacheLine &second) {
                             return first.get_timer() < second.get_timer();
                           });
      it->set_timer(++timer);
      it->set_tag(address.tag);
    } else {
      instr_hit++;
      it->set_timer(++timer);
    }
    int old_i = i;
    exec(args[i], regs, regs_map, addr, i);
    if (args[old_i][0] == "lb" || args[old_i][0] == "lh" ||
        args[old_i][0] == "lw" || args[old_i][0] == "lbu" ||
        args[old_i][0] == "lhu" || args[old_i][0] == "sb" ||
        args[old_i][0] == "sh" || args[old_i][0] == "sw") {
      data_instructions_exec(mem, args[old_i], regs, regs_map, cache, timer,
                             addr, data_hit, "lru");
      i++;
      data_cnt++;
    }
    if (args[old_i][0] == "ecall" || args[old_i][0] == "ebreak" ||
        args[old_i][0] == "pause" || args[old_i][0] == "fence" ||
        args[old_i][0] == "fence.tso") {
      i++;
      addr += 4;
    }
  }
  return {instr_cnt, data_cnt, instr_hit, data_hit};
}

std::vector<int>
simulate_plru_cache(std::vector<std::vector<std::string>> &args,
                    std::vector<int> &regs,
                    std::unordered_map<std::string, std::string> &regs_map,
                    std::array<uint8_t, constants::MEM_SIZE> &mem) {
  std::vector<CacheSet> cache = std::vector<CacheSet>(constants::CACHE_SETS);
  int i = 0;
  int addr = 0x10000;
  int timer = 0;
  int instr_cnt = 0, data_cnt = 0;
  int instr_hit = 0, data_hit = 0;
  std::fill(mem.begin(), mem.end(), 0);
  while (addr < 0x10000 + 4 * args.size() && addr >= 0x10000) {
    instr_cnt++;
    Address address = Address(addr);
    auto it = std::find_if(cache[address.index].get_cache_set().begin(),
                           cache[address.index].get_cache_set().end(),
                           [&address](const CacheLine &cl) {
                             return cl.get_tag() == address.tag;
                           });
    if (it == cache[address.index].get_cache_set().end()) {
      auto it = std::find_if(
          cache[address.index].get_cache_set().begin(),
          cache[address.index].get_cache_set().end(),
          [&address](const CacheLine &cl) { return cl.get_timer() == 0; });
      auto cnt_bits = std::count_if(
          cache[address.index].get_cache_set().begin(),
          cache[address.index].get_cache_set().end(),
          [&address](const CacheLine &cl) { return cl.get_timer() == 1; });
      if (cnt_bits == constants::CACHE_WAY - 1) {
        std::transform(cache[address.index].get_cache_set().begin(),
                       cache[address.index].get_cache_set().end(),
                       cache[address.index].get_cache_set().begin(),
                       [](CacheLine &cl) {
                         if (cl.get_timer() == 1) {
                           cl.set_timer(0);
                           return cl;
                         } else {
                           cl.set_timer(1);
                           return cl;
                         }
                       });
      } else {
        it->set_timer(1);
      }
      it->set_tag(address.tag);
    } else {
      instr_hit++;
      exists_line_plru(cache, address, it);
    }
    int old_i = i;
    exec(args[i], regs, regs_map, addr, i);
    if (args[old_i][0] == "lb" || args[old_i][0] == "lh" ||
        args[old_i][0] == "lw" || args[old_i][0] == "lbu" ||
        args[old_i][0] == "lhu" || args[old_i][0] == "sb" ||
        args[old_i][0] == "sh" || args[old_i][0] == "sw") {
      data_instructions_exec(mem, args[old_i], regs, regs_map, cache, timer,
                             addr, data_hit, "plru");
      i++;
      data_cnt++;
    }
    if (args[old_i][0] == "ecall" || args[old_i][0] == "ebreak" ||
        args[old_i][0] == "pause" || args[old_i][0] == "fence" ||
        args[old_i][0] == "fence.tso") {
      i++;
      addr += 4;
    }
  }
  return {instr_cnt, data_cnt, instr_hit, data_hit};
}
