
#include "assemblerPass1.h"

//Implements the operations during the first pass of the assembler

std::vector<sourceLineStruct> pass1(std::vector<std::string> sourceLines, SymbolTable& symtab){
    std::vector<sourceLineStruct> output;

    sourceLineStruct firstLine;
    firstLine.getLineComponents(sourceLines[0]);
    unsigned int startingLine=0;

    //process any number of commentlines until first line is reached
    while(firstLine.label=="."){
        output.push_back(firstLine);
        firstLine =sourceLineStruct();
        startingLine++;
        firstLine.getLineComponents(sourceLines[startingLine]);
    }
    //do error checking to ensure program is started correctly
    if(firstLine.operation!="START"){
        std::cout<<"Program not started with correct opcode: Start. \n Incorrect opcode: "+firstLine.operation + "\n";
       //throw "Program not started with correct opcode: Start. \n Incorrect opcode: "+firstLine.operation + "\n";
       exit(3);
    }

    //if our starting address is 0, this is a relocatable program and symbol addresses are relative
    //otherwise they are absolute
    bool absoluteProgram = true;
    if(toDec(firstLine.targetAddress)==0){
        absoluteProgram =false;
    }

    //set defaults based on first line contents
    LocationCounter locctr = LocationCounter(firstLine.targetAddress);
    firstLine.lineAddress = locctr.getLocationCounter();
    output.push_back(firstLine);
    symtab.addSymbol(firstLine.label, firstLine.lineAddress);
    symtab.defineSymbol(firstLine.label, toDec(firstLine.lineAddress), absoluteProgram);

    for(unsigned int i = startingLine+1; i<(sourceLines.size()-1); i++){
        sourceLineStruct currentLine = sourceLineStruct();
        currentLine.getLineComponents(sourceLines[i]); //extract the line components from the current source line
        if(currentLine.label!="."){
        currentLine.lineAddress = locctr.getLocationCounter();//assign address to current line of source
        }
        //append the proccessed line struct
        output.push_back(currentLine);
        if(currentLine.label!="."){
        
        bool isLiteral = currentLine.targetAddress.find("=")!= std::string::npos;
        if(currentLine.label != "" && !isLiteral){ //check if label is defined and is not a literal
            symtab.addSymbol(currentLine.label,currentLine.lineAddress);
            symtab.defineSymbol(currentLine.label, toDec(currentLine.lineAddress), absoluteProgram);
        }
        //add literal with no label using definition string as default
        else if(currentLine.label==""&& isLiteral){
            symtab.addLiteral(currentLine.targetAddress, currentLine.targetAddress);
        }
        else if(isLiteral){//add a literl with a label
            symtab.addLiteral(currentLine.label, currentLine.targetAddress);
        } 

        //if the instruction is an opcode, we can just account for its size and move on
        if(checkOpcode(currentLine.operation)){
            int bytes = getOpcodeSize(currentLine.operation);
            locctr.incrementLocationCounter(bytes);
        }
        //check and handle directive here
        else if(checkDirective(currentLine.operation)){
            //if true handleDirective(currentLine.operation, currentLine.targetAddress, locctr)
            handleDirective(currentLine.label, currentLine.operation, currentLine.targetAddress, locctr, symtab, output);
            //increment locctr if directive requires it
            int bytes = getDirectiveSize(symtab,currentLine.operation, currentLine.targetAddress);
            locctr.incrementLocationCounter(bytes);
        }
        else{
            std::cout<<"Unregocnized command: "+ currentLine.operation+ " at line: "+ std::to_string(i)+"\n";
            //throw "Unregocnized command: "+ currentLine.operation+ " at line: "+ std::to_string(i)+"\n";
            exit(3);
        }
        }


    }

    //once all lines have been processed we may need to resolve symbol values
    //As well as assign any unassigned literals, we would do this by "adding" a line for each one
    symtab.instantiateLiterals(locctr,output);
    //e.g for the example we would add a sourcelinestruct with the values
    //line address = 0FC6 label =*      opcode  =C'EOF' and hexinstruction = 454F46  

    std::vector<std::string> symbolNames = symtab.getAllSymbols();
    for(unsigned int i = 0; i<symbolNames.size(); i++){
        if(!symtab.isDefined(symbolNames[i])){
            Operand result = parseExpression(symtab.getSymbolValue(symbolNames[i]), symtab);
            symtab.defineSymbol(symbolNames[i], result.value, result.getAbsoluteFlag());
        }
    }         

    //process the last line which should have the value of end
    sourceLineStruct endLine;
    endLine.getLineComponents(sourceLines[sourceLines.size()-1]);
    //do error checking to ensure program is started correctly
    if(endLine.operation!="END"){
        std::cout<<"Program not started with correct opcode: END. \n Incorrect opcode: "+endLine.operation + "\n";
       //throw "Program not started with correct opcode: Start. \n Incorrect opcode: "+firstLine.operation + "\n";
       exit(3);
    }
    endLine.lineAddress=locctr.getLocationCounter();
    output.push_back(endLine);

    return output;
}

/*
int main(){
    SymbolTable symtab;

    //read file
    std::vector<std::string> testLines;
    std::ifstream file("testFile.sic");
    std::string str;
    while (std::getline(file, str))
    {
        testLines.push_back(str);
    }
    //do and print pass1
    std::vector<sourceLineStruct> testOutput = pass1(testLines,symtab);
    std::cout<<"TEST"<<std::endl;
    for (unsigned int i=0; i<testOutput.size(); i++){
        testOutput[i].printLine();
    }
    std::vector<sourceLineStruct> pass2Output = pass2(testOutput, symtab);
    //do and print pass 2
    for (unsigned int i = 0; i < pass2Output.size(); i++) {
        pass2Output[i].printLine();
    }
}
*/
