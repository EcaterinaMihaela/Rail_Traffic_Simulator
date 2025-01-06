#include "ticket.h"
#include <iostream>
#include <fstream>  // Include this header for file I/O
#include <sstream>  // Include this for stringstream
using namespace std;

Ticket::Ticket(double price, const string& status, const string& route, const int train, const string& passengerCategory)
    : basePrice(price), ticketStatus(status), route(route), trainID(train), category(passengerCategory),discount(0.0)
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


void Ticket::displayTicketDetails(int carriageNumber, int chosenSeat, string departureStation, string arrivalStation,int classType) const
{
    cout << "You will travel on date " << travelDate << " from " << departureStation << " to " << arrivalStation << " !\n Ticket details: \n";

    cout << "\n======================================Ticket purchased!================================================\n";
    cout << "Category: " << category << endl;
    cout << "Ticket ID: " << ticketID << endl;
    cout << "Base Price: " << basePrice << endl;
    cout << "Discount: " << discount * 100 << "%\n";
    cout << "Final Price: " << getPrice() << endl;
    cout << "Route: " << departureStation << "-" << arrivalStation << "\n";
    cout << "Travel Date: " << travelDate << endl;
    cout << "Train: " << trainID << endl;
    cout << "Purchase Date: " << purchaseDate << endl;
    cout << "Ticket Status: " << ticketStatus << endl;
    cout << "Carriage: " << carriageNumber << endl;
    cout << "Seat: " << chosenSeat << endl;
    cout << "Carriage Class: " << classType << endl;
    cout << "=========================================================================================================";
}

void Ticket::saveTicketToFile(int carriageNumber, int chosenSeat, string departureStation, string arrivalStation,int classType)
{
    ofstream outFile("ticket.txt", ios::app); // Open file in append mode
    if (outFile.is_open()) {
        stringstream ss;
        ss << "\n======================================Ticket purchased!================================================\n";
        ss << "Category: " << category << endl;
        ss << "Ticket ID: " << ticketID << endl;
        ss << "Base Price: " << basePrice << endl;
        ss << "Discount: " << discount * 100 << "%\n";
        ss << "Final Price: " << getPrice() << endl;
        ss << "Route: " << departureStation << "-" << arrivalStation << endl;
        ss << "Travel Date: " << travelDate << endl;
        ss << "Train: " << trainID << endl;
        ss << "Purchase Date: " << purchaseDate << endl;
        ss << "Ticket Status: " << ticketStatus << endl;
        ss << "Carriage: " << carriageNumber << endl;
        ss << "Seat: " << chosenSeat << endl;
        ss << "Carriage Class: " << classType << endl;
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

void Ticket::setTravelDate(const string& departureTime)
{
    // Get the current date and time
    time_t now = time(0);
    tm ltm;
    if (localtime_s(&ltm, &now) != 0)
    {
        throw runtime_error("Error getting local time.");
    }

    int currentYear = 1900 + ltm.tm_year;
    int currentMonth = 1 + ltm.tm_mon;
    int currentDay = ltm.tm_mday;

    // Determines the number of days in the current month
    static const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int daysInCurrentMonth = daysInMonth[currentMonth - 1];

    // Checks if the current year is a leap year--bisect year
    if (currentMonth == 2 && ((currentYear % 4 == 0 && currentYear % 100 != 0) || (currentYear % 400 == 0)))
    {
        daysInCurrentMonth = 29;
    }

    int selectedDay = -1;  //invalid initialization
    bool validDay = false;

    while (!validDay)
    {
        // Displays the remaining days of the current month
        cout << "\nDays available for travel in the current month (" << currentMonth << "/" << currentYear << "): ";
        for (int i = currentDay; i <= daysInCurrentMonth; ++i) {
            cout << i << " ";
        }
        cout << endl;

        // Ask the user to select a valid day
        cout << "Enter the desired day of the current month: ";
        cin >> selectedDay;

        // Validate selected day
        if (selectedDay < currentDay || selectedDay > daysInCurrentMonth)
        {
            cout << "The selected day is not valid. Please choose a day between " << currentDay << " and " << daysInCurrentMonth << ".\n";
            continue;
        }

        // If the user selects the current day, we check the time
        if (selectedDay == currentDay)
        {
            int currentHour = ltm.tm_hour;
            int currentMinute = ltm.tm_min;

            // Extract the hour and minutes from departureTime
            int departureHour = stoi(departureTime.substr(0, 2));
            int departureMinute = stoi(departureTime.substr(3, 2));

            // Compare departure time with current time
            if (currentHour > departureHour || (currentHour == departureHour && currentMinute >= departureMinute))
            {
                cout << "The train has already left today. Please choose another day.\n";
                continue;
            }
        }
        validDay = true;
    }

    // Build the travel date
    stringstream ss;
    ss << currentYear << "-"
        << setfill('0') << setw(2) << currentMonth << "-"
        << setfill('0') << setw(2) << selectedDay;

    travelDate = ss.str();
    cout << "\nThe travel date has been set : " << travelDate << endl;
}



string Ticket::getTravelDate() const
{
    return travelDate;
}