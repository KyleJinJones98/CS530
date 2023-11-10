#ifndef expressionParsing_H
#define expressionParsing_H

#include <string>
#include "symbolTable.h"

//used for resolving addition, subtraction, multiplication and division with symbols, and integers
//Does not handle Parentheses. However, parentheses can be functionally used by storing the parentheses operands inside of a symbol
//e.g (5-2)*3 can be processed by storing MYSYM EQU 5-2 and then writing the expression MYSYM*3
//This is acceptable in all but the most complex equations
int parseExpression(std::string expression, SymbolTable symtab);

int parseExpression(std::string expression, SymbolTable symtab, int depth);

#endif