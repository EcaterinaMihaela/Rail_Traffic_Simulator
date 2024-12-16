#ifndef STATION_H
#define STATION_H

#include <string>

using namespace std;

class Station
{
private:
    string name;
    string arrivalTime;
    int stationLine;

public:

    // Constructor
    Station(const string& name, const string& arrivalTime, int stationLine);

    // Access functions
    string getName() const;
    string getArrivalTime() const;
    int getStationLine() const;

    /*friend ostream& operator<<(ostream& os, const Station& station)
    {
        os << station.name;
        return os;
    }*/
};

#endif
