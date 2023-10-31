#Kyle Jones
#cssc2623
#CS530 Fall 2023
#Assignment 2
#makefile
CC = g++
CFLAGS = -Wall -g -std=c++11

#create executable
assembler: assemblerPass1.cpp opcodeHandler.cpp symbolTable.cpp locationCounter.cpp sourceLineStruct.h assemblerDirectivesPass1.cpp
	$(CC) $(CFLAGS) assemblerPass1.cpp locationCounter.cpp symbolTable.cpp opcodeHandler.cpp assemblerDirectivesPass1.cpp -o assembler

#remove executable
clean:
	rm assembler