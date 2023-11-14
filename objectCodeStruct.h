#ifndef OBJECTCODESTRUCT_H
#define OBJECTCODESTRUCT_H

#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include "hexConverter.h"

struct HeaderLine{
    std::string programName;
    int programLength;
    int startingAddress;
    void writeLine(std::ofstream& objFile){
        objFile<<"H"<<"^"<<programName<<"^"<<toHex(startingAddress,6)<<"^"<<toHex(programLength,6)<<std::endl;
    }
};

struct TextLine{
    //lineaddress starts as undef
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

struct ModificationLine{
    int modifiedAddress;
    int modifiedHalfBytes;
    void writeLine(std::ofstream& objFile){
        objFile<<"M"<<"^"<<toHex(modifiedAddress,6)<<"^"<<toHex(modifiedHalfBytes,2)<<std::endl;
    }
};

struct EndLine{
    int endingAddress;
    int startingAddress;

    void writeLine(std::ofstream& objFile){
        objFile<<"E"<<"^"<<toHex(endingAddress,6)<<"^"<<toHex(startingAddress,6)<<std::endl;
    }
};

#endif