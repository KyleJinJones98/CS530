/**
 * CS 530, Fall 2023
 * 11/14/2023
 * Joseph Vue, RED ID: 820231744
 * Jake Opatz, RED ID: 826638326
 * Kyle Jones, RED ID: 819938646
 */

//
// Created by Jacob Opatz   on 10/31/23.
//
#include "assemblerPass2.h"
#include "assemblerPass1.h"

std::vector<sourceLineStruct> pass2(std::vector<sourceLineStruct> P1listingFile, SymbolTable pass1SymTab) {
    std::string baseLoc;
    bool hasBase = false;
    bool hasX = false;
    int opcodeFormat;
    int numForceExtended = 0;
    int objectCodeLength = 100;

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


    //iterate through instructions
    for (unsigned int i = startingLine; i<(listingFile.size()-1); i++) {
        //get next line
        objectCodeLength = 100;
        currentLine = listingFile[i];
        if(currentLine.lineAddress != "" && numForceExtended != 0) {
            listingFile[i].lineAddress = toHex((toDec(currentLine.lineAddress) + (numForceExtended)), 4);
            if(symtab.isSymbol(currentLine.label)) {
                symtab.symbolTable.at(currentLine.label).value = toHex((toDec(symtab.symbolTable.at(currentLine.label).value) + 1), 4);
            }
        }
        hasX = false;
        opcodeFormat = getOpcodeFormat(currentLine.operation);
        //if not comment line
        if(currentLine.label != ".") {

            // if opcode = "BYTE" or "WORD"
            //TODO: process other directives, use assemblerDirectivesPass1.cpp
            if(currentLine.operation == "START") {
                continue;
            }
            else if (currentLine.operation == "BYTE") {
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
            else if (currentLine.operation == "BASE") {
                hasBase = true;
                baseLoc = symtab.getSymbolValue(currentLine.targetAddress);
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
                    if(currentLine.targetAddress[currentLine.targetAddress.length() - 1] == 'X' && getOpcodeFormat(currentLine.operation)!=2) {

                        for(unsigned int i = 0; i < currentLine.targetAddress.length() ; i++) {
                            if (currentLine.targetAddress[i] == ',') {
                                hasX = true;
                                currentLine.targetAddress.erase(i, currentLine.targetAddress.length());
                                break;
                            }
                        }

                    }
                    //store symbol value in operand field
                    if(symtab.isSymbol(currentLine.targetAddress)){
                        currentLine.targetAddress = symtab.getSymbolValue(currentLine.targetAddress);
                    }
                    

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




                if (opcodeFormat == 3) {
                    objectCodeLength = 6;
                }
                tempObjectCode = assemble(currentLine, symtab, hasX, hasBase, baseLoc);
                if(tempObjectCode.length() > objectCodeLength) {
                    numForceExtended += 1;
                    listingFile[i].operation = "+" + currentLine.operation;


                }

            };

            //add to listing file
            listingFile[i].hexInstruction = tempObjectCode;



        }

    }
    if(numForceExtended != 0) {
        listingFile = pass2(listingFile, symtab);
    }
    return listingFile;

}







