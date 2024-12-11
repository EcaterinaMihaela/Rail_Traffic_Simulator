#include <iostream>
#include "train.h"
#include "carriage.h"
#include "ticket.h"
#include "station.h"
#include <fstream>
#include <vector>
#include <sstream>

#define basePrice 1.6

using namespace std;

int main()
{
    ifstream File("trains.txt");
    if (!File)
    {
        cerr << "Could not open the file!" << endl;
        return 1;
    }

    // Reading trains from file
    vector<Train> trains = Train::readFromFile(File);

    /*// Display readen trains     //FOR DEBUGGING
    cout << "Available trains:\n";
    for (const auto& train : trains) {
        train.display();
        cout << "\n";

        // Display intermediate stations
        cout << "Stations:\n";
        for (const auto& station : train.getStations()) {
            cout << "- " << station.getName() << " at " << station.getArrivalTime() << "\n";
        }
    }*/

    // Main menu
    int option = 0;
    while (option != 5)
    {
        cout << endl
            << "                    Menu: " << endl;
        cout << "______________________________________________________________________________________________________________________" << endl;
        cout << "     1. My train-INFO\n     2. Choose route\n     3. Buy ticket\n     4. My ticket\n     5. Exit\n";

        //  Handle input for option
        while (true)
        {
            cin >> option;

            if (cin.fail())
            {
                cout << "Invalid option! Enter a number between 1 and 5!\n";
                cin.clear();                              // Reset error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore wrong input
            }
            else if (option < 1 || option > 5)
            {
                cout << "Invalid option! Enter a number between 1 and 5!\n";
            }
            else
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line
                break; // valid input, exit the loop
            }
        }

        switch (option)
        {
        case 1: // My train-INFO
        {
            // Display the available trains
            cout << "Available train IDs:\n";
            for (const auto& train : trains)
            {
                cout << "- Train ID: " << train.getID() << "\n";
            }

            int searchByID;
            cout << "\nEnter the train ID,for infos: \n";
            cin >> searchByID;

            bool found = false;
            for (const auto& train : trains) // Search in the train vector
            {
                if (train.getID() == searchByID) //If found
                {
                    train.display();   //display infos about it
                    found = true;     //and mark it as found
                    break;
                }
            }

            if (!found)   //if train not found
            {
                cout << "\nTrain with ID " << searchByID << " was not found!\n";
            }
            break;
        }

        case 2: // Choose route
        {
            cout << "Choose an route:" << endl;
            cout << "1 - Choose the route from the list!" << endl;
            cout << "2 - Choose the route by entering the name of the departure/arrival station!" << endl;

            int subOption;
            cin >> subOption;
            cin.ignore();

            switch (subOption)
            {
            case 1:   //Chose the route from the list
            {

                // Display all the available routes
                cout << "\nAvailable routes:\n";
                vector<pair<string, string>> routes; // Store unique routes

                for (const auto& train : trains)
                {
                    const auto& stations = train.getStations();
                    for (size_t i = 0; i < stations.size(); ++i)
                    {
                        for (size_t j = i + 1; j < stations.size(); ++j)
                        {
                            pair<string, string> route = { stations[i].getName(), stations[j].getName() };
                            if (find(routes.begin(), routes.end(), route) == routes.end())
                            {
                                routes.push_back(route); // Add the route if it doesn't exist
                            }
                        }
                    }
                }

                // Display the routes
                for (size_t i = 0; i < routes.size(); ++i)
                {
                    cout << i + 1 << ". " << routes[i].first << " -> " << routes[i].second << "\n";
                }

                // Let the user select a route
                int routeChoice;
                cout << "Enter the number corresponding to the route: ";
                cin >> routeChoice;

                if (routeChoice < 1 || routeChoice > static_cast<int>(routes.size()))
                {
                    throw out_of_range("Invalid choice! Please try again.");
                }

                // Store the selected departure/arrival stations
                string departureStation = routes[routeChoice - 1].first;
                string arrivalStation = routes[routeChoice - 1].second;

                // Afișăm trenurile disponibile pentru ruta selectată
                cout << "Available trains from \"" << departureStation << "\" to \"" << arrivalStation << "\":" << endl;
                bool found = false;

                // Căutăm trenuri care parcurg ruta selectată
                for (const auto& train : trains)
                {
                    const auto& stations = train.getStations();
                    bool departureFound = false;

                    for (const auto& station : stations)
                    {
                        if (station.getName() == departureStation)
                        {
                            departureFound = true; // Stația de plecare găsită
                        }

                        if (departureFound && station.getName() == arrivalStation)
                        {
                            // Afișăm detaliile trenului
                            cout << "\nTrain " << train.getType() << " " << train.getID()
                                << " departs at " << train.getArrivalTimeForStation(departureStation)
                                << " and arrives at " << station.getArrivalTime() << ".\n";
                            found = true;
                            break;
                        }
                    }
                }

                if (!found)
                {
                    cout << "No trains available from \"" << departureStation << "\" to \"" << arrivalStation << "\"!\n";
                }
                break;
            }

            case 2: // Choose route manual,by entering the strings
            {
                string departureStation, arrivalStation;

                cout << "Enter the departure station: ";
                getline(cin, departureStation);

                cout << "Enter the arrival station: ";
                getline(cin, arrivalStation);

                cout << "Available trains from \"" << departureStation << "\" to \"" << arrivalStation << "\":" << endl;
                bool found = false;

                for (const auto& train : trains)   //search in train vector
                {
                    const auto& stations = train.getStations();
                    bool departureFound = false;   //at first departure is not found

                    // Search for the departure station
                    for (const auto& station : stations)
                    {
                        if (station.getName() == departureStation)
                        {
                            departureFound = true; // Found the departure station
                        }

                        // If departure was found, check for the arrival station
                        if (departureFound)
                        {
                            // Check if it's the arrival station
                            if (station.getName() == arrivalStation)
                            {
                                // Display correct time for the departure station
                                cout << "Train " << train.getType() << " " << train.getID()
                                    << " departs at " << train.getArrivalTimeForStation(departureStation) // departure time
                                    << " and will arrive at the destination at " << station.getArrivalTime() << ".\n"; // arrival time
                                found = true;
                                break; // Found the arrival station
                            }
                        }
                    }
                }

                if (!found)
                {
                    cout << "No trains available from \"" << departureStation << "\" to \"" << arrivalStation << "\"!\n";
                }
                break;
            }
            default:
                cout << "Invalid option, please try again." << endl;
                break;
            }
            break;
        }

        case 3:
        {
            // Main menu
            cout << "Welcome to the train ticket booking system!\n" << endl;
            cout << "Choose an option:" << endl;
            cout << "1 - Choose your desired route!" << endl;
            cout << "0 - Choose the desired train directly!" << endl;

            int subOption;
            cin >> subOption;
            cin.ignore();

            switch (subOption)
            {
            case 1:
            {
                // logic for choosing a route
                cout << "\nChoose your desired route: " << endl;
                string departureStation, arrivalStation;

                cout << "Enter the departure station: ";
                getline(cin, departureStation);
                cout << "Enter the arrival station: ";
                getline(cin, arrivalStation);

                cout << "Available trains from \"" << departureStation << "\" to \"" << arrivalStation << "\":" << endl;
                bool found = false;

                for (const auto& train : trains)
                {
                    const auto& stations = train.getStations();
                    bool departureFound = false;

                    // Search for departure station
                    for (const auto& station : stations)
                    {
                        if (station.getName() == departureStation)
                        {
                            departureFound = true; // departure station found
                        }

                        // If departure station found,search for arrival station
                        if (departureFound && station.getName() == arrivalStation) {
                            // Display the exact time for departure station
                            train.display();
                            found = true;  //if we also found the arrival station,display the trains
                            break;
                        }
                    }
                }

                if (!found)
                {
                    cout << "There are not available trains from \"" << departureStation << "\" to \"" << arrivalStation << "\"!\n";
                }
                else
                {
                    // After finding available trains on the choosen route,choose a train
                    //Like in case 1,if train id found,generate a ticket
                    cout << "Choose the desired train for the selected route (ID): ";
                    int searchByID;
                    cin >> searchByID;

                    bool found = false;
                    for (auto& train : trains) // Search in train vector
                    {
                        if (train.getID() == searchByID)    //if found
                        {
                            train.display();    //display them
                            found = true;

                            train.generateRandomCarriages(); // generate and display all the wagons

                            cout << "Select the desired carriage class (1 for First Class, 2 for Second Class): ";
                            int carriageClass;
                            cin >> carriageClass;

                            // Verify the validity of the class
                            if (carriageClass != 1 && carriageClass != 2)   //the only available classes are 1 and 2
                            {
                                cout << "Invalid class selected. Please choose either 1 or 2." << endl;
                                break;
                            }


                            vector<Carriage> filteredCarriages;        //search in available carriges and random choose a wagon
                            for (const auto& carriage : train.getCarriages())
                            {
                                if (carriage.getCarriageClass() == carriageClass)   //ff there is a carriage with the specified class
                                {
                                    filteredCarriages.push_back(carriage);    //add it in the filtered carriages vector
                                }
                            }

                            // Verify if there are available wagons for the wanted class
                            if (filteredCarriages.empty())
                            {
                                cout << "No carriages available for the selected class." << endl;
                                break;
                            }

                            //random choose a wagon from the ones available
                            int chosenCarriageIndex = rand() % filteredCarriages.size();
                            Carriage& chosenCarriage = filteredCarriages[chosenCarriageIndex];

                            //Choose a seat (random) - if there is any available
                            int occupiedSeat = chosenCarriage.getOccupiedSeats();
                            int freeSeat = chosenCarriage.getFreeSeats();
                            if (freeSeat > 0) {
                                int chosenSeat = rand() % freeSeat + 1; // Random seat index

                                // Create a ticket
                                cout << "Select passenger category (1-Student, 2-Child, 3-Pensioner, 4-Advance, 0-None): ";
                                int choice;
                                cin >> choice;

                                string passengerCategory;
                                switch (choice)
                                {
                                case 1:
                                    passengerCategory = "Student";
                                    break;
                                case 2:
                                    passengerCategory = "Child";
                                    break;
                                case 3:
                                    passengerCategory = "Pensioner";
                                    break;
                                case 4:
                                    passengerCategory = "Advance";
                                    break;
                                case 0:
                                    passengerCategory = "None";
                                    break;
                                default:
                                    cout << "Invalid choice. Please try again.\n";
                                    return 1;
                                }

                                Ticket ticket(basePrice * train.getKilometers(), "Purchased", train.getRoute(), train.getID(), passengerCategory); // price is an exemple


                                // Infos about ticket
                                ticket.applyDiscount(carriageClass);    //apply discount
                                ticket.displayTicketDetails(chosenCarriage.getNumber(), chosenSeat);    //display infos about the ticket
                                ticket.saveTicketToFile(train.getCarriagesCount(), chosenSeat);    //save ticket to file
                                chosenCarriage.reduceFreeSeats(chosenCarriage);         //freeSeats-- after buying a ticket
                            }
                            else
                            {
                                cout << "There are no free seats in the selected carriage." << endl;
                            }
                            break;
                        }
                    }

                    if (!found)
                    {
                        cout << "Train with ID " << searchByID << " was not found." << endl;
                    }
                }
                break;
            }
            case 0:
            {
                // Display all available trains
                cout << "Choose a train (ID):" << endl;
                for (const auto& train : trains) {
                    cout << "Train with ID: " << train.getID() << ", Route: " << train.getRoute() << endl;
                }

                int IDTrain;
                cin >> IDTrain;

                //Find the chosen train
                Train chosenTrain;
                bool found = false;
                for (const auto& train : trains)
                {
                    if (train.getID() == IDTrain)
                    {
                        chosenTrain = train;
                        found = true;
                        break;
                    }
                }

                if (found)   //if train found
                {
                    chosenTrain.generateRandomCarriages(); // generate and display all the wagons

                    cout << "Select the desired carriage class (1 for First Class, 2 for Second Class): ";
                    int carriageClass;
                    cin >> carriageClass;

                    // Verify the validity of the class
                    if (carriageClass != 1 && carriageClass != 2)   //the only available classes are 1 and 2
                    {
                        cout << "Invalid class selected. Please choose either 1 or 2." << endl;
                        break;
                    }

                    vector<Carriage> filteredCarriages;        //search in available carriges and random choose a wagon
                    for (const auto& carriage : chosenTrain.getCarriages())
                    {
                        if (carriage.getCarriageClass() == carriageClass)   //ff there is a carriage with the specified class
                        {
                            filteredCarriages.push_back(carriage);    //add it in the filtered carriages vector
                        }
                    }

                    // Verify if there are available wagons for the wanted class
                    if (filteredCarriages.empty())
                    {
                        cout << "No carriages available for the selected class." << endl;
                        break;
                    }

                    //random choose a wagon from the ones available
                    int chosenCarriageIndex = rand() % filteredCarriages.size();
                    Carriage& chosenCarriage = filteredCarriages[chosenCarriageIndex];

                    // Choose a seat (random) - if the is any available
                    int occupiedSeat = chosenCarriage.getOccupiedSeats();
                    int freeSeat = chosenCarriage.getFreeSeats();
                    if (freeSeat > 0)
                    {
                        int chosenSeat = rand() % freeSeat + 1; // Random seat index
                        // Create a ticket
                        cout << "Select passenger category (1-Student, 2-Child, 3-Pensioner, 4-Advance, 0-None): ";
                        int choice;
                        cin >> choice;

                        string passengerCategory;
                        switch (choice)
                        {
                        case 1:
                            passengerCategory = "Student";
                            break;
                        case 2:
                            passengerCategory = "Child";
                            break;
                        case 3:
                            passengerCategory = "Pensioner";
                            break;
                        case 4:
                            passengerCategory = "Advance";
                            break;
                        case 0:
                            passengerCategory = "None";
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                            return 1;
                        }

                        Ticket ticket(basePrice * chosenTrain.getKilometers(), "Purchased", chosenTrain.getRoute(), chosenTrain.getID(), passengerCategory); // price is an exemple-50

                        // Infos about ticket
                        ticket.applyDiscount(carriageClass);    //apply discount
                        ticket.displayTicketDetails(chosenCarriage.getNumber(), chosenSeat);    //display infos about the ticket
                        ticket.saveTicketToFile(chosenTrain.getCarriagesCount(), chosenSeat);    //save ticket to file
                        chosenCarriage.reduceFreeSeats(chosenCarriage);         //freeSeats-- after buying a ticket
                    }
                    else
                    {
                        cout << "There are no free seats in the selected carriage." << endl;
                    }
                }
                else
                {
                    cout << "Train with ID " << IDTrain << " was not found." << endl;
                }
                break;
            }
            default:
                cout << "Invalid option,please try again." << endl;
                break;
            }
            break;
        }

        case 4:
        {
            ifstream inFile("ticket.txt");
            if (inFile.is_open()) {
                string line;
                cout << "Your purchased tickets:\n";
                while (getline(inFile, line)) {
                    cout << line << "\n";
                }
                inFile.close();
            }
            else {
                cout << "No tickets purchased yet or file missing.\n";
            }
            break;
        }
        case 5:
        {
            cout << "Thank you for using the train booking system!" << endl;
            break;
        }

        default:
        {
            cout << "Invalid option!!!\n";
            break;
        }
        }
    }

    // Close the file
    File.close();
    system("PAUSE");
    return 0;
}