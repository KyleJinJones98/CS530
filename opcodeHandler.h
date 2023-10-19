#ifndef opcodeHandler_H
#define opcodeHandler_H
#include <string>
#include <unordered_map>
#include <iostream>
#include "hexConverter.h"

//Handles operations relating to opcodes
//Does not need to be a class since there is no data we need to store

std::string encodeOpcode(std::string opcode, bool nflag, bool iflag);
bool checkOpcode(std::string opcode);
std::string encodeOpcode(std::string opcode, bool nflag, bool iflag);
int getOpcodeFormat(std::string opcode);
int getOpcodeSize(std::string opcode);
std::string normalizeOpcode(std::string opcode);


#endif