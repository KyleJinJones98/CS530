#include <string>
#include <unordered_map>
#include <iostream>
#include "hexConverter.h"

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
    auto opcodeNumber = opcodeTable.find(opcode);
    if(opcodeNumber!= opcodeTable.end()){
        return true;
    }
    //else return false    
    return false;
}

//returns the given opcode as a hex string
std::string encodeOpcode(std::string opcode, bool nflag, bool iflag){
    std::string opcodeNumber = opcodeTable[opcode];

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

//Expected output: 6D 03 20 0 1
int main(){
    std::cout<<encodeOpcode("LDS",false,true)<<std::endl;
    std::cout<<encodeOpcode("LDA",true,true)<<std::endl;
    std::cout<<encodeOpcode("MUL",false,false)<<std::endl;
    std::cout<<checkOpcode("ALU")<<std::endl;
    std::cout<<checkOpcode("MUL")<<std::endl;
}