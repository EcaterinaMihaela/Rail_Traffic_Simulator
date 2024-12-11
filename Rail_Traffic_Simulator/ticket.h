#ifndef TICKET_H
#define TICKET_H

#include <string>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <iomanip>
using namespace std;

class Ticket {
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
    Ticket(double price, const string& status, const string& route, const int train, const string& passengerCategory)
        : basePrice(price), ticketStatus(status), route(route), trainID(train), category(passengerCategory)
    {
        // Generate a random ticket ID
        ticketID = rand() % 1000000000 + 100000;

        // Set purchase date to today
        time_t t = time(nullptr);
        tm now;
        localtime_s(&now, &t);

        ostringstream oss;
        oss << (now.tm_year + 1900) << '-'
            << setw(2) << setfill('0') << (now.tm_mon + 1) << '-'
            << setw(2) << setfill('0') << now.tm_mday;

        // Initialize purchaseDate with formatted date
        purchaseDate = oss.str();
    }

    int getTicketID() const;
    string getPurchaseDate() const;
    double getPrice() const;

    void applyDiscount(int carriageClass);
    void displayTicketDetails(int carriageNumber, int chosenSeat) const;
    void saveTicketToFile(int carriageNumber, int chosenSeat);
};

#endif
