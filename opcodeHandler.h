#ifndef opcodeHandler_H
#define opcodeHandler_H
#include <string>
#include <unordered_map>
#include <iostream>
#include "hexConverter.h"
#include <tuple>

//Handles operations relating to opcodes
//Does not need to be a class since there is no data we need to store

//converts a given opcode into hex
std::string encodeOpcode(std::string opcode, bool nflag, bool iflag);

//checks if an opcode is in the table
bool checkOpcode(std::string opcode);

//returns the format of the opcode
int getOpcodeFormat(std::string opcode);

//returns the number of bytes used by the opcode 3 or 4
int getOpcodeSize(std::string opcode);

//removes + from the beginning of opcodes
std::string normalizeOpcode(std::string opcode);


#endif