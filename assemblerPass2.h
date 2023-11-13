#ifndef ASSEMBLERPASS2_H
#define ASSEMBLERPASS2_H

#include "sourceLineStruct.h"
#include "locationCounter.h"
#include "opcodeHandler.h"
#include "symbolTable.h"
#include "assemblerDirectivesPass1.h"
#include "objectCodeLineStruct.h"
#include <string>
#include <vector>
#include <iostream>

std::vector<sourceLineStruct> pass2(std::vector<sourceLineStruct> P1listingFile, SymbolTable pass1SymTab); 

#endif