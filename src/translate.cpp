#include "translate.h"

std::set<std::string> cmd = {
    "lui",  "auipc",  "jal",   "jalr", "beq",   "bne",   "blt",    "bge",
    "bltu", "bgeu",   "lb",    "lh",   "lw",    "lbu",   "lhu",    "sb",
    "sh",   "sw",     "addi",  "slti", "sltiu", "xori",  "ori",    "andi",
    "slli", "srli",   "srai",  "add",  "sub",   "sll",   "slt",    "sltu",
    "xor",  "srl",    "sra",   "or",   "and",   "ecall", "ebreak", "mul",
    "mulh", "mulhsu", "mulhu", "div",  "divu",  "rem",   "remu"};
std::unordered_map<std::string, std::string> cmd_type = {
    {"lui", "U"},   {"auipc", "U"},  {"jal", "J"},    {"jalr", "I"},
    {"beq", "B"},   {"bne", "B"},    {"blt", "B"},    {"bge", "B"},
    {"bltu", "B"},  {"bgeu", "B"},   {"lb", "I"},     {"lh", "I"},
    {"lw", "I"},    {"lbu", "I"},    {"lhu", "I"},    {"sb", "S"},
    {"sh", "S"},    {"sw", "S"},     {"addi", "I"},   {"slti", "I"},
    {"sltiu", "I"}, {"xori", "I"},   {"ori", "I"},    {"andi", "I"},
    {"slli", "I"},  {"srli", "I"},   {"srai", "I"},   {"add", "R"},
    {"sub", "R"},   {"sll", "R"},    {"slt", "R"},    {"sltu", "R"},
    {"xor", "R"},   {"srl", "R"},    {"sra", "R"},    {"or", "R"},
    {"and", "R"},   {"ecall", "I"},  {"ebreak", "I"}, {"mul", "R"},
    {"mulh", "R"},  {"mulhsu", "R"}, {"mulhu", "R"},  {"div", "R"},
    {"divu", "R"},  {"rem", "R"},    {"remu", "R"}};
std::unordered_map<std::string, std::string> cmd_opcode = {
    {"lui", "0110111"},   {"auipc", "0010111"}, {"jal", "1101111"},
    {"jalr", "1100111"},  {"beq", "1100011"},   {"bne", "1100011"},
    {"blt", "1100011"},   {"bge", "1100011"},   {"bltu", "1100011"},
    {"bgeu", "1100011"},  {"lb", "0000011"},    {"lh", "0000011"},
    {"lw", "0000011"},    {"lbu", "0000011"},   {"lhu", "0000011"},
    {"sb", "0100011"},    {"sh", "0100011"},    {"sw", "0100011"},
    {"addi", "0010011"},  {"slti", "0010011"},  {"sltiu", "0010011"},
    {"xori", "0010011"},  {"ori", "0010011"},   {"andi", "0010011"},
    {"slli", "0010011"},  {"srli", "0010011"},  {"srai", "0010011"},
    {"add", "0110011"},   {"sub", "0110011"},   {"sll", "0110011"},
    {"slt", "0110011"},   {"sltu", "0110011"},  {"xor", "0110011"},
    {"srl", "0110011"},   {"sra", "0110011"},   {"or", "0110011"},
    {"and", "0110011"},   {"ecall", "1110011"}, {"ebreak", "1110011"},
    {"mul", "0110011"},   {"mulh", "0110011"},  {"mulhsu", "0110011"},
    {"mulhu", "0110011"}, {"div", "0110011"},   {"divu", "0110011"},
    {"rem", "0110011"},   {"remu", "0110011"}};
