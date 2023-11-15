/**
 * CS 530, Fall 2023
 * 11/14/2023
 * Joseph Vue, RED ID: 820231744
 * Jake Opatz, RED ID: 826638326
 * Kyle Jones, RED ID: 819938646
 */

#include "opcodeHandler.h"
//Handles functionality related to the opcode table including checking for valid opcodes, and encoding opcodes

//opcode table is our hard coded hashmap of opcodes and their corresponding hexvalues and instruction formats
//A value of 
std::unordered_map<std::string, std::tuple<std::string, int>> opcodeTable{
    {"ADD",std::tuple<std::string, int>{"18",3}},
    {"ADDF",std::tuple<std::string, int>{"58",3}},
    {"ADDR",std::tuple<std::string, int>{"90",2}},
    {"AND",std::tuple<std::string, int>{"40",3}},
    {"CLEAR",std::tuple<std::string, int>{"B4",2}},
    {"COMP",std::tuple<std::string, int>{"28",3}},
    {"COMPF",std::tuple<std::string, int>{"88",3}},
    {"COMPR",std::tuple<std::string, int>{"A0",2}},
    {"DIV",std::tuple<std::string, int>{"24",3}},
    {"DIVF",std::tuple<std::string, int>{"64",3}},
    {"DIVR",std::tuple<std::string, int>{"9C",2}},
    {"FIX",std::tuple<std::string, int>{"C4",1}},
    {"FLOAT",std::tuple<std::string, int>{"C0",1}},
    {"HIO",std::tuple<std::string, int>{"F4",1}},
    {"J",std::tuple<std::string, int>{"3C",3}},
    {"JEQ",std::tuple<std::string, int>{"30",3}},
    {"JGT",std::tuple<std::string, int>{"34",3}},
    {"JLT",std::tuple<std::string, int>{"38",3}},
    {"JSUB",std::tuple<std::string, int>{"48",3}},
    {"LDA",std::tuple<std::string, int>{"00",3}},
    {"LDB",std::tuple<std::string, int>{"68",3}},
    {"LDCH",std::tuple<std::string, int>{"50",3}},
    {"LDF",std::tuple<std::string, int>{"70",3}},
    {"LDL",std::tuple<std::string, int>{"08",3}},
    {"LDS",std::tuple<std::string, int>{"6C",3}},
    {"LDT",std::tuple<std::string, int>{"74",3}},
    {"LDX",std::tuple<std::string, int>{"04",3}},
    {"LPS",std::tuple<std::string, int>{"D0",3}},
    {"MUL",std::tuple<std::string, int>{"20",3}},
    {"MULF",std::tuple<std::string, int>{"60",3}},
    {"MULR",std::tuple<std::string, int>{"98",2}},
    {"NORM",std::tuple<std::string, int>{"C8",1}},
    {"OR",std::tuple<std::string, int>{"44",3}},
    {"RD",std::tuple<std::string, int>{"D8",3}},
    {"RMO",std::tuple<std::string, int>{"AC",2}},
    {"RSUB",std::tuple<std::string, int>{"4C",3}},
    {"SHIFTL",std::tuple<std::string, int>{"A4",2}},
    {"SHIFTR",std::tuple<std::string, int>{"A8",3}},
    {"SIO",std::tuple<std::string, int>{"F0",1}},
    {"SSK",std::tuple<std::string, int>{"EC",3}},
    {"STA",std::tuple<std::string, int>{"0C",3}},
    {"STB",std::tuple<std::string, int>{"78",3}},
    {"STCH",std::tuple<std::string, int>{"54",3}},
    {"STF",std::tuple<std::string, int>{"80",3}},
    {"STI",std::tuple<std::string, int>{"D4",3}},
    {"STL",std::tuple<std::string, int>{"14",3}},
    {"STS",std::tuple<std::string, int>{"7C",3}},
    {"STSW",std::tuple<std::string, int>{"E8",3}},
    {"STT",std::tuple<std::string, int>{"84",3}},
    {"STX",std::tuple<std::string, int>{"10",3}},
    {"SUB",std::tuple<std::string, int>{"1C",3}},
    {"SUBF",std::tuple<std::string, int>{"5C",3}},
    {"SUBR",std::tuple<std::string, int>{"94",2}},
    {"SVC",std::tuple<std::string, int>{"B0",2}},
    {"TD",std::tuple<std::string, int>{"E0",3}},
    {"TIO",std::tuple<std::string, int>{"F8",1}},
    {"TIX",std::tuple<std::string, int>{"2C",3}},
    {"TIXR",std::tuple<std::string, int>{"B8",2}},
    {"WD",std::tuple<std::string, int>{"DC",3}}
  };
  
//checks if a string is a valid opcode
bool checkOpcode(std::string opcode){
    //if opcode in opcode table return true
    auto opcodeNumber = opcodeTable.find(normalizeOpcode(opcode));
    if(opcodeNumber!= opcodeTable.end()){
        return true;
    }
    //else return false    
    return false;
}

//returns the given opcode as a hex string
std::string encodeOpcode(std::string opcode, bool nflag, bool iflag){
    
    std::string opcodeNumber = std::get<0>(opcodeTable[normalizeOpcode(opcode)]);

    //add to our opcode integer here to set n and i flags
    //if n should be set we add +2
    if(nflag){
        opcodeNumber=toHex(toDec(opcodeNumber)+2,2);
    }
    //if i should be set we add +1
    if(iflag){
        opcodeNumber=toHex(toDec(opcodeNumber)+1,2);
    }

    return opcodeNumber;
}

//returns the number of Bytes used up by the opcode
int getOpcodeSize(std::string opcode){
    //if it is extended return 4, otherwise we return 3
    if(opcode[0]=='+'){
        return 4;
    }
    return 3;
}

int getOpcodeFormat(std::string opcode){
    int opcodeFormat = std::get<1>(opcodeTable[normalizeOpcode(opcode)]);
    //for format 3 instructions check if this instruction was extended
    if(opcodeFormat==3){
            if(opcode[0]=='+'){
                return 4;
            }
            return 3;
    }
    //else just return format
    else{
        return opcodeFormat;
    }
}

//gets rid of the + at the beginning of opcodes to they can be properly searched
std::string normalizeOpcode(std::string opcode){
    if(opcode[0]=='+'){
        return opcode.substr(1);
    }
    return opcode;
}
