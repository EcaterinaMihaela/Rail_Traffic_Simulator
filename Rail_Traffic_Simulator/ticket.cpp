#include "ticket.h"
#include <iostream>
#include <fstream>  // Include this header for file I/O
#include <sstream>  // Include this for stringstream
using namespace std;

Ticket::Ticket(double price, const string& status, const string& route, const int train, const string& passengerCategory)
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

int Ticket::getTicketID() const
{
    return ticketID;
}

string Ticket::getPurchaseDate() const
{
    return purchaseDate;
}

double Ticket::getPrice() const
{
    return basePrice * (1 - discount);
}


void Ticket::applyDiscount(int carriageClass)
{
    if (carriageClass == 1)
    {
        discount = 0.0; // No discount for first-class
    }
    else if (carriageClass == 2)
    {
        // Apply discount for second-class based on passenger category
        if (category == "Student")
        {
            discount = 0.9; // 90% discount
        }
        else if (category == "Child")
        {
            discount = 0.5; // 50% discount
        }
        else if (category == "Pensioner")
        {
            discount = 0.3; // 30% discount
        }
        else if (category == "Advance")
        {
            discount = 0.25; // 25% discount
        }
        else
        {
            discount = 0.0; // No discount
        }
    }
    else {
        cout << "Invalid carriage class.\n";
        discount = 0.0; // No discount by default
    }
}


void Ticket::displayTicketDetails(int carriageNumber, int chosenSeat, string departureStation, string arrivalStation) const
{
    cout << "\n======================================Ticket purchased!================================================\n";
    cout << "Category: " << category << "\n";
    cout << "Ticket ID: " << ticketID << endl;
    cout << "Base Price: " << basePrice << "\n";
    cout << "Discount: " << discount * 100 << "%\n";
    cout << "Final Price: " << getPrice() << "\n";
    cout << "Route: " << departureStation << "-" << arrivalStation << "\n";
    cout << "Train: " << trainID << "\n";
    cout << "Purchase Date: " << purchaseDate << "\n";
    cout << "Ticket Status: " << ticketStatus << "\n";
    cout << "Carriage: " << carriageNumber << endl;
    cout << "Seat: " << chosenSeat << endl;
    cout << "=========================================================================================================";
}

void Ticket::saveTicketToFile(int carriageNumber, int chosenSeat, string departureStation, string arrivalStation)
{
    ofstream outFile("ticket.txt", ios::app); // Open file in append mode
    if (outFile.is_open()) {
        stringstream ss;
        ss << "\n======================================Ticket purchased!================================================\n";
        ss << "Category: " << category << "\n";
        ss << "Ticket ID: " << ticketID << endl;
        ss << "Base Price: " << basePrice << "\n";
        ss << "Discount: " << discount * 100 << "%\n";
        ss << "Final Price: " << getPrice() << "\n";
        ss << "Route: " << departureStation << "-" << arrivalStation << "\n";
        ss << "Train: " << trainID << "\n";
        ss << "Purchase Date: " << purchaseDate << "\n";
        ss << "Ticket Status: " << ticketStatus << "\n";
        ss << "Carriage: " << carriageNumber << endl;
        ss << "Seat: " << chosenSeat << endl;
        ss << "=========================================================================================================";

        // Write to file
        outFile << ss.str() << endl;

        outFile.close(); // Close the file after writing
    }
    else
    {
        cerr << "Error opening tickets file for writing!\n";
    }
}