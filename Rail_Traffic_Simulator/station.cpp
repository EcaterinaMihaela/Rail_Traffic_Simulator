#include "Station.h"

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