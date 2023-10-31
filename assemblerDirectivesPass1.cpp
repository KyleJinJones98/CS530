#include "assemblerDirectivesPass1.h"



enum Directive{RESB, RESW, BYTE, WORD, BASE, LTORG, ORG, EQU};
std::unordered_map<std::string, Directive> directiveTable{
    {"RESB", Directive::RESB},
    {"RESW", Directive::RESW},
    {"BYTE", Directive::BYTE},
    {"WORD", Directive::WORD},
    {"BASE", Directive::BASE},
    {"LTORG", Directive::LTORG},
    {"ORG", Directive::ORG},
    {"EQU", Directive::EQU}
  };


bool checkDirective(std::string operation)
{
    //if directive in directive table return true
    auto directiveEnum = directiveTable.find(operation);
    if(directiveEnum!= directiveTable.end()){
        return true;
    }
    //else return false    
    return false;
}

void handleDirective(std::string operation, std::string targetAddress, LocationCounter& locctr, SymbolTable& symtab, std::vector<sourceLineStruct>& output){
    Directive directiveEnum = directiveTable[operation];
    switch (directiveEnum)
    {
    //we tell the symbol table to instantiate literals with the given location counter
    case Directive::LTORG:
        symtab.instantiateLiterals(locctr,output);
    //we reset the location counter to the given address
    case Directive::ORG:
        if(symtab.isSymbol(targetAddress)){
            locctr.setLocationCounter(toDec(symtab.getSymbolValue(targetAddress)));
        }
        else{
            locctr.setLocationCounter(std::stoi(targetAddress));
        }
    default:
        break;
    }
}

//returns the given directive's size
//if the directive does not take up space returns 0
int getDirectiveSize(SymbolTable symtab, std::string operation, std::string targetAddress)
{
    Directive directiveEnum = directiveTable[operation];
    int size;
    switch (directiveEnum)
    {
    case Directive::RESB:
        if(symtab.isSymbol(targetAddress)){
            size = toDec(symtab.getSymbolValue(targetAddress));
        }
        else{
            size = std::stoi(targetAddress);
        }
        return size;
    case Directive::RESW:
        if(symtab.isSymbol(targetAddress)){
            size = toDec(symtab.getSymbolValue(targetAddress));
        }
        else{
            size = std::stoi(targetAddress);
        }
        return size*3;
    case Directive::BYTE:
        return 1;
    case Directive::WORD:
        return 3;
    default:
        return 0;
    }
}
