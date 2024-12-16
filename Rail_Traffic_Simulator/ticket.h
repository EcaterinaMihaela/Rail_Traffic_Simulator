#ifndef TICKET_H
#define TICKET_H

#include <string>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <iomanip>
using namespace std;

class Ticket
{
private:
    int ticketID;
    double basePrice;
    double discount;
    string ticketStatus;
    string route;
    int trainID;
    string purchaseDate;
    string category;  //Category of the pasager:Student,etc

public:
    Ticket(double price, const string& status, const string& route, const int train, const string& passengerCategory);

    int getTicketID() const;
    string getPurchaseDate() const;
    double getPrice() const;

    void applyDiscount(int carriageClass);
    void displayTicketDetails(int carriageNumber, int chosenSeat, string departureStation, string arrivalStation) const;
    void saveTicketToFile(int carriageNumber, int chosenSeat, string departureStation, string arrivalStation);
};

#endif
