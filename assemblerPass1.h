#ifndef ASSEMBLERPASS1_H
#define ASSEMBLERPASS1_H

#include "sourceLineStruct.h"
#include "locationCounter.h"
#include "opcodeHandler.h"
#include "symbolTable.h"
#include <string>
#include <vector>
#include <iostream>
#include "assemblerDirectivesPass1.h"
#include "expressionParsing.h"


std::vector<sourceLineStruct> pass1(std::vector<std::string> sourceLines, SymbolTable& symtab);

#endif
