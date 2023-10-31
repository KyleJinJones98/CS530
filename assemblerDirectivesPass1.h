#ifndef assemblerDirectivesPass1_H
#define assemblerDirectivesPass1_H

#include <string>
#include <vector>
#include <unordered_map>
#include "locationCounter.h"
#include "symbolTable.h"
#include "sourceLineStruct.h"
#include "hexConverter.h"

//Directives to Handle:
//ResB ResW Byte Word
// Ltorg Org EQU
//Possibly Use?

// We don't need to do anything for Base

//Handles assembler directives during pass1 of the Assembler
int getDirectiveSize(std::string operation, std::string targetAddress);
bool checkDirective(std::string operation);
void handleDirective(std::string operation, std::string targetAddress, LocationCounter& locctr, SymbolTable& symtab, std::vector<sourceLineStruct>& output);


#endif