std::unordered_map<std::string, std::string> cmd_funct3 = {
    {"jalr", "000"},   {"beq", "000"},   {"bne", "001"},   {"blt", "100"},
    {"bge", "101"},    {"bltu", "110"},  {"bgeu", "111"},  {"lb", "000"},
    {"lh", "001"},     {"lw", "010"},    {"lbu", "100"},   {"lhu", "101"},
    {"sb", "000"},     {"sh", "001"},    {"sw", "010"},    {"addi", "000"},
    {"slti", "010"},   {"sltiu", "011"}, {"xori", "100"},  {"ori", "110"},
    {"andi", "111"},   {"slli", "001"},  {"srli", "101"},  {"srai", "101"},
    {"add", "000"},    {"sub", "000"},   {"sll", "001"},   {"slt", "010"},
    {"sltu", "011"},   {"xor", "100"},   {"srl", "101"},   {"sra", "101"},
    {"or", "110"},     {"and", "111"},   {"mul", "000"},   {"mulh", "001"},
    {"mulhsu", "010"}, {"mulhu", "011"}, {"div", "100"},   {"divu", "101"},
    {"rem", "110"},    {"remu", "111"},  {"ecall", "000"}, {"ebreak", "000"}};
std::unordered_map<std::string, std::string> cmd_funct7 = {
    {"slli", "0000000"},   {"srli", "0000000"},  {"srai", "0100000"},
    {"add", "0000000"},    {"sub", "0100000"},   {"sll", "0000000"},
    {"slt", "0000000"},    {"sltu", "0000000"},  {"xor", "0000000"},
    {"srl", "0000000"},    {"sra", "0100000"},   {"or", "0000000"},
    {"and", "0000000"},    {"mul", "0000001"},   {"mulh", "0000001"},
    {"mulhsu", "0000001"}, {"mulhu", "0000001"}, {"div", "0000001"},
    {"divu", "0000001"},   {"rem", "0000001"},   {"remu", "0000001"}};
std::unordered_map<std::string, std::string> regs = {
    {"zero", "00000"}, {"ra", "00001"}, {"sp", "00010"}, {"gp", "00011"},
    {"tp", "00100"},   {"t0", "00101"}, {"t1", "00110"}, {"t2", "00111"},
    {"s0", "01000"},   {"fp", "01000"}, {"s1", "01001"}, {"a0", "01010"},
    {"a1", "01011"},   {"a2", "01100"}, {"a3", "01101"}, {"a4", "01110"},
    {"a5", "01111"},   {"a6", "10000"}, {"a7", "10001"}, {"s2", "10010"},
    {"s3", "10011"},   {"s4", "10100"}, {"s5", "10101"}, {"s6", "10110"},
    {"s7", "10111"},   {"s8", "11000"}, {"s9", "11001"}, {"s10", "11010"},
    {"s11", "11011"},  {"t3", "11100"}, {"t4", "11101"}, {"t5", "11110"},
    {"t6", "11111"}};

