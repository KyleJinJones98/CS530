/**
 * CS 530, Fall 2023
 * Joseph Vue, RED ID: 820231744
 */

#ifndef CREATEOBJECTFILE_H
#define CREATEOBJECTFILE_H
#include "objectCodeStruct.h"
#include "hexConverter.h"
#include "opcodeHandler.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "sourceLineStruct.h"
#include <fstream>
void generateObjectFile(std::vector<sourceLineStruct> assembledLines, std::string fileName);
#endif
