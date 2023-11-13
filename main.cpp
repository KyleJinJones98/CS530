//Main File for the assembler program
//handles commands, reading/writing to files
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "sourceLineStruct.h"
#include "assemblerPass1.h"

void writeListingFile(std::vector<sourceLineStruct> assembledLines, std::string fileName){
    std::ofstream listingFile(fileName+".lis");
    for(sourceLineStruct line : assembledLines){
        line.writeLine(listingFile);
    }
}

int main(int argc, char* argv[]){

    //if we recieved no filenames as input error out immediately
    if(argc==1){
        std::cout << "Input Error: No input received expected at least 1 input file."<< std::endl;
        exit(1);
    }

    //read filenames into a string of vectors
    std::vector<std::string> fileNames;
    for(int i =1; i<argc; i++){
        fileNames.push_back(argv[i]);
    }

    for(std::string fileName : fileNames){
        std::ifstream sourceFile(fileName);

        //if we fail to open the file, we cannot begin assembly of that file
        if (!sourceFile.is_open()) {
            std::cout << "Failed to open file: " << fileName<< std::endl;
        }
        else{
            //read file into vector of strings
            std::vector<std::string> sourceLines;
            std::string currentLine;
            while(std::getline(sourceFile,currentLine)){
                sourceLines.push_back(currentLine);
            }
            //symtab, and vector of strings to pass1
            SymbolTable symtab= SymbolTable();
            std::vector<sourceLineStruct> pass1Lines =pass1(sourceLines, symtab);
            //pass1 sourceline struct to pass2
            //pass2 sourceline struct to write to listing file
            int endOfName = fileName.find(".");
            std::string isolatedName= fileName.substr(0,endOfName);
            std::cout<<"Pass1 Successful"<<std::endl;
            writeListingFile(pass1Lines,isolatedName);
            //symtab to symfile
            //print file names
            std::cout<<"Successfully assembled source code to files: "<<isolatedName<<".lis and "<<isolatedName<<".sym"<<std::endl;
            //catch assemblyerror

            sourceFile.close();
        }
    }
    exit(0);
}
