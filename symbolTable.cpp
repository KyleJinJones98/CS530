#include "symbolTable.h"
//add a new literal to the literalTable
//However, does not define its address, which is assumed to be defined later
void SymbolTable::addLiteral(std::string literalName, std::string literalValue){
    literal newLiteral =  {literalValue, ""};
    literalTable[literalName] = newLiteral;
}

//Adds the address that the assembler automatically assigned to a literal to its value in the table
void SymbolTable::addLiteralAddress(std::string literalName, std::string literalAddress){
    if(literalTable.at(literalName).address!=""){
        std::cerr << "Double address assignment to literal: " <<literalName<< std::endl;
    }
    literalTable.at(literalName).address=literalAddress;
}

//adds a new symbol to the symboltable
void SymbolTable::addSymbol(std::string symbolName, std::string symbolValue, bool isAbsolute){
    symbol newSymbol = {symbolValue, isAbsolute};
    symbolTable[symbolName] = newSymbol;
}

//returns whether the given symbol is an absolute or relative value
std::string SymbolTable::getSymbolValue(std::string symbolName){
    try
    {
        return symbolTable.at(symbolName).value;
    }
    catch(const std::out_of_range& e)
    {
    }

    try
    {
        std::string addr=  literalTable.at(symbolName).address;
        if(addr==""){
            std::cerr << "Unassigned Literal: " <<symbolName<< std::endl;
            exit(3);
        }
        return addr;
    }
        //throws an undefined symbol exception, but might be better to include line/address symbol was found at 
    catch(const std::out_of_range& e)
    {
        std::cerr << "Undefined Symbol: " <<symbolName<< std::endl;
        exit(3);
    }
}

//used when creating a literal pool
std::string SymbolTable::getLiteralValue(std::string literalName){
        try
    {
        return literalTable.at(literalName).value;
    }
        //throws an undefined symbol exception, but might be better to include line/address symbol was found at 
    catch(const std::out_of_range& e)
    {
        std::cerr << "Undefined Literal: " <<literalName<< std::endl;
        exit(3);
    }
}

//returns whether the given symbol is an absolute or relative value
bool SymbolTable::isAbsolute(std::string symbolName){
    try
    {
        return symbolTable.at(symbolName).absoluteFlag;
    }
    //throws an undefined symbol exception, but might be better to include line/address symbol was found at 
    catch(const std::out_of_range& e)
    {
        std::cerr << "Undefined Symbol: " <<symbolName<< std::endl;
        exit(3);
    }
    
}
