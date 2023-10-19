#include "sourceLineStruct.h"
#include "locationCounter.h"
#include "opcodeHandler.h"
#include "symbolTable.h"
#include <string>
#include <vector>

//Implements the operations during the first pass of the assembler

std::vector<sourceLineStruct> pass1(std::vector<std::string> sourceLines){
    std::vector<sourceLineStruct> output;
    SymbolTable symtab;
    
    //Process first Line here! 
    sourceLineStruct firstLine;
    firstLine.getLineComponents(sourceLines[0]);
    //do error checking to ensure program is started correctly
    if(firstLine.operation!="START"){
        throw "Program not started with correct opcode: Start. \n Incorrect opcode: "+firstLine.operation;
    }
    
    //set defaults based on first line contents
    LocationCounter locctr = LocationCounter(firstLine.targetAddress);
    output.push_back(firstLine);
    //updateSymbolTable(firstline.label)

    for(int i = 1; i<sourceLines.size(); i++){
        sourceLineStruct currentLine = sourceLineStruct();
        currentLine.getLineComponents(sourceLines[i]); //extract the line components from the current source line
        currentLine.lineAddress = locctr.getLocationCounter();//assign address to current line of source

        if(currentLine.label != "" && currentLine.targetAddress.find("=")== std::string::npos){ //check if label is defined and is not a literal
            //addSymbol(currentLine.label,currentLine.lineAddress, true);
        }
        else if(currentLine.targetAddress.find("=")!= std::string::npos){//check if a literal was defined
            //addLiteral(currentLine.label, currentLine.targetAddress);
        } 

        //checkOpcode(currentLine.operation)
        //getOpcodeSize(currentLine.targetAddress)
        //checkDirective(currentLine.operation) //check for + flag
        //if true handleDirective(currentLine.operation, currentLine.targetAddress, locctr)

        //increment locctr
    }
    return output;
}

