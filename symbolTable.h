#ifndef symbolTable_H
#define symbolTable_H

#include <string>
#include <unordered_map>
#include <iostream>
#include "sourceLineStruct.h"
#include <vector>
#include "locationCounter.h"
#include <regex>
#include <iostream>
#include "hexConverter.h"

//handles functionality related to the symbol table including updating symbol values, getting values, and writing the symbol table to a file


struct symbol{
    std::string value;
    bool absoluteFlag; // false = relative true = absolute
};

struct literal{
    std:: string value;
    std:: string address;
};


class SymbolTable{
    //tracks symbols in the source code
    private:
    std::unordered_map<std::string, symbol> symbolTable{
    };

    //tracks literals in the source code
    std::unordered_map<std::string, literal> literalTable{
    };
public:
  void addLiteral(std::string literalName, std::string literalValue);
  void addLiteralAddress(std::string literalName, std::string literalAddress);
  void addSymbol(std::string symbolName, std::string symbolValue, bool isAbsolute);
  std::string getSymbolValue(std::string symbolName);
  std::string getLiteralValue(std::string literalName);
  bool isAbsolute(std::string symbolName);
  void instantiateLiterals(LocationCounter locctr, std::vector<sourceLineStruct> output);

};

#endif