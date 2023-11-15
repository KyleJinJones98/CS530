/**
 * CS 530, Fall 2023
 * 11/14/2023
 * Joseph Vue, RED ID: 820231744
 * Jake Opatz, RED ID: 826638326
 * Kyle Jones, RED ID: 819938646
 */

#include "symbolTable.h"
//add a new literal to the literalTable
//However, does not define its address, which is assumed to be defined later
void SymbolTable::addLiteral(std::string literalName, std::string literalValue){
    //need to add check literalvalue against already existing literals
    //if already in table no need to readd it
    literal newLiteral =  {literalValue, ""};
    newLiteral.insertionOrder=symNumber;
    symNumber++;
    literalTable[literalName] = newLiteral;
}

//adds a new symbol to the symboltable
void SymbolTable::addSymbol(std::string symbolName, std::string symbolValue){
    symbol newSymbol = symbol();
    newSymbol.value=symbolValue;
    newSymbol.insertionOrder=symNumber;
    symNumber++;
    symbolTable[symbolName] = newSymbol;
}

//returns the symbols definition, or the address of a literal
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
            throw AssemblyException();
        }
        return addr;
    }
        //throws an undefined symbol exception, but might be better to include line/address symbol was found at 
    catch(const std::out_of_range& e)
    {
        std::cerr << "Undefined Symbol: " <<symbolName<< std::endl;
        throw AssemblyException();
    }
}

//increments all relative symbols greater than a given address
//used when an instruction is extended
void SymbolTable::incrementAddresses(std::string modAddress){
    int addr = toDec(modAddress);
    for (auto sym : symbolTable){
        if(!sym.second.absoluteFlag&&sym.second.intValue>addr){
            symbolTable[sym.first].intValue+=1;
        }
    }
}

//returns true if a symbol or literal is in the symtab
bool SymbolTable::isSymbol(std::string symbolName){
        try
    {
        symbolTable.at(symbolName);
        return true;
    }
    catch(const std::out_of_range& e)
    {
    }

    try
    {
        literalTable.at(symbolName);
        return true;
    }
        //throws an undefined symbol exception, but might be better to include line/address symbol was found at 
    catch(const std::out_of_range& e)
    {
       return false;
    }
}

//used to get the definition of a literal
std::string SymbolTable::getLiteralValue(std::string literalName){
        try
    {
        return literalTable.at(literalName).value;
    }
        //throws an undefined symbol exception, but might be better to include line/address symbol was found at 
    catch(const std::out_of_range& e)
    {
        std::cerr << "Undefined Literal: " <<literalName<< std::endl;
        throw AssemblyException();
    }
}
std::string SymbolTable::getLiteralAddress(std::string literalName){
    try
    {
        return literalTable.at(literalName).address;
    }
        //throws an undefined symbol exception, but might be better to include line/address symbol was found at
    catch(const std::out_of_range& e)
    {

        std::cerr << "Undefined Literal: " <<literalName<< std::endl;
        throw AssemblyException();
    }
}

//returns whether the given symbol is an absolute or relative value
bool SymbolTable::isAbsolute(std::string symbolName){
    try
    {
        return symbolTable.at(symbolName).absoluteFlag;
    }
    catch(const std::out_of_range& e)
    {
    }

    //check if the name is a literal
    //if so return true since all literals are absolute values
    try
    {
        std::string addr=  literalTable.at(symbolName).address;
        return true;
    }
    //if the name is neither symbol or literal error out
    catch(const std::out_of_range& e)
    {
        std::cerr << "Undefined Symbol: " <<symbolName<< std::endl;
        throw AssemblyException();
    }
}

std::vector<std::string> SymbolTable::getAllSymbols(){
    std::vector<std::string> symbolNames;
    for (auto symbol : symbolTable){
        symbolNames.push_back(symbol.first);
    }
    return symbolNames;
}

