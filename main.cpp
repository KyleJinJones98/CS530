/**
 * CS 530, Fall 2023
 * 11/14/2023
 * Joseph Vue, RED ID: 820231744
 */

//Main File for the assembler program
//handles commands, reading/writing to files
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "sourceLineStruct.h"
#include "assemblerPass1.h"
#include "assemblerPass2.h"
#include "createObjectFile.h"


int main(int argc, char* argv[]){

    //if we recieved no filenames as input error out immediately
    if(argc==1){
        std::cout << "Input Error: No input received expected at least 1 input file."<< std::endl;
        exit(1);
    }

    //read filenames into a string of vectors
    std::vector<std::string> fileNames;
    bool writeObjectFile =false;
    for(int i =1; i<argc; i++){
        std::string currentArg = argv[i];
        if(currentArg=="-o"){
            writeObjectFile=true;
        }
        else{
            fileNames.push_back(currentArg);
        }
    }

    for(std::string fileName : fileNames){

        int endOfName = fileName.find(".");
        std::string isolatedName= fileName.substr(0,endOfName);
        if(fileName.substr(endOfName)!=".sic"){
            std::cout << "File of wrong type: " <<fileName.substr(endOfName)<<" Expected: .sic" << std::endl;
        }
        else{
        //could do some error checking here to ensure the fileName is a proper .sic file
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
            try{
            //symtab, and vector of strings to pass1
            SymbolTable symtab= SymbolTable();
            std::vector<sourceLineStruct> assembledLines =pass1(sourceLines, symtab);
            assembledLines = pass2(assembledLines,symtab);
            //pass1 sourceline struct to pass2
            //pass2 sourceline struct to write to listing file

            //Write Listing File
            std::ofstream listingFile(isolatedName+".l");
            for(sourceLineStruct line : assembledLines){
                line.writeLine(listingFile);
            }
            listingFile.close();

            //write symtab to symfile 
            std::ofstream symFile(isolatedName+".st");
            symtab.writeTable(symFile);
            symFile.close();    
   
            //print file names
            std::cout<<"Successfully assembled source code to files: "<<isolatedName<<".l and "<<isolatedName<<".st"<<std::endl;
            try{
            if(writeObjectFile){
                generateObjectFile(assembledLines, isolatedName+".ob");
                std::cout<<"Successfully assembled object code to file: "<<isolatedName<<".ob"<<std::endl;
            }
            }
            //catch error writting obj code
            catch(AssemblyException e){
                std::cout<<"Error during writing object code could not write object code to file File: "<<fileName<<std::endl;
            }

            //catch assemblyerror
            }catch(AssemblyException e){
                std::cout<<"Error during Assembly could not assemble File: "<<fileName<<std::endl;
            }

            
            sourceFile.close();
        }
        }
    }
    exit(0);
}
