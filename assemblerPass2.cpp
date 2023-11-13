//
// Created by Jacob Opatz   on 10/31/23.
//
#include "assemblerPass2.h"

std::vector<sourceLineStruct> pass2(std::vector<sourceLineStruct> P1listingFile, SymbolTable pass1SymTab) {


    SymbolTable symtab = pass1SymTab;
    std::vector<sourceLineStruct> listingFile = P1listingFile;
    //first line of source file
    sourceLineStruct firstLine = listingFile[0];
    //first line of our object code

    int startingLine = 0;
    while(firstLine.label=="."){
        startingLine++;
        firstLine = listingFile[startingLine];
    }


    //write first line
    //listingFile.push_back(firstLine);

    //initialize text record


    std::string operandAddress;
    std::string tempObjectCode;

    sourceLineStruct currentLine = sourceLineStruct();
    bool hasX = false;

    //iterate through instructions
    for (int i = startingLine; currentLine.operation != "END"; i++) {
        //get next line

        currentLine = listingFile[i];
        //if not comment line
        if(currentLine.label != ".") {

            // if opcode = "BYTE" or "WORD"
            //TODO: process other directives, use assemblerDirectivesPass1.cpp
            if (currentLine.operation == "BYTE") {
                //convert constant to object code
                tempObjectCode = currentLine.targetAddress;
                listingFile[i].hexInstruction = tempObjectCode;
                continue;
            }
            else if (currentLine.operation == "WORD") {

                tempObjectCode = toHex(currentLine.targetAddress, 6);
                listingFile[i].hexInstruction = tempObjectCode;

                continue;
            }
            if (checkDirective(currentLine.operation)) {

                continue;
            }
            if( currentLine.label == "*") {
                tempObjectCode = currentLine.hexInstruction;
            }
                //if opcode not byte or word, check opcode table for operation
            else if(checkOpcode(currentLine.operation)) {

                //if symbol in operand field
                if((currentLine.targetAddress[0] >= 64) && (currentLine.targetAddress[0] <= 122 )) {

                    //check if target address includes a comma
                    if(currentLine.targetAddress[currentLine.targetAddress.length() - 1] == 'X') {

                        for(unsigned int i = 0; i < currentLine.targetAddress.length() ; i++) {
                            if (currentLine.targetAddress[i] == ',') {
                                hasX = true;
                                currentLine.targetAddress.erase(i, currentLine.targetAddress.length());
                                break;
                            }
                        }

                    }
                    //store symbol value in operand field
                    currentLine.targetAddress = symtab.getSymbolValue(currentLine.targetAddress);

                }

                else if (currentLine.targetAddress[0] == '='){
                    if (currentLine.label != "") {
                        currentLine.targetAddress = symtab.getLiteralAddress(currentLine.label);
                    }
                    else{
                        currentLine.targetAddress = symtab.getLiteralAddress(currentLine.targetAddress);
                    }
                }

                else {
                    //FIXME: throw error here, unless # or @
                    operandAddress = "000000";
                };
                //FIXME: finish assemble function in objectCodeLine.h - Jacob
                tempObjectCode = assemble(currentLine, symtab, hasX);


            };

            //add to listing file
            listingFile[i].hexInstruction = tempObjectCode;



        }

    }

    return listingFile;

}







