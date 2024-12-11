#ifndef STATION_H
#define STATION_H

#include <string>

using namespace std;

class Station
{
private:
    string name;
    string arrivalTime;

public:

    // Constructor
    Station(const string& name, const string& arrivalTime)
        : name(name), arrivalTime(arrivalTime) {}

    // Access functions
    string getName() const;
    string getArrivalTime() const;
};

#endif
