/**
 * CS 530, Fall 2023
 * 11/14/2023
 * Joseph Vue, RED ID: 820231744
 * Jake Opatz, RED ID: 826638326
 * Kyle Jones, RED ID: 819938646
 */

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
