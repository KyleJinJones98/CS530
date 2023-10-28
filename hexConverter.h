#ifndef hexConverter_H
#define hexConverter_H
#include <sstream>
#include <string>
#include <iomanip>

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
    return stoi(hexnumber, 0, 16);
}

//converts string to ascii and then to hex
inline
std::string toHex(std::string str, int width){
  std::stringstream strstream;

  for (const auto &c : str) {
    strstream<<std::setfill('0') << std::setw(width) <<std::hex <<std::uppercase<< int(c); 
  }
  return (strstream.str());
}

#endif