#ifndef sourceLineStruct
#define sourceLineStruct
#include <sstream>
#include <string>
#include <vector>
//used to store the contents of a line of source in assembler relevant variables
struct sourceLineStruct
{
    std::string label; //stores the name of 
    std::string operation; //stores the assembler directive or opcode
    std::string targetAddress; //stores the address the line of source targets
    std::string lineaddress; // the address of the line of source, to be assigned during pass 1

    void getLineComponents(std::string sourceLine){
    std::string word;
    std::vector<std::string> components;
    sourceLineStruct output;
    std::istringstream iss(sourceLine);
    while (std::getline(iss, word, ' ')) {
        components.push_back(word);
    }
    if(components.size() == 2){
        output.label = ""; //no label if we only have 2 components being opcode and address
        output.operation = components[0];
        output.targetAddress = components[1]; 
    }
    else if(components.size()==3){
        output.label = components[0]; 
        output.operation = components[1];
        output.targetAddress = components[2]; 
    }
    else{
        throw "Unexpected number of arguments in line of source: "+ components.size();
    }

    }
};

#endif
