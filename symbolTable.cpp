#include <string>
#include <unordered_map>
#include <iostream>

//handles functionality related to the symbol table including updating symbol values, getting values, and writing the symbol table to a file


struct symbol{
    std::string value;
    bool absoluteFlag; // false = relative true = absolute
    
};

std::unordered_map<std::string, symbol> symbolTable{
  };


//adds a new symbol to the symboltable
void addSymbol(std::string symbolName, std::string symbolValue, bool isAbsolute){
    symbol newSymbol = {symbolValue, isAbsolute};
    symbolTable[symbolName] = newSymbol;
}

//returns whether the given symbol is an absolute or relative value
std::string getSymbolValue(std::string symbolName){
    try
    {
        return symbolTable.at(symbolName).value;
    }
    //throws an undefined symbol exception, but might be better to include line/address symbol was found at 
    catch(const std::out_of_range& e)
    {
        std::cerr << "Undefined Symbol: " <<symbolName<< std::endl;
        exit(3);
    }
}

//returns whether the given symbol is an absolute or relative value
bool isAbsolute(std::string symbolName){
    try
    {
        return symbolTable.at(symbolName).absoluteFlag;
    }
    //throws an undefined symbol exception, but might be better to include line/address symbol was found at 
    catch(const std::out_of_range& e)
    {
        std::cerr << "Undefined Symbol: " <<symbolName<< std::endl;
        std::cerr << e.what() << std::endl;
        exit(3);
    }
    
}

//some simple error tests
int main(){
        addSymbol("Start", "00000", false);
        std::cout<<getSymbolValue("Start")<<std::endl;
        std::cout<<getSymbolValue("Star")<<std::endl;
}