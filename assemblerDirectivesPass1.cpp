/**
 * Joseph Vue, RED ID: 820231744
 */

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

void handleDirective(std::string label, std::string operation, std::string targetAddress, LocationCounter& locctr, SymbolTable& symtab, std::vector<sourceLineStruct>& output){
    Directive directiveEnum = directiveTable[operation];
    switch (directiveEnum)
    {
    //we tell the symbol table to instantiate literals with the given location counter
    case Directive::LTORG:
        symtab.instantiateLiterals(locctr,output);
    //we reset the location counter to the given address
    case Directive::ORG:
        locctr.setLocationCounter(parseExpression(targetAddress,symtab).value);
    case Directive::EQU:
        symtab.addSymbol(label, targetAddress);
    case Directive::BYTE:
        if(label!=""){
            symtab.addSymbol(label, targetAddress);
        }
    case Directive::WORD:
        if(label!=""){
            symtab.addSymbol(label, targetAddress);
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
    switch (directiveEnum)
    {
    case Directive::RESB:
        return parseExpression(targetAddress,symtab).value;
    case Directive::RESW:
        return  parseExpression(targetAddress,symtab).value*3;
    case Directive::BYTE:
        return 1;
    case Directive::WORD:
        return 3;
    default:
        return 0;
    }
}
