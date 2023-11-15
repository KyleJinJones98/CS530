/**
 * CS 530, Fall 2023
 * 11/14/2023
 * Joseph Vue, RED ID: 820231744
 * Jake Opatz, RED ID: 826638326
 * Kyle Jones, RED ID: 819938646
 */

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
