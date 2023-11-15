/**
 * CS 530, Fall 2023
 * 11/14/2023
 * Joseph Vue, RED ID: 820231744
 */
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
#include <iostream>
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

inline
string assemble(sourceLineStruct instruction, SymbolTable pass1symTab, bool hasX, bool hasBase, std::string baseLoc) {
    //TODO: finish getopcodeformat in opcodeHandler.cpp
    string opcode = instruction.operation;
    int insFormat = getOpcodeFormat(opcode);
    SymbolTable symTab = pass1symTab;
    //int insFormat = 3;
    
    if (insFormat == 1) {
        //TODO: return type 1 ins form in hex representation
        formatOneObjCode hexCode = formatOneObjCode();
        
        checkOpcode(opcode);
        return hexCode.getObjCode();
    }
    else if (insFormat == 2) {
        //TODO: return type 2 ins form in hex representation
        formatTwoObjCode hexCode = formatTwoObjCode(); 
        string reg1, reg2, comma, reg1Temp, reg2Temp;
        
        //to extract register information from the read instruction
        std::istringstream iss(opcode);
        if (iss >> opcode >> reg1Temp >> comma >> reg2Temp)
        {
            //remove commas from register strings
            reg1 = reg1Temp;
            reg2 = reg2Temp;
            reg1.erase(std::remove(reg1.begin(), reg1.end(), ','), reg1.end());
            reg2.erase(std::remove(reg2.begin(), reg2.end(), ','), reg2.end());
        }

        //create the format 2 object code
        hexCode.opcode = opcode;
        hexCode.reg1 = reg1;
        hexCode.reg2 = reg2;

        return hexCode.getObjCode();
    }
    //if format 3 or 4 instruction
    else {
        formatThreeAndFourObjCode hexCode = formatThreeAndFourObjCode();
        //assume simple addressing, will change if operand is imediate or indirect
        hexCode.n = "1";
        hexCode.i = "1";
        string opcode = instruction.operation;
        string currentProgLoc = instruction.lineAddress;
        string targetAddress = instruction.targetAddress;
        string indexAmount = "";
        string BASE ="";
        int displacement;
        bool isImmediate = false;


        //set bits
        if (targetAddress == "") {
            hexCode.opcode = encodeOpcode(opcode,false, false);
            hexCode.address = "000";
            return hexCode.getObjCode();
        }
        if (hasX) {
            hexCode.x = "1";
        }

        //if operand is immediate
        if (targetAddress[0] == '#') {
            targetAddress.erase(0,1);
            if (symTab.isSymbol(targetAddress)) {
                targetAddress = symTab.getSymbolValue(targetAddress);

            }
            else {
                isImmediate = true;
            }
            hexCode.address = targetAddress;
            hexCode.n = "0";
            hexCode.i = "1";
        }
        //if operand is using indirect addressing
        if (targetAddress[0] == '@') {
            targetAddress.erase(0,1);

            if (symTab.isSymbol(targetAddress)) {
                targetAddress = symTab.getSymbolValue(targetAddress);
            }
            hexCode.address = targetAddress;
            hexCode.n = "1";
            hexCode.i = "0";
            hexCode.opcode = encodeOpcode(opcode, hexCode.n == "1", hexCode.i == "1");
            return hexCode.getObjCode();
        }

        //check if base or pc relative will be used, set b and p accordingly
        if (instruction.operation[0] == '+') {
            hexCode.e = "1";
        }
        //if not using extended format

        if ((hexCode.e != "1") &&(!isImmediate)) {
            displacement = toDec(targetAddress)- toDec(currentProgLoc);
            //TODO: check if I should use base, if base is in symtab
            if ((-2048 <= displacement) && (2047 >= displacement)) {
                hexCode.p = "1";

            }
            else if(hasBase) {
                displacement = toDec(targetAddress) - toDec(baseLoc);
                if ((displacement >= 0) && (displacement < 4095)) {
                    hexCode.b = "1";
                    hexCode.p = "0";
                }
                else {
                    hexCode.b = "0";
                    hexCode.i = "1";
                    hexCode.p = "0";
                    hexCode.e = "1";
                    hexCode.n = "1";
                }
            }
        }

        //bits are set, now calculate address field from target address
        if (hexCode.p == "1") {

            hexCode.address = toHex(displacement,3);
        }
        else if (hexCode.b == "1") {
            hexCode.address = toHex(displacement, 3);
        }
        else {
            hexCode.address = targetAddress;
        }
        //else, if using imediate addressing
         if (hexCode.e == "1") {

            hexCode.address = toHex(toDec(hexCode.address), 4);

        }
        if (isImmediate) {
            if(hexCode.e == "1") {
                hexCode.address = toHex(toDec(targetAddress), 5);
            }
            else {
                hexCode.address = toHex(toDec(targetAddress), 3);
            }
        }
        if (hexCode.address[0] == 'F') {
            if (hexCode.address.length() > 3) {
                hexCode.address.erase(0, hexCode.address.length()-3);
            }
        }
        //TODO: add base relative address calculation
        //get opcode + n + i (encodeOpcode adds these for us)
        hexCode.opcode = encodeOpcode(opcode, hexCode.n=="1", hexCode.i=="1");

        return hexCode.getObjCode();
    };
};
#endif
