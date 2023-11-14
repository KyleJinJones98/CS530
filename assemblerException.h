#ifndef ASSEMBLEREXCEPTION_H
#define ASSEMBLEREXCEPTION_H
#include <exception> 

//Assembly Exception error, so that errors in source code found during assembly time
//can generate proper stack traces
class AssemblyException : public std::exception {
};

#endif