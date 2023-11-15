#Kyle Jones (RED ID: 819938646), Joseph Vue (RED ID: 820231744), Jake Opatz (RED ID: 826638326)
#CS530 Fall 2023
#Assignment 2
#makefile
CC = g++
CFLAGS = -Wall -g -std=c++11

#create executable
axe: assemblerPass1.cpp opcodeHandler.cpp symbolTable.cpp locationCounter.cpp sourceLineStruct.h assemblerDirectivesPass1.cpp expressionParsing.cpp assemblerPass2.cpp createObjectFile.cpp main.cpp
	$(CC) $(CFLAGS) assemblerPass1.cpp locationCounter.cpp symbolTable.cpp opcodeHandler.cpp assemblerDirectivesPass1.cpp expressionParsing.cpp createObjectFile.cpp assemblerPass2.cpp main.cpp -o assembler

#remove executable
clean:
	rm axe
