#ifndef sourceLineStruct_H
#define sourceLineStruct_H
#include <sstream>
#include <string>
#include <vector>
#include<iostream>
#include <iomanip>
//used to store the contents of a line of source in assembler relevant variables
struct sourceLineStruct
{
    std::string label; //stores the name of 
    std::string operation; //stores the assembler directive or opcode
    std::string targetAddress; //stores the address the line of source targets
    std::string lineAddress; // the address of the line of source, to be assigned during pass 1
    std::string hexInstruction = "";

    //used to deconstruct a line of source and assign values
    void getLineComponents(std::string sourceLine){
    std::string word;
    std::vector<std::string> components;
    std::istringstream iss(sourceLine);
    while (std::getline(iss, word, ' ')) {
        if(word!=""){
            components.push_back(word);
        }
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
        std::cout << "Unexpected number of arguments in line of source: "+std::to_string(components.size()) +"\n";
        //throw "Unexpected number of arguments in line of source: "+ components.size() +"\n";
        exit(3);
    }

    }

    void printLine(){
        std::cout << std::setw(5) << std::left << lineAddress<< std::setw(8) << std::left << label<< std::setw(7) << std::left << operation<< std::setw(8) << std::left << targetAddress<< std::setw(8) << std::left << hexInstruction<<std::endl;
        //printf("%s %s    %s    %s          %s\n", lineAddress.c_str(), label.c_str(), operation.c_str(), targetAddress.c_str(), hexInstruction.c_str());
    }

};

#endif
