#include "ticket.h"
#include <iostream>

using namespace std;

int Ticket::getTicketID() const
{
    return ticketID;
}

string Ticket::getPurchaseDate() const
{
    return purchaseDate;
}

double Ticket::getPrice() const {
    return basePrice * (1 - discount);
}


void Ticket::applyDiscount(int carriageClass) {
    if (carriageClass == 1) {
        discount = 0.0; // No discount for first-class
    }
    else if (carriageClass == 2) {
        // Apply discount for second-class based on passenger category
        if (category == "Student") {
            discount = 0.9; // 90% gratuity
        }
        else if (category == "Pupil") {
            discount = 0.5; // 50% discount
        }
        else if (category == "Pensioner") {
            discount = 0.3; // 30% discount
        }
        else if (category == "Advance") {
            discount = 0.25; // 25% discount
        }
        else {
            discount = 0.0; // No discount
        }
    }
    else {
        cout << "Invalid carriage class.\n";
        discount = 0.0; // No discount by default
    }
}


void Ticket::displayTicketDetails(int carriageNumber, int chosenSeat) const {
    cout << "\n======================================Ticket purchased!================================================\n";
    cout << "Category: " << category << "\n";
    cout << "Ticket ID: " << ticketID << endl;
    cout << "Base Price: " << basePrice << "\n";
    cout << "Discount: " << discount * 100 << "%\n";
    cout << "Final Price: " << getPrice() << "\n";
    cout << "Route: " << route << "\n";
    cout << "Train: " << trainID << "\n";
    cout << "Purchase Date: " << purchaseDate << "\n";
    cout << "Ticket Status: " << ticketStatus << "\n";
    cout << "Carriage: " << carriageNumber << endl;
    cout << "Seat: " << chosenSeat << endl;
    cout << "=========================================================================================================";
}
