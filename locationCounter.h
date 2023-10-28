#ifndef locationCounter_H
#define locationCounter_H

#include <string>
#include "hexConverter.h"

class LocationCounter{
    
    private:
        int counter = 0;
    public:
        LocationCounter();
        LocationCounter(std::string startingaddress);
        std::string getLocationCounter();
        void incrementLocationCounter(int i);
        void setLocationCounter(int i);
};


#endif