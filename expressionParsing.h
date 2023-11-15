/**
 * CS 530, Fall 2023
 * 11/14/2023
 * Joseph Vue, RED ID: 820231744
 * Jake Opatz, RED ID: 826638326
 * Kyle Jones, RED ID: 819938646
 */

#ifndef expressionParsing_H
#define expressionParsing_H

#include <string>
#include "symbolTable.h"
#include <iostream>
#include <stack>
#include <string>
#include <queue>
#include "assemblerException.h"
//used for resolving addition, subtraction, multiplication and division with symbols, and integers
//Assumes all operands are either Symbols/Literals or integer strings

struct Operand{
    //integer value of the operand
    int value;
    //absolute is indicated by 0
    //relative is indicated by 1
    //expression is invalid if relatives do not cancel back to 0 or 1
    int isAbsolute =0;
    bool getAbsoluteFlag(){
        return isAbsolute==0;
    }
}; 

//Does not handle Parentheses. However, parentheses can be functionally used by storing the parentheses operands inside of a symbol
//e.g (5-2)*3 can be processed by storing MYSYM EQU 5-2 and then writing the expression MYSYM*3
//This is acceptable in all but the most complex equations
Operand parseExpression(std::string expression, SymbolTable symtab);

//int parseExpression(std::string expression, SymbolTable symtab, int depth);

#endif
