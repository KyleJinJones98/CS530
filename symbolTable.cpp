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

//instantiates literals starting at the given address
void SymbolTable::instantiateLiterals(LocationCounter& locctr, std::vector<sourceLineStruct>& output)
{
    //regex is here to isolate the type and value of the literal
    std::regex literalRegex("=[C,X]'(.*)'");
    for(auto literal : literalTable) {
        sourceLineStruct currentLiteral = sourceLineStruct();
        std::string literalDefinition = literal.second.value;
        std::smatch isolatedValue;
        std::regex_search(literalDefinition,isolatedValue,literalRegex);
            if(isolatedValue.size()!=2){
                std::cout<<"Error Parsing Literal: "+literalDefinition<<std::endl;
                exit(3);
            }

            std::string isolatedLiteral = isolatedValue.str(1);
            //if the literal is a charstring we need to convert to ascii and then to hex first
            if(literalDefinition[1]=='C'){
                isolatedLiteral = toHex(isolatedLiteral,6);
            }
            //if the literal is hexstring then its value does not need to be further modified
            else if(literalDefinition[1]=='X'){
                //just make sure we have the appropriate number of preceeding 0's
               isolatedLiteral= toHex(toDec(isolatedLiteral),6);
            }
            else{
                std::cout<<"Error Parsing Literal: "+literalDefinition<<std::endl;
                exit(3);
            }
            //update the literaltable
            literalTable[literal.first].value=isolatedLiteral;
            literalTable[literal.first].address = locctr.getLocationCounter();
            //finish literal initialization
            currentLiteral.lineAddress = locctr.getLocationCounter();
            currentLiteral.label = '*';
            currentLiteral.hexInstruction = isolatedLiteral;
            currentLiteral.operation= literalDefinition;
            //add literal to sourcelines and increment locctr
            output.push_back(currentLiteral);
            //we'll assume that each literal is 1 word in length
            locctr.incrementLocationCounter(3);
    } 

}
