#include "sourceLineStruct.h"
#include "locationCounter.h"
#include "opcodeHandler.h"
#include "symbolTable.h"
#include <string>
#include <vector>
#include <iostream>

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
    firstLine.lineAddress = locctr.getLocationCounter();
    output.push_back(firstLine);
    symtab.addSymbol(firstLine.label, firstLine.lineAddress, true);

    for(int i = 1; i<sourceLines.size(); i++){
        sourceLineStruct currentLine = sourceLineStruct();
        currentLine.getLineComponents(sourceLines[i]); //extract the line components from the current source line
        currentLine.lineAddress = locctr.getLocationCounter();//assign address to current line of source

        if(currentLine.label != "" && currentLine.targetAddress.find("=")== std::string::npos){ //check if label is defined and is not a literal
            symtab.addSymbol(currentLine.label,currentLine.lineAddress, true);
        }
        else if(currentLine.targetAddress.find("=")!= std::string::npos){//check if a literal was defined
            symtab.addLiteral(currentLine.label, currentLine.targetAddress);
        } 

        //if the instruction is an opcode, we can just account for its size and move on
        if(checkOpcode(currentLine.operation)){
            int bytes = getOpcodeSize(currentLine.operation);
            locctr.incrementLocationCounter(bytes);
        }
        //check and handle directive here
        else if(false){
            //if true handleDirective(currentLine.operation, currentLine.targetAddress, locctr)

            //increment locctr if directive requires it
        }
        else{
            throw "Unregocnized command: "+ currentLine.operation+ " at line: "+ std::to_string(i)+"\n";
        }
    }
    return output;
}

int main(){
    std::cout<<"TEST"<<std::endl;
}

