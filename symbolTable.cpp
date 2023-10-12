#include <string>
#include <unordered_map>
#include <iostream>

//handles functionality related to the symbol table including updating symbol values, getting values, and writing the symbol table to a file


struct symbol{
    std::string value;
    bool absoluteFlag; // false = relative true = absolute
    
};

struct literal{
    std:: string value;
    std:: string address;
};

std::unordered_map<std::string, symbol> symbolTable{
  };

std::unordered_map<std::string, literal> literalTable{
  };

void addLiteral(std::string literalName, std::string literalValue){
    literal newLiteral =  {literalValue, ""};
    literalTable[literalName] = newLiteral;
}

void addLiteralAddress(std::string literalName, std::string literalAddress){
    if(literalTable.at(literalName).address!=""){
        std::cerr << "Double address assignment to literal: " <<literalName<< std::endl;
    }
    literalTable.at(literalName).address=literalAddress;
}

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
std::string getLiteralValue(std::string literalName){
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
bool isAbsolute(std::string symbolName){
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

//some simple error tests
//Expected Results: 00000, 0, 00FE, Undefined Symbol: Star 
//As well as exit code =3 due to exiting early
int main(){
        addSymbol("Start", "00000", false);
        std::cout<<getSymbolValue("Start")<<std::endl;
        std::cout<<isAbsolute("Start")<<std::endl;
        addLiteral("MyLit", "=C'EOF'" );
        addLiteralAddress("MyLit", "00FE");
        std::cout<<getSymbolValue("MyLit")<<std::endl;
        std::cout<<getSymbolValue("Star")<<std::endl;
        std::cout<<getSymbolValue("MyLit")<<std::endl;
}