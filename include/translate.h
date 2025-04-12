#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <bitset>
#include <sstream>
void translate(std::vector<std::vector<std::string>> &, std::ofstream &);
void write_bytes(std::string &, std::ofstream &);

extern std::set<std::string> cmd;
extern std::unordered_map<std::string, std::string> cmd_type;
extern std::unordered_map<std::string, std::string> cmd_opcode;
extern std::unordered_map<std::string, std::string> cmd_funct3;
extern std::unordered_map<std::string, std::string> cmd_funct7;
extern std::unordered_map<std::string, std::string> regs;