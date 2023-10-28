#ifndef assemblerDirectivePass1_H
#define assemblerDirectivePass1_H

#include <string>
#include <vector>
#include <unordered_map>
#include "locationCounter.h"
#include "symbolTable.h"
#include "sourceLineStruct.h"

//Directives to Handle:
//ResB ResW Byte Word
// Ltorg Org EQU
//Possibly Use?

// We don't need to do anything for Base

//Handles assembler directives during pass1 of the Assembler
bool isDirective(std::string operation);
int getDirectiveSize(std::string operation);


#endif