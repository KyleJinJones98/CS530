/**
 * CS 530, Fall 2023
 * 11/14/2023
 * Joseph Vue, RED ID: 820231744
 * Jake Opatz, RED ID: 826638326
 * Kyle Jones, RED ID: 819938646
 */

#ifndef ASSEMBLEREXCEPTION_H
#define ASSEMBLEREXCEPTION_H
#include <exception> 

//Assembly Exception error, so that errors in source code found during assembly time
//can generate proper stack traces
class AssemblyException : public std::exception {
};

#endif
