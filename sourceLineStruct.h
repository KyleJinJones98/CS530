#ifndef sourceLineStruct_H
#define sourceLineStruct_H
#include <sstream>
#include <string>
#include <vector>
//used to store the contents of a line of source in assembler relevant variables
struct sourceLineStruct
{
    std::string label; //stores the name of 
    std::string operation; //stores the assembler directive or opcode
    std::string targetAddress; //stores the address the line of source targets
    std::string lineAddress; // the address of the line of source, to be assigned during pass 1

    void getLineComponents(std::string sourceLine){
    std::string word;
    std::vector<std::string> components;
    std::istringstream iss(sourceLine);
    while (std::getline(iss, word, ' ')) {
        components.push_back(word);
    }
    if(components.size() == 2){
        label = ""; //no label if we only have 2 components being opcode and address
        operation = components[0];
        targetAddress = components[1]; 
    }
    else if(components.size()==3){
        label = components[0]; 
        operation = components[1];
        targetAddress = components[2]; 
    }
    else{
        throw "Unexpected number of arguments in line of source: "+ components.size();
    }

    }
};

#endif
