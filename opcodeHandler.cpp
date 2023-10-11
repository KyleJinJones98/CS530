#include <string>
#include <unordered_map>
#include <sstream>

//TODO ADD FULL OPCODETABLE
//
//TODO ADD FULL OPCODETABLE

//opcode table is our hard coded hashmap of opcodes and their corresponding integer values
std::unordered_map<std::string, int> opcodeTable{
    {"MUL",20},
    {"ADD",18}
    {"LDA",00}
  };
  
//checks if a string is a valid opcode
bool checkOpcode(string opcode){
    //if opcode in opcode table return true
    auto opcodeNumber = opcodeTable.find(opcode);
    if(opcodeNumber!= opcodeTable.end()){
        return true;
    }
    //else return false    
    return false;
}

//returns the given opcode as a hex string
string encodeOpcode(string opcode, bool nflag, bool iflag){
    int opcodeNumber = opcodeTable[opcode];

    //add to our opcode integer here to set n and i flags
    //if n should be set we add +2
    if(nflag){
        opcodeNumber+=2;
    }
    //if i should be set we add +1
    if(iflag){
        opcodeNumber+=1;
    }

    std::stringstream strstream;
    strstream<<std::setfill('0') << std::setw(2) <<std::hex << opcodeNumber; 
    //return the converted hex string
    return ( strstream.str() );
}