#include "carriage.h"
#include <iostream>

Carriage::Carriage(int carriageNumber, int classType, int occupiedSeats, int freeSeats)
    : carriageNumber(carriageNumber), classType(classType), occupiedSeats(occupiedSeats), freeSeats(totalSeats - occupiedSeats) {}


int Carriage::getFreeSeats() const
{
    return freeSeats;
}
void Carriage::setFreeSeats(int freeSeats)
{
    this->freeSeats = freeSeats;
}
int Carriage::getNumber() const
{
    return carriageNumber;
}

int Carriage::getCarriageClass() const
{
    return classType;
}

int Carriage::getTotalSeats() const
{
    return totalSeats;
}

int Carriage::getOccupiedSeats() const
{
    return occupiedSeats;
}

void Carriage::displayCarriages() const {
    cout << "------------------------" << endl;
    cout << "Carriage number: " << carriageNumber << endl;
    cout << "Class: " << classType << endl;
    cout << "Occupied seats: " << occupiedSeats << endl;
    cout << "Free seats: " << freeSeats << endl;
    cout << "------------------------" << endl;
}
void Carriage::reduceFreeSeats(Carriage& carriage) {
    if (carriage.getFreeSeats() > 0) {
        carriage.setFreeSeats(carriage.getFreeSeats() - 1);
    }
}