void write_bytes(std::string &code, std::ofstream &out) {
  uint8_t code0 = (uint8_t)std::bitset<8>(code.substr(0, 8)).to_ulong();
  uint8_t code1 = (uint8_t)std::bitset<8>(code.substr(8, 8)).to_ulong();
  uint8_t code2 = (uint8_t)std::bitset<8>(code.substr(16, 8)).to_ulong();
  uint8_t code3 = (uint8_t)std::bitset<8>(code.substr(24, 8)).to_ulong();
  out << code3 << code2 << code1 << code0;
}
void translate(std::vector<std::vector<std::string>> &commands, std::ofstream &out) {
  for (std::size_t i = 0; i < commands.size(); ++i) {
    if (commands[i][0] == "fence") {
      std::unordered_map<std::string, std::string> fence_args = {
          {"i", "1000"},    {"o", "0100"},    {"r", "0010"},
          {"w", "0001"},    {"io", "1100"},   {"oi", "1100"},
          {"ir", "1010"},   {"ri", "1010"},   {"iw", "1001"},
          {"wi", "1001"},   {"or", "0110"},   {"ro", "0110"},
          {"ow", "0101"},   {"wo", "0101"},   {"rw", "0011"},
          {"wr", "0011"},   {"ior", "1110"},  {"iro", "1110"},
          {"oir", "1110"},  {"ori", "1110"},  {"rio", "1110"},
          {"roi", "1110"},  {"iow", "1101"},  {"iwo", "1101"},
          {"oiw", "1101"},  {"owi", "1101"},  {"wio", "1101"},
          {"woi", "1101"},  {"irw", "1011"},  {"iwr", "1011"},
          {"riw", "1011"},  {"rwi", "1011"},  {"wir", "1011"},
          {"wri", "1011"},  {"orw", "0111"},  {"owr", "0111"},
          {"row", "0111"},  {"rwo", "0111"},  {"wor", "0111"},
          {"wro", "0111"},  {"iorw", "1111"}, {"iowr", "1111"},
          {"irwo", "1111"}, {"irow", "1111"}, {"iwor", "1111"},
          {"iwro", "1111"}, {"oiwr", "1111"}, {"oirw", "1111"},
          {"owir", "1111"}, {"owri", "1111"}, {"orwi", "1111"},
          {"oriw", "1111"}, {"riow", "1111"}, {"riwo", "1111"},
          {"roiw", "1111"}, {"rowi", "1111"}, {"rwio", "1111"},
          {"rwoi", "1111"}, {"wior", "1111"}, {"wiro", "1111"},
          {"woir", "1111"}, {"wori", "1111"}, {"wroi", "1111"},
          {"wrio", "1111"}};
      std::string code = std::string(4, '0') + fence_args[commands[i][1]] +
                         fence_args[commands[i][2]] + std::string(16, '0') +
                         std::string(4, '1');
      write_bytes(code, out);
    }
    if (commands[i][0] == "fence.tso") {
      std::string code =
          "100000110011" + std::string(16, '0') + std::string(4, '1');
      write_bytes(code, out);
    }
    if (commands[i][0] == "pause") {
      std::string code = std::string(7, '0') + std::string(1, '1') +
                         std::string(20, '0') + std::string(4, '1');
      write_bytes(code, out);
    }
    if (cmd_type[commands[i][0]] == "R") {
      std::string code = cmd_funct7[commands[i][0]] + regs[commands[i][3]] +
                         regs[commands[i][2]] + cmd_funct3[commands[i][0]] +
                         regs[commands[i][1]] + cmd_opcode[commands[i][0]];
      write_bytes(code, out);
    }
    if (cmd_type[commands[i][0]] == "I" && commands[i][0] != "lb" &&
        commands[i][0] != "lh" && commands[i][0] != "lw" &&
        commands[i][0] != "lhu" && commands[i][0] != "lbu" &&
        commands[i][0] != "jalr") {
      std::string code;
      if (commands[i][3].substr(0, 2) == "0x") {
        std::stringstream ss;
        std::string num = commands[i][3].substr(2);
        int val;
        ss << std::hex << num;
        ss >> val;
        val %= (1 << 12);
        if (val >= (1 << 11))
          val -= 1 << 12;
        else if (val < -(1 << 11))
          val += 1 << 12;
        commands[i][3] = std::to_string(val);
        std::string imm = std::bitset<12>(val).to_string();
        if (commands[i][0] == "slli" || commands[i][0] == "srli")
          imm = imm.replace(0, 7, std::string(7, '0'));
        if (commands[i][0] == "srai")
          imm = imm.replace(0, 7, "0100000");
        code = imm + regs[commands[i][2]] + cmd_funct3[commands[i][0]] +
               regs[commands[i][1]] + cmd_opcode[commands[i][0]];
      } else {
        int val = std::stoi(commands[i][3]);
        val %= (1 << 12);
        if (val >= (1 << 11))
          val -= 1 << 12;
        else if (val < -(1 << 11))
          val += 1 << 12;
        commands[i][3] = std::to_string(val);
        std::string imm = std::bitset<12>(val).to_string();
        if (commands[i][0] == "slli" || commands[i][0] == "srli")
          imm = imm.replace(0, 7, std::string(7, '0'));
        if (commands[i][0] == "srai")
          imm = imm.replace(0, 7, "0100000");
        code = imm + regs[commands[i][2]] + cmd_funct3[commands[i][0]] +
               regs[commands[i][1]] + cmd_opcode[commands[i][0]];
      }
      write_bytes(code, out);
    }
    if (commands[i][0] == "lb" || commands[i][0] == "lh" ||
        commands[i][0] == "lw" || commands[i][0] == "lbu" ||
        commands[i][0] == "lhu") {
      std::string code;
      if (commands[i][2].substr(0, 2) == "0x") {
        std::stringstream ss;
        std::string num = commands[i][2].substr(2);
        int val;
        ss << std::hex << num;
        ss >> val;
        val %= (1 << 12);
        if (val >= (1 << 11))
          val -= 1 << 12;
        else if (val < -(1 << 11))
          val += 1 << 12;
        commands[i][2] = std::to_string(val);
        code = std::bitset<12>(val).to_string() + regs[commands[i][3]] +
               cmd_funct3[commands[i][0]] + regs[commands[i][1]] +
               cmd_opcode[commands[i][0]];
      } else {
        int val = std::stoi(commands[i][2]);
        val %= (1 << 12);
        if (val >= (1 << 11))
          val -= 1 << 12;
        else if (val < -(1 << 11))
          val += 1 << 12;
        commands[i][2] = std::to_string(val);
        code = std::bitset<12>(val).to_string() + regs[commands[i][3]] +
               cmd_funct3[commands[i][0]] + regs[commands[i][1]] +
               cmd_opcode[commands[i][0]];
      }
      write_bytes(code, out);
    }
    if (commands[i][0] == "jalr") {
      std::string code;
      if (commands[i][3].substr(0, 2) == "0x") {
        std::stringstream ss;
        std::string num = commands[i][3].substr(2);
        int val;
        ss << std::hex << num;
        ss >> val;
        val %= (1 << 12);
        if (val >= (1 << 11))
          val -= 1 << 12;
        else if (val < -(1 << 11))
          val += 1 << 12;
        commands[i][3] = std::to_string(val);
        code = std::bitset<12>(val).to_string() + regs[commands[i][2]] +
               cmd_funct3[commands[i][0]] + regs[commands[i][1]] +
               cmd_opcode[commands[i][0]];
      } else {
        int val = std::stoi(commands[i][3]);
        val %= (1 << 12);
        if (val >= (1 << 11))
          val -= 1 << 12;
        else if (val < -(1 << 11))
          val += 1 << 12;
        commands[i][3] = std::to_string(val);
        code = std::bitset<12>(val).to_string() + regs[commands[i][2]] +
               cmd_funct3[commands[i][0]] + regs[commands[i][1]] +
               cmd_opcode[commands[i][0]];
      }
      write_bytes(code, out);
    }
    if (cmd_type[commands[i][0]] == "S") {
      std::string code;
      if (commands[i][2].substr(0, 2) == "0x") {
        std::stringstream ss;
        std::string num = commands[i][2].substr(2);
        int val;
        ss << std::hex << num;
        ss >> val;
        val %= (1 << 12);
        if (val >= (1 << 11))
          val -= 1 << 12;
        else if (val < -(1 << 11))
          val += 1 << 12;
        commands[i][2] = std::to_string(val);
        std::string imm = std::bitset<12>(val).to_string();
        code = imm.substr(0, 7) + regs[commands[i][1]] + regs[commands[i][3]] +
               cmd_funct3[commands[i][0]] + imm.substr(7) +
               cmd_opcode[commands[i][0]];
      } else {
        int val = std::stoi(commands[i][2]);
        val %= (1 << 12);
        if (val >= (1 << 11))
          val -= 1 << 12;
        else if (val < -(1 << 11))
          val += 1 << 12;
        commands[i][2] = std::to_string(val);
        std::string imm = std::bitset<12>(val).to_string();
        code = imm.substr(0, 7) + regs[commands[i][1]] + regs[commands[i][3]] +
               cmd_funct3[commands[i][0]] + imm.substr(7) +
               cmd_opcode[commands[i][0]];
      }
      write_bytes(code, out);
    }
    if (cmd_type[commands[i][0]] == "B") {
      std::string code;
      if (commands[i][3].substr(0, 2) == "0x") {
        std::stringstream ss;
        std::string num = commands[i][3].substr(2);
        int val;
        ss << std::hex << num;
        ss >> val;
        val %= (1 << 13);
        if (val >= (1 << 12))
          val -= 1 << 13;
        else if (val < -(1 << 12))
          val += 1 << 13;
        commands[i][3] = std::to_string(val);
        std::string imm = std::bitset<13>(val).to_string();
        imm = imm.substr(0, imm.size() - 1);
        code = imm.substr(0, 1) + imm.substr(2, 6) + regs[commands[i][2]] +
               regs[commands[i][1]] + cmd_funct3[commands[i][0]] +
               imm.substr(8) + imm.substr(1, 1) + cmd_opcode[commands[i][0]];
      } else {
        int num = std::stoi(commands[i][3]);
        int val = num;
        val %= (1 << 13);
        if (val >= (1 << 12))
          val -= 1 << 13;
        else if (val < -(1 << 12))
          val += 1 << 13;
        commands[i][3] = std::to_string(val);
        std::string imm = std::bitset<13>(num).to_string();
        imm = imm.substr(0, imm.size() - 1);
        code = imm.substr(0, 1) + imm.substr(2, 6) + regs[commands[i][2]] +
               regs[commands[i][1]] + cmd_funct3[commands[i][0]] +
               imm.substr(8) + imm.substr(1, 1) + cmd_opcode[commands[i][0]];
      }
      write_bytes(code, out);
    }
    if (cmd_type[commands[i][0]] == "U") {
      std::string code;
      if (commands[i][2].substr(0, 2) == "0x") {
        std::stringstream ss;
        std::string num = commands[i][2].substr(2);
        int val;
        ss << std::hex << num;
        ss >> val;
        val %= (1 << 20);
        if (val >= (1 << 19))
          val -= 1 << 20;
        else if (val < -(1 << 19))
          val += 1 << 20;
        commands[i][2] = std::to_string(val);
        std::string imm = std::bitset<20>(val).to_string();
        code = imm + regs[commands[i][1]] + cmd_opcode[commands[i][0]];
      } else {
        int val = std::stoi(commands[i][2]);
        val %= (1 << 20);
        if (val >= (1 << 19))
          val -= 1 << 20;
        else if (val < -(1 << 19))
          val += 1 << 20;
        commands[i][2] = std::to_string(val);
        std::string imm =
            std::bitset<20>(std::stoi(commands[i][2])).to_string();
        code = imm + regs[commands[i][1]] + cmd_opcode[commands[i][0]];
      }
      write_bytes(code, out);
    }
    if (cmd_type[commands[i][0]] == "J") {
      std::string code;
      if (commands[i][2].substr(0, 2) == "0x") {
        std::stringstream ss;
        std::string num = commands[i][2].substr(2);
        int32_t val;
        ss << std::hex << num;
        ss >> val;
        val %= (1 << 21);
        if (val >= (1 << 20))
          val -= 1 << 21;
        else if (val < -(1 << 20))
          val += 1 << 21;
        commands[i][2] = std::to_string(val);
        std::string imm = std::bitset<21>(val).to_string();
        imm = imm.substr(0, imm.size() - 1);
        code = imm.substr(0, 1) + imm.substr(10) + imm.substr(9, 1) +
               imm.substr(1, 8) + regs[commands[i][1]] +
               cmd_opcode[commands[i][0]];
      } else {
        int32_t val = std::stoi(commands[i][2]);
        val %= (1 << 21);
        if (val >= (1 << 20))
          val -= 1 << 21;
        else if (val < -(1 << 20))
          val += 1 << 21;
        std::string imm = std::bitset<21>(val).to_string();
        imm = imm.substr(0, imm.size() - 1);
        code = imm.substr(0, 1) + imm.substr(10) + imm.substr(9, 1) +
               imm.substr(1, 8) + regs[commands[i][1]] +
               cmd_opcode[commands[i][0]];
      }
      write_bytes(code, out);
    }
  }
}
