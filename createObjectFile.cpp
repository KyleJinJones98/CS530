#include "createObjectFile.h"

enum Directive{RESB, RESW, BYTE, WORD, BASE, LTORG, ORG, EQU};
std::unordered_map<std::string, Directive> directivetable{
    {"RESB", Directive::RESB},
    {"RESW", Directive::RESW},
    {"BYTE", Directive::BYTE},
    {"WORD", Directive::WORD},
    {"BASE", Directive::BASE},
    {"LTORG", Directive::LTORG},
    {"ORG", Directive::ORG},
    {"EQU", Directive::EQU}
  };

const int MAXTEXTLENGTH = 30;
void generateObjectFile(std::vector<sourceLineStruct> assembledLines, std::string fileName){
    sourceLineStruct firstLine = assembledLines[0];
    int startingLine = 0;
    //get first line that is not a comment
    while(firstLine.label=="."){
        startingLine++;
        firstLine = assembledLines[startingLine];
    }
    HeaderLine hl = HeaderLine();
    hl.programName= firstLine.label;
    hl.startingAddress= toDec(firstLine.targetAddress);

    std::vector<TextLine> textLines;
    std::vector<ModificationLine> modLines;
    TextLine currentLine = TextLine();
    for(unsigned int i = startingLine+1; i <(assembledLines.size()-1); i++){
        try{
        //we only process noncomment lines
        if(assembledLines[i].label!="."){
            //we can handle opcodes and literals in the sameway
            if(checkOpcode(assembledLines[i].operation) || assembledLines[i].label=="*"){
                //if this is the first hexinstruction in the object code
                //set the text line's address 
                if(currentLine.lineAddress==-1){
                    currentLine.textLines.push_back(assembledLines[i].hexInstruction);
                    currentLine.lineAddress=toDec(assembledLines[i].lineAddress);
                }
                //otherwise we have to check if the line fits
                else if(toDec(assembledLines[i+1].lineAddress)-currentLine.lineAddress<=30){
                    currentLine.textLines.push_back(assembledLines[i].hexInstruction);
                    currentLine.lineLength =toDec(assembledLines[i+1].lineAddress)-currentLine.lineAddress;
                }
                //and if it doesn't, begin a newline
                else{
                    textLines.push_back(currentLine);
                    currentLine= TextLine();
                    currentLine.textLines.push_back(assembledLines[i].hexInstruction);
                    currentLine.lineLength =toDec(assembledLines[i+1].lineAddress)-currentLine.lineAddress;
                }

                //Then we see if this line requires a modification record
                if(assembledLines[i].needsModification){
                    ModificationLine currentMod = ModificationLine();
                    currentMod.modifiedAddress = toDec(assembledLines[i].lineAddress);
                    if(getOpcodeFormat(assembledLines[i].operation)==4){
                        currentMod.modifiedHalfBytes=5;
                    }
                    else{
                        currentMod.modifiedHalfBytes =3;
                    }
                    modLines.push_back(currentMod);
                }
            }
            //otherwise this is a directive
            else{
                Directive d = directivetable[assembledLines[i].operation];
                switch (d)
                {
                //only directives that have relevant hex to Store in textLine
                case Directive::BYTE:
                    //we can handle BYTE and WORD similarly to how we handle opcodes and literals
                    if(currentLine.lineAddress==-1){
                        currentLine.textLines.push_back(assembledLines[i].hexInstruction);
                        currentLine.lineAddress=toDec(assembledLines[i].lineAddress);
                    }
                    else if(toDec(assembledLines[i+1].lineAddress)-currentLine.lineAddress<=30){
                        currentLine.textLines.push_back(assembledLines[i].hexInstruction);
                        currentLine.lineLength =toDec(assembledLines[i+1].lineAddress)-currentLine.lineAddress;
                    }
                    else{
                        textLines.push_back(currentLine);
                        currentLine= TextLine();
                        currentLine.textLines.push_back(assembledLines[i].hexInstruction);
                        currentLine.lineLength =toDec(assembledLines[i+1].lineAddress)-currentLine.lineAddress;
                    }
                    if(assembledLines[i].needsModification){
                        ModificationLine currentMod = ModificationLine();
                        currentMod.modifiedAddress = toDec(assembledLines[i].lineAddress);
                        //only change is the number of halfbytes will always be the same being the entire Byte
                        currentMod.modifiedHalfBytes =2;
                        modLines.push_back(currentMod);
                        
                    }
                    break;
                case Directive::WORD:
                    if(currentLine.lineAddress==-1){
                        currentLine.textLines.push_back(assembledLines[i].hexInstruction);
                        currentLine.lineAddress=toDec(assembledLines[i].lineAddress);
                    }
                    else if(toDec(assembledLines[i+1].lineAddress)-currentLine.lineAddress<=30){
                        currentLine.textLines.push_back(assembledLines[i].hexInstruction);
                        currentLine.lineLength =toDec(assembledLines[i+1].lineAddress)-currentLine.lineAddress;
                    }
                    else{
                        textLines.push_back(currentLine);
                        currentLine= TextLine();
                        currentLine.textLines.push_back(assembledLines[i].hexInstruction);
                        currentLine.lineLength =toDec(assembledLines[i+1].lineAddress)-currentLine.lineAddress;
                    }
                    if(assembledLines[i].needsModification){
                        ModificationLine currentMod = ModificationLine();
                        currentMod.modifiedAddress = toDec(assembledLines[i].lineAddress);
                        //only change is the number of halfbytes will always be the same being the entire 3 Bytes
                        currentMod.modifiedHalfBytes =6;
                        modLines.push_back(currentMod);

                    }
                    break;

                //need to end current line and begin new textline
                case Directive::RESB:
                    //if lineAddress is not undefined
                    if(currentLine.lineAddress!=-1){
                        textLines.push_back(currentLine);
                        currentLine = TextLine();
                    }
                    break;
                case Directive::RESW:
                    //if lineAddress is not undefined
                    if(currentLine.lineAddress!=-1){
                        textLines.push_back(currentLine);
                        currentLine = TextLine();
                    }
                    break;
                case Directive::ORG:
                    //if lineAddress is not undefined
                    if(currentLine.lineAddress!=-1){
                        textLines.push_back(currentLine);
                        currentLine = TextLine();
                    }
                    break;
                //all other directives can be safely ignored
                default:
                    break;
                }

            }
        }
        }
        catch(AssemblyException e){
            std::cout<<"Failed to Convert Line "<<i<<"To Object Code: ";
            assembledLines[i].printLine();
            throw AssemblyException();
        }
    }

    if(currentLine.lineAddress!=-1){
        textLines.push_back(currentLine);
    }

    EndLine el = EndLine();
    el.endingAddress= toDec(assembledLines[assembledLines.size()-1].lineAddress);
    el.startingAddress = hl.startingAddress;
    hl.programLength= el.endingAddress- hl.startingAddress;

    //begin writing object file here
    std::ofstream objFile(fileName);
    hl.writeLine(objFile);
    for(TextLine tl : textLines){
        tl.writeLine(objFile);
    }
    for(ModificationLine ml : modLines){
        ml.writeLine(objFile);
    }
    el.writeLine(objFile);

}