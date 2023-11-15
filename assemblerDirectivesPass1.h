/**
 * CS 530, Fall 2023
 * 11/14/2023
 * Joseph Vue, RED ID: 820231744
 * Jake Opatz, RED ID: 826638326
 * Kyle Jones, RED ID: 819938646
 */

#ifndef assemblerDirectivesPass1_H
#define assemblerDirectivesPass1_H

#include <string>
#include <vector>
#include <unordered_map>
#include "locationCounter.h"
#include "symbolTable.h"
#include "sourceLineStruct.h"
#include "hexConverter.h"
#include "expressionParsing.h"

//Directives to Handle:
//ResB ResW Byte Word
// Ltorg Org EQU
//Possibly Use?

// We don't need to do anything for Base

//Handles assembler directives during pass1 of the Assembler
int getDirectiveSize(SymbolTable symtab, std::string operation, std::string targetAddress);
bool checkDirective(std::string operation);
void handleDirective(std::string label, std::string operation, std::string targetAddress, LocationCounter& locctr, SymbolTable& symtab, std::vector<sourceLineStruct>& output);


#endif
