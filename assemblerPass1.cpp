#include "sourceLineStruct.h"
#include "locationCounter.h"
#include "opcodeHandler.h"
#include "symbolTable.h"
#include <string>
#include <vector>
#include <iostream>
#include "assemblerDirectivesPass1.h"

//Implements the operations during the first pass of the assembler

std::vector<sourceLineStruct> pass1(std::vector<std::string> sourceLines, SymbolTable& symtab){
    std::vector<sourceLineStruct> output;
    
    //Process first Line here! 
    sourceLineStruct firstLine;
    firstLine.getLineComponents(sourceLines[0]);
    //do error checking to ensure program is started correctly
    if(firstLine.operation!="START"){
        std::cout<<"Program not started with correct opcode: Start. \n Incorrect opcode: "+firstLine.operation + "\n";
       //throw "Program not started with correct opcode: Start. \n Incorrect opcode: "+firstLine.operation + "\n";
       exit(3);
    }
    
    //set defaults based on first line contents
    LocationCounter locctr = LocationCounter(firstLine.targetAddress);
    firstLine.lineAddress = locctr.getLocationCounter();
    output.push_back(firstLine);
    symtab.addSymbol(firstLine.label, firstLine.lineAddress, true);

    for(unsigned int i = 1; i<(sourceLines.size()-1); i++){
        sourceLineStruct currentLine = sourceLineStruct();
        currentLine.getLineComponents(sourceLines[i]); //extract the line components from the current source line
        currentLine.lineAddress = locctr.getLocationCounter();//assign address to current line of source
        //append the proccessed line struct
        output.push_back(currentLine);

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
        else if(checkDirective(currentLine.operation)){
            //if true handleDirective(currentLine.operation, currentLine.targetAddress, locctr)
            handleDirective(currentLine.operation, currentLine.targetAddress, locctr, symtab, output);
            //increment locctr if directive requires it
            int bytes = getDirectiveSize(symtab,currentLine.operation, currentLine.targetAddress);
            locctr.incrementLocationCounter(bytes);
        }
        else{
            std::cout<<"Unregocnized command: "+ currentLine.operation+ " at line: "+ std::to_string(i)+"\n";
            //throw "Unregocnized command: "+ currentLine.operation+ " at line: "+ std::to_string(i)+"\n";
            exit(3);
        }


    }

    //once all lines have been processed we may need to resolve symbol values

    //As well as assign any unassigned literals, we would do this by "adding" a line for each one
    symtab.instantiateLiterals(locctr,output);
    //e.g for the example we would add a sourcelinestruct with the values
    //line address = 0FC6 label =*      opcode  =C'EOF' and hexinstruction = 454F46           

    //process the last line which should have the value of end
    sourceLineStruct endLine;
    endLine.getLineComponents(sourceLines[sourceLines.size()-1]);
    //do error checking to ensure program is started correctly
    if(endLine.operation!="END"){
        std::cout<<"Program not started with correct opcode: END. \n Incorrect opcode: "+endLine.operation + "\n";
       //throw "Program not started with correct opcode: Start. \n Incorrect opcode: "+firstLine.operation + "\n";
       exit(3);
    }
    endLine.lineAddress=locctr.getLocationCounter();
    output.push_back(endLine);
    
    return output;
}

int main(){
    SymbolTable symtab;
    std::vector<std::string> testLines = {"SUM      START   0","FIRST    LDX    #0","LDA    #0", "+LDB    #TABLE2  ", "MYLIT    LDA    =C'E'", "LIT    LDA    =C'EOF'",
    "COUNT    RESW    5", "    ORG    FIRST","END     FIRST"};
    std::vector<sourceLineStruct> testOutput = pass1(testLines,symtab);
    std::cout<<"TEST"<<std::endl;
    for (unsigned int i=0; i<testOutput.size(); i++){
        testOutput[i].printLine();
    }
}

