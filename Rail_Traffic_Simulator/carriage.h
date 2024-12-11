#ifndef CARRIAGE_H
#define CARRIAGE_H

using namespace std;

class Carriage
{
private:
    int carriageNumber;
    int classType;
    int totalSeats = 106;
    int occupiedSeats;
    int freeSeats;

public:
    // Constructors
    Carriage(int carriageNumber, int classType, int occupiedSeats, int freeSeats);

    // Methods

    int getNumber() const;
    int getCarriageClass() const;
    int getTotalSeats() const;
    int getOccupiedSeats() const;
    int getFreeSeats() const;
    void setFreeSeats(int freeSeats);

    void displayCarriages() const;
    void reduceFreeSeats(Carriage& carriage);
};

#endif
