#ifndef hexConverter_H
#define hexConverter_H
#include <sstream>
#include <string>
#include <iomanip>

/*
hex Converter is a Utility class used for converting values to and from hex
*/
inline
std::string toHex(int decnumber, int width){
  std::stringstream strstream;
  strstream<<std::setfill('0') << std::setw(width) <<std::hex <<std::uppercase<< decnumber; 
  return ( strstream.str() );
}

inline
int toDec(std::string hexnumber){
    return stoi(hexnumber, 0, 16);
}

#endif