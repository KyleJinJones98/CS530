/**
 * CS 530, Fall 2023
 * 11/14/2023
 * Joseph Vue, RED ID: 820231744
 * Jake Opatz, RED ID: 826638326
 * Kyle Jones, RED ID: 819938646
 */

#ifndef hexConverter_H
#define hexConverter_H
#include <sstream>
#include <string>
#include <iomanip>
#include <iostream>
#include "assemblerException.h"

/*
hex Converter is a Utility class used for converting values to and from hex
*/

//converts a decimal number to a hex string
//width is used to define a min number of characters in the hexstring for formatting output
inline
std::string toHex(int decnumber, int width){
  std::stringstream strstream;
  strstream<<std::setfill('0') << std::setw(width) <<std::hex <<std::uppercase<< decnumber; 
  return (strstream.str());
}

//converts hex string to decimal
inline
int toDec(std::string hexnumber){
  try{
    return stoi(hexnumber, 0, 16);
  }
  catch(std::invalid_argument e){
    std::cout<<"Problem converting String: "<<hexnumber<<" To Decimal"<<std::endl;
    throw AssemblyException();
  }
}

//converts string to ascii and then to hex
inline
std::string toHex(std::string str, int width){
  std::stringstream hexstream;

  for (const auto &c : str) {
    hexstream<<std::hex <<std::uppercase<< int(c); 
  }
  std::stringstream formatstream;
  formatstream<<std::setfill('0') << std::setw(width)<<hexstream.str();
  return (formatstream.str());
}

#endif
