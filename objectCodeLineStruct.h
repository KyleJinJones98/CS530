//
// Created by Jacob Opatz   on 11/1/23.
//

#ifndef CS530_MAIN_OBJECTCODELINESTRUCT_H
#define CS530_MAIN_OBJECTCODELINESTRUCT_H
using namespace std;
#include "sourceLineStruct.h"
#include "locationCounter.h"
#include "opcodeHandler.h"
#include "symbolTable.h"

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include<iostream>
#include <iomanip>
//TODO: make actual assemble function

struct formatOneObjCode{
    std::string byte;
    std::string getObjCode() {
         return byte;
    };
};

struct formatTwoObjCode {
    std::string opcode;
    std::string reg1;
    std::string reg2;
    std::string getObjCode() {
        return opcode + reg1 + reg2;
    };
};
struct formatThreeAndFourObjCode {
    std::string opcode;
    std::string n = "0";
    std::string i = "0";
    std::string x = "0";
    std::string b = "0";
    std::string p = "0";
    std::string e = "0";
   std::string address;

    std::string getObjCode() {
        int xbpeBit = 0;
        if(x == "1") {
            xbpeBit += 8;
        }
        if (b == "1") {
            xbpeBit += 4;
        }
        if (p == "1") {
            xbpeBit += 2;
        }
        if (e == "1") {
            xbpeBit += 1;
        }

        return opcode + toHex(xbpeBit,1) + address;
    };
};
string assemble(sourceLineStruct instruction, SymbolTable pass1symTab, bool hasX) {
    //TODO: finish getopcodeformat in opcodeHandler.cpp
    int insFormat = getOpcodeFormat(instruction.operation);
    //TODO: delete this before push
    insFormat = 3;
    SymbolTable symTab = pass1symTab;


    if (insFormat == 1) {
        //TODO: return type 1 ins form in hex representation
        formatOneObjCode hexCode = formatOneObjCode();
        string opcode = instruction.operation;
        string operand = instruction.targetAddress;

        if (operand[0] == '#') {
            // Immediate addressing
            operand.erase(0, 1);  // Remove the '#' symbol
            // Validate and convert the immediate value to a suitable format.
            if (symTab.isSymbol(targetAddress)) {
                targetAddress = symTab.getSymbolValue(targetAddress);
            }
            hexCode.address = targetAddress;

            hexCode.byte = instruction.targetAddress;  // Immediate value as hex representation.
        }
        else if (operand[0] == '=') {
            // Literal addressing
            operand.erase(0, 1); // Remove the '=' symbol

        }
        else {
            // Handle other cases, if needed, for the specific addressing modes of your assembly language.
            hexCode.byte = "0";  // Use a default hex value.
        }
        return hexCode.getObjCode();
    }
    else if (insFormat == 2) {
        //TODO: return type 2 ins form in hex representation
        formatTwoObjCode hexCode = formatTwoObjCode();

        string opcode = instruction.operation;
        string operand = instruction.targetAddress;

        if (operand[0] == '#') {
            // Immediate addressing
            operand.erase(0, 1);  // Remove the '#' symbol
            // May want to validate and convert the immediate value to a suitable format.

            hexCode.opcode = opcode;
            hexCode.reg1 = "01";  // Replace with the actual register value.
            hexCode.reg2 = "00";  // You can set reg2 to a default value, e.g., "00".
        }
        else if (operand[0] == '@') {
            // Indirect addressing
            operand.erase(0, 1);  // Remove the '@' symbol
            // May need to look up the value in the symbol table based on the operand.

            hexCode.opcode = opcode;
            hexCode.reg1 = "01";
            hexCode.reg2 = "00";
        }
        else if (operand[0] == '=') {
            // Literal addressing
            operand.erase(0, 1);  // Remove the '=' symbol
            // Handle literals here.

            hexCode.opcode = opcode;
            hexCode.reg1 = "R1";  // Replace with the actual register value.
            hexCode.reg2 = "R2";  // Replace with the actual register value.
        }
        else {
            // Handle other cases, if needed, for the specific addressing modes.

            hexCode.opcode = opcode;
            hexCode.reg1 = "00";
            hexCode.reg2 = "00";
        }

        return hexCode.getObjCode();
    }
    //if format 3 or 4 instruction
    else {
        formatThreeAndFourObjCode hexCode = formatThreeAndFourObjCode();
        //assume simple addressing, will change if operand is imediate or indirect
        hexCode.n = "1";

        hexCode.i = "1";
        hexCode.p = "1";
        string opcode = instruction.operation;
        string currentProgLoc = instruction.lineAddress;
        string targetAddress = instruction.targetAddress;
        string indexAmount = "";
        int displacement;

        //set bits
        //if operand is immediate
        if (targetAddress[0] == '#') {
            targetAddress.erase(0,1);

            if (symTab.isSymbol(targetAddress)) {
                targetAddress = symTab.getSymbolValue(targetAddress);
                hexCode.p = "1";
            }
            std::stringstream stream;
            stream <<std::setfill('0') << std::setw(3) << hexCode.address;
            hexCode.address = stream.str();
            hexCode.n = '0';
            hexCode.i = '1';
            hexCode.p = '0';

        }
        //if operand is using indirect addressing
        if (targetAddress[0] == '@') {
            targetAddress.erase(0,1);

            if (symTab.isSymbol(targetAddress)) {
                targetAddress = symTab.getSymbolValue(targetAddress);
                hexCode.p = '1';
            }
            hexCode.address = targetAddress;
            hexCode.n = '1';
            hexCode.i = '0';
            hexCode.opcode = encodeOpcode(opcode, hexCode.n == "1", hexCode.i == "1");
            return hexCode.getObjCode();
        }
        //check for indexed addressing, get indexAmount
        for( int i = 0; i < targetAddress.length(); i ++) {
            if (targetAddress[i] == ',') {
                hexCode.x = '1';
                while (i < targetAddress.length()) {
                    indexAmount.append(&targetAddress[i]);
                    i++;
                };
            }
        }
        //check if base or pc relative will be used, set b and p accordingly
        if (instruction.operation[0] == '+') {
            hexCode.e = "1";
        }
        //if not using extended format, check if displacement will fit in format 4
        if (hexCode.e != "1") {
            if (hexCode.p == "1") {
                displacement = toDec(targetAddress) - (toDec(currentProgLoc) + 3);
                //TODO: check if I should use base, if base is in symtab
                if ((-2048 <= displacement) && (2047 >= displacement)) {
                    hexCode.p = "1";

                } else {
                    hexCode.e = "1";


                }
            }
        }

        //bits are set, now calculate address field from target address
        if (hexCode.p == "1") {


            hexCode.address = toHex(displacement,3);
            if (displacement < 0) {
                hexCode.address = hexCode.address.erase(0, hexCode.address.length() - 3);
            }
        }
            //else, if using imediate addressing
        else if (hexCode.e == "1") {
            hexCode.address = toHex(toDec(targetAddress), 5);

        }
        if (hasX) {

            hexCode.x = "1";
        };
        //TODO: add base relative address calculation
        //get opcode + n + i (encodeOpcode adds these for us)
        hexCode.opcode = encodeOpcode(opcode,hexCode.n=="1", hexCode.i=="1");

        return hexCode.getObjCode();
    };
};
#endif
