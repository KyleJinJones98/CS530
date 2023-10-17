#include "locationCounter.h"

#include "hexConverter.h"


LocationCounter::LocationCounter()
{
}

LocationCounter::LocationCounter(std::string startingaddress)
{
    counter = toDec(startingaddress);
}

std::string LocationCounter::getLocationCounter()
{
    return toHex(counter, 4);
}

void LocationCounter::incrementLocationCounter(int i){
    counter+=i;
}

