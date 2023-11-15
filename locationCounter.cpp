/**
 * CS 530, Fall 2023
 * 11/14/2023
 * Joseph Vue, RED ID: 820231744
 * Jake Opatz, RED ID: 826638326
 * Kyle Jones, RED ID: 819938646
 */

#include "locationCounter.h"

LocationCounter::LocationCounter()
{
}

//initializes the location counter with a given address
LocationCounter::LocationCounter(std::string startingaddress)
{
    counter = toDec(startingaddress);
}

//gets the value of the location counter in hex
std::string LocationCounter::getLocationCounter()
{
    return toHex(counter, 4);
}

//increase the location counter by the given number of bytes
void LocationCounter::incrementLocationCounter(int i){
    counter+=i;
}

//sets the location counter to a given address
void LocationCounter::setLocationCounter(int i)
{
    counter = i;
}