//instantiates literals starting at the given address
void SymbolTable::instantiateLiterals(LocationCounter& locctr, std::vector<sourceLineStruct>& output)
{
    //regex is here to isolate the type and value of the literal
    //std::regex literalRegex("=[C,X]'(.*)'");
    for(auto literal : literalTable) {

        //only assign literals who have no assigned address
        if(literal.second.address==""){
        sourceLineStruct currentLiteral = sourceLineStruct();
        std::string literalDefinition = literal.second.value;

            size_t litStart = literalDefinition.find("'");
            std::string isolatedLiteral = literalDefinition.substr(litStart+1);
            isolatedLiteral.erase(isolatedLiteral.size()-1);
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
                throw AssemblyException();
            }
            //update the literaltable
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

}

//defines a symbol as being absolute or relative, and assigns the integer value that corresponds to its definition string
void SymbolTable::defineSymbol(std::string symbolName, int value, bool isAbsolute){

       symbolTable.at(symbolName).intValue = value;
       symbolTable.at(symbolName).absoluteFlag=isAbsolute;
        symbolTable.at(symbolName).isDefined=true;

}

//attempts to resolve all symbol values
//at the end of pass1 if not all symbolvalues can be resolved throws an error
void SymbolTable::resolveSymbols(bool endOfPass1){

}

//returns the resolved integer value of a symbol's defining string 
//or a literals address converted to an integer
int SymbolTable::getSymbolValueInt(std::string symbolName)
{
    try
    {
        return symbolTable.at(symbolName).intValue;
    }
    catch(const std::out_of_range& e)
    {
    }

    try
    {
        std::string addr=  literalTable.at(symbolName).address;
        if(addr==""){
            std::cerr << "Unassigned Literal: " <<symbolName<< std::endl;
            throw AssemblyException();
        }
        return toDec(addr);
    }
        //throws an undefined symbol exception, but might be better to include line/address symbol was found at 
    catch(const std::out_of_range& e)
    {
        std::cerr << "Undefined Symbol: " <<symbolName<< std::endl;
        throw AssemblyException();
    }
}

//returns true if the integer value of a symbol has been defined
//always returns true for literals 
bool SymbolTable::isDefined(std::string symbolName)
{
    try
    {
        return symbolTable.at(symbolName).isDefined;
    }
    catch(const std::out_of_range& e)
    {
    }

    try
    {
        std::string addr=  literalTable.at(symbolName).address;
        return true;
    }
        //throws an undefined symbol exception, but might be better to include line/address symbol was found at 
    catch(const std::out_of_range& e)
    {
        std::cerr << "Undefined Symbol: " <<symbolName<< std::endl;
        throw AssemblyException();
    }
}

void SymbolTable::writeTable(std::ofstream &symFile){
    //symboltable header
    symFile<< std::setw(SYM) << std::left << "Symbol"<< "  "<< std::setw(VAL) << std::left <<"Value"<< "  "<< std::setw(FLAG)<< std::left <<"Flags:"<<std::endl;
    //spacing line
    symFile<<std::left<<std::string(SYM+VAL+FLAG +6, '-')<<std::endl;

    for (auto symbol : symbolTable){
        //convert true fals absolute flag to A and R
        std::string absFlag = "R";
        if(symbol.second.absoluteFlag){
            absFlag="A";
        }
        symFile<< std::setw(SYM) << std::left <<symbol.first<< "  "<< std::setw(VAL)<< std::left <<toHex(symbol.second.intValue, 6)<< "  "<< std::setw(FLAG)<< std::left<<absFlag<<std::endl;
    }

    //spacing line between tables
    symFile<<std::endl;

    //Literal Table Head
    symFile<< std::setw(NAM) << std::left << "Name"<< "  "<< std::setw(LIT) << std::left <<"Literal"<< "  "<< std::setw(ADDR)<< std::left <<"Address:"<<std::endl;
    //spacing line
    symFile<<std::left<<std::string(NAM+LIT+ADDR +6, '-')<<std::endl;

    for (auto literal : literalTable){
        symFile<< std::setw(NAM) << std::left << literal.first<< "  "<< std::setw(LIT) << std::left <<literal.second.value<< "  "<< std::setw(ADDR)<< std::left <<literal.second.address<<std::endl;
    }
}
