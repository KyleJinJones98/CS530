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
    std::string hexInstruction = "";//the translated operation in hex

    //used to deconstruct a line of source and assign values
    void getLineComponents(std::string sourceLine){
    //detect inline comments
    size_t commentStart =sourceLine.find(".");
    if(commentStart !=std::string::npos){
        operation = sourceLine.substr(commentStart+1);
        label =".";
        return; //we are finished if the line was just an inline comment

    }

    std::string cleanedLine = sourceLine;
    //remove comments past the end of argument space
    if(cleanedLine.size()>45){
        cleanedLine =sourceLine.substr(0,45);
    }

    std::string word;
    std::vector<std::string> components;
    std::istringstream iss(cleanedLine);
    while (std::getline(iss, word, ' ')) {
        if(word!=""){
            components.push_back(word);
        }
    }

    //if there was only 2 arguments, then we do not have a label just an opcode/directive and address
    if(components.size() == 2){
        label = "";
        operation = components[0];
        targetAddress = components[1]; 
        }
    //otherwise we have a label, operation, and address
    else if(components.size()==3){
        label = components[0]; 
        operation = components[1];
        targetAddress = components[2]; 
        }
    //if this wasn't a comment line and we have more than 3 arguments then there was some error in the line
    else{
        std::cout << "Unexpected number of arguments in line of source: "+std::to_string(components.size()) +"\n";
        //throw "Unexpected number of arguments in line of source: "+ components.size() +"\n";
        exit(3);
        }
    }


    void printLine(){
        if(label!="."){
            std::cout << std::setw(5) << std::left << lineAddress<< std::setw(8) << std::left << label<< std::setw(7) << std::left << operation<< std::setw(8) << std::left << targetAddress<< std::setw(8) << std::left << hexInstruction<<std::endl;
        }
        else{
            std::cout << std::setw(5) << std::left << label<< std::left <<operation<<std::endl;
        }
    }

};

#endif
