#ifndef locationCounter
#define locationCounter

#include <string>

class LocationCounter{
    
    private:
        int counter = 0;
    public:
        LocationCounter();
        LocationCounter(std::string startingaddress);
        std::string getLocationCounter();
        void incrementLocationCounter(int i);
};


#endif