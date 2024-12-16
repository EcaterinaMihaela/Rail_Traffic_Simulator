#include "Station.h"

Station::Station(const string& name, const string& arrivalTime, int stationLine)
    : name(name), arrivalTime(arrivalTime), stationLine(stationLine) {}

string Station::getName() const
{
    return name;
}

string Station::getArrivalTime() const
{
    return arrivalTime;
}
int Station::getStationLine() const
{
    return stationLine;
}