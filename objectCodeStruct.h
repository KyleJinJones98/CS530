/**
 * CS 530, Fall 2023
 * 11/14/2023
 * Joseph Vue, RED ID: 820231744
 * Jake Opatz, RED ID: 826638326
 * Kyle Jones, RED ID: 819938646
 */

#ifndef OBJECTCODESTRUCT_H
#define OBJECTCODESTRUCT_H

#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include "hexConverter.h"
//Defines the Structs used for creating an object file
//each struct has its own writeLine function for writing the objectcode to a file

//Header line struct for the start of a program
struct HeaderLine{
    std::string programName;
    int programLength;
    int startingAddress;
    void writeLine(std::ofstream& objFile){
        objFile<<"H"<<"^"<<programName<<"^"<<toHex(startingAddress,6)<<"^"<<toHex(programLength,6)<<std::endl;
    }
};


struct TextLine{
    //lineaddress starts as undef and is only assigned after finding first hexinstruction to add
    int lineAddress = -1;
    int lineLength=0;
    std::vector<std::string> textLines;

    void writeLine(std::ofstream& objFile){
        objFile<<"T"<<"^"<<toHex(lineAddress,6)<<"^"<<toHex(lineLength,2);
        for(std::string text: textLines){
            objFile<<"^"<<text;
        }
        objFile<<std::endl;
    }
};

//Simple modification record that assumes the only thing we are adding is the program start to any relative variables
struct ModificationLine{
    int modifiedAddress;
    int modifiedHalfBytes;
    void writeLine(std::ofstream& objFile){
        objFile<<"M"<<"^"<<toHex(modifiedAddress,6)<<"^"<<toHex(modifiedHalfBytes,2)<<std::endl;
    }
};

//Endline for the end of a program
struct EndLine{
    int endingAddress;
    int startingAddress;

    void writeLine(std::ofstream& objFile){
        objFile<<"E"<<"^"<<toHex(endingAddress,6)<<"^"<<toHex(startingAddress,6)<<std::endl;
    }
};

#endif
