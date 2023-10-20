#include "opcodeHandler.h"
//Handles functionality related to the opcode table including checking for valid opcodes, and encoding opcodes

//TODO ADD FULL OPCODETABLE
//
//TODO ADD FULL OPCODETABLE

//opcode table is our hard coded hashmap of opcodes and their corresponding integer values
std::unordered_map<std::string, std::string> opcodeTable{
    {"MUL","20"},
    {"ADD","18"},
    {"LDA","00"},
    {"LDS","6C"}
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
    
    std::string opcodeNumber = opcodeTable[normalizeOpcode(opcode)];

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
    //Stub need to convert opcodes to structs to track format as well
    return 1;
}

//gets rid of the + at the beginning of opcodes to they can be properly searched
std::string normalizeOpcode(std::string opcode){
    if(opcode[0]=='+'){
        return opcode.substr(1);
    }
    return opcode;
}