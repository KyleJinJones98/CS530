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
#include <vector>

//handles functionality related to the symbol table including updating symbol values, getting values, and writing the symbol table to a file


struct symbol{
    std::string value;
    bool absoluteFlag; // false = relative true = absolute
    int intValue;
    bool isDefined=false;
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
  //used to add a new literal to the literal table
  void addLiteral(std::string literalName, std::string literalValue);

  //used to add a new symbol to the symtab
  void addSymbol(std::string symbolName, std::string symbolValue);

  //used to get the address of a symbol or literal
  std::string getSymbolValue(std::string symbolName);

  //used to access the immediate value of a literal
  std::string getLiteralValue(std::string literalName);

    //used to access the address of a literal
    std::string getLiteralAddress(std::string literalName);

  //used to check if a symbol is absolute or not
  bool isAbsolute(std::string symbolName);

  //used to assign locations to all the literals currently waiting for assignment in the literal table
  void instantiateLiterals(LocationCounter& locctr, std::vector<sourceLineStruct>& output);

  //used to check if a string is a valid symbol or literal
  bool isSymbol(std::string symbolName);

  //attempts to resolve all symbol values
  //if there are symbols that are unable to be resolved and this is the end of Pass 1 we throw an error
  void resolveSymbols(bool endOfPass1);

  //used to give a symbol its integer value
  void defineSymbol(std::string symbolName, int value, bool isAbsolute); 

  //returns the resolved integer value of a symbol, or the integer value of 
  int getSymbolValueInt(std::string symbolName);

  //returns whether the resolved integer value of a symbol has been defined
  bool isDefined(std::string symbolName);

  std::vector<std::string> getAllSymbols();

};

#endif