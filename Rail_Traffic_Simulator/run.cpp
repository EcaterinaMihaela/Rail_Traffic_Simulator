#include "run.h"
#include "ticket.h"
#include <fstream>

#define basePrice 1.6

void Run::CaseInfo(const vector<Train>& trains)
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
}

void Run::CaseChooseRoute(const vector<Train>& trains)
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
        string departureStation, arrivalStation;

        while (true)
        {
            cout << "Enter the number corresponding to the route: ";
            cin >> routeChoice;

            if (routeChoice >= 1 && routeChoice <= static_cast<int>(routes.size()))
            {
                // Store the selected departure/arrival stations
                departureStation = routes[routeChoice - 1].first;
                arrivalStation = routes[routeChoice - 1].second;
                break; // Exit the loop
            }
            else
            {
                cout << "\nInvalid choice! Please enter a number between 1 and " << routes.size() << ".\n";
            }
        }

        // Displaying the available trains for the selected route
        cout << "Available trains from \"" << departureStation << "\" to \"" << arrivalStation << "\":" << endl;
        bool found = false;

        // Looking for trains that travel the selected route
        for (const auto& train : trains)
        {
            const auto& stations = train.getStations();
            bool departureFound = false;

            for (const auto& station : stations)
            {
                if (station.getName() == departureStation)
                {
                    departureFound = true; // Departure station found
                }

                if (departureFound && station.getName() == arrivalStation)
                {
                    // Showing the train details
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
}

void Run::CaseBuyTicket(vector<Train>& trains)
{
    cout << "Welcome to the train ticket booking system!\n" << endl;
    cout << "Choose an option:" << endl;
    cout << "1 - Choose your desired route from the list of stations!" << endl;
    cout << "0 - Choose the desired train directly!" << endl;

    int subOption;
    cin >> subOption;
    cin.ignore();

    switch (subOption)
    {
    case 1:
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

        int routeChoice;

        while (true)
        {
            // Let the user select a route
            cout << "\nEnter the number corresponding to the route: ";
            cin >> routeChoice;

            if (routeChoice < 1 || routeChoice > static_cast<int>(routes.size()))
            {
                cout<<"\nInvalid choice! Please try again.";
            }
            else
            {
                cout << "You selected route: " << routes[routeChoice - 1].first
                    << " -> " << routes[routeChoice - 1].second << "\n";
                break; 
            }
        }

        // Store the selected departure/arrival stations
        string departureStation = routes[routeChoice - 1].first;
        string arrivalStation = routes[routeChoice - 1].second;

        // Display the advailable trains for the selected route
        cout << "\nAvailable trains from \"" << departureStation << "\" to \"" << arrivalStation << "\":" << endl;
        bool found = false;

        // Shearch for the trains 
        for (const auto& train : trains)
        {
            const auto& stations = train.getStations();
            bool departureFound = false;

            for (const auto& station : stations)
            {
                if (station.getName() == departureStation)
                {
                    departureFound = true; // departure station found
                }

                if (departureFound && station.getName() == arrivalStation)
                {
                    // Display train details
                    cout << "\n";
                    train.display();
                    found = true;
                    break;
                }
            }
        }

        if (!found)
        {
            cout << "There are not available trains from \"" << departureStation << "\" to \"" << arrivalStation << "\"!\n";
            break;
        }
        else
        {
            // After finding available trains on the choosen route,choose a train
            //Like in case 1,if train id found,generate a ticket
            cout << "If you want to continue buying the ticket from " << departureStation << " to " << arrivalStation << " , enter the ID of the desired train!\n";
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

                    cout << "\nSelect the desired carriage class (1 for First Class, 2 for Second Class): ";
                    int carriageClass;
                    cin >> carriageClass;

                    // Verify the validity of the class
                    if (carriageClass != 1 && carriageClass != 2)   //the only available classes are 1 and 2
                    {
                        cout << "\nInvalid class selected. Please choose either 1 or 2." << endl;
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
                        cout << "\nNo carriages available for the selected class." << endl;
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
                            break;
                        }

                        Ticket ticket(basePrice * train.getKilometers(), "Purchased", train.getRoute(), train.getID(), passengerCategory); // price is an exemple


                        // Infos about ticket
                        ticket.setTravelDate(train.getDepartureTime());
                        ticket.applyDiscount(carriageClass);    //apply discount
                        ticket.displayTicketDetails(chosenCarriage.getNumber(), chosenSeat, departureStation, arrivalStation,carriageClass);    //display infos about the ticket
                        ticket.saveTicketToFile(train.getCarriagesCount(), chosenSeat, departureStation, arrivalStation,carriageClass);    //save ticket to file
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
        for (const auto& train : trains)
        {
            cout << "Train with ID: " << train.getID() << ", Route: " << train.getRoute() << endl;
        }

        cout << "Choose a train (ID):" << endl;

        int IDTrain;
        cin >> IDTrain;

        //Find the chosen train
        Train chosenTrain;
        bool found = false;
        for (const auto& train : trains)
        {
            if (train.getID() == IDTrain)
            {
                train.display();
                chosenTrain = train;
                found = true;
                break;
            }
        }

        if (found)   //if train found
        {
            // Get all stations of the selected train
            const auto& allStations = chosenTrain.getStations();
            cout << "\nAvailable routes for train ID " << IDTrain << ":\n";

            // Show all intermediate route combinations
            int routeCounter = 1;
            for (size_t i = 0; i < allStations.size(); ++i)
            {
                for (size_t j = i + 1; j < allStations.size(); ++j)
                {
                    cout << routeCounter++ << ". " << allStations[i].getName() << " -> " << allStations[j].getName() << endl;

                }
            }

            // Choose the desired route
            cout << "\nSelect the desired route (enter the corresponding number): ";
            int routeChoice;
            cin >> routeChoice;

            // Validate the choice
            string departureStation, arrivalStation;
            routeCounter = 1;
            bool routeFound = false;
            for (size_t i = 0; i < allStations.size(); ++i)
            {
                for (size_t j = i + 1; j < allStations.size(); ++j, ++routeCounter)
                {
                    if (routeCounter == routeChoice)
                    {
                        departureStation = allStations[i].getName();
                        arrivalStation = allStations[j].getName();
                        routeFound = true;
                        break;
                    }
                }
                if (routeFound) break;
            }

            if (!routeFound)
            {
                cout << "Invalid route selection. Please try again." << endl;
                break;
            }

            // Shows the selected route
            cout << "You selected the route: " << departureStation << " -> " << arrivalStation << endl;


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
                if (carriage.getCarriageClass() == carriageClass)   //if there is a carriage with the specified class
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

            //Random choose a wagon from the ones available
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
                    break;
                }

                Ticket ticket(basePrice * chosenTrain.getKilometers(), "Purchased", chosenTrain.getRoute(), chosenTrain.getID(), passengerCategory); // price is an exemple-50

                // Infos about ticket
                ticket.setTravelDate(chosenTrain.getDepartureTime());
                ticket.applyDiscount(carriageClass);    //apply discount
                ticket.displayTicketDetails(chosenCarriage.getNumber(), chosenSeat, departureStation, arrivalStation,carriageClass);    //display infos about the ticket
                ticket.saveTicketToFile(chosenTrain.getCarriagesCount(), chosenSeat, departureStation, arrivalStation,carriageClass);    //save ticket to file
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
}

void Run::CaseMyTickets(const vector<Train>& trains)
{
    ifstream inFile("ticket.txt");      //display all my tickets i have been purchasing
    if (inFile.is_open())
    {
        string line;
        cout << "Your purchased tickets:\n";
        while (getline(inFile, line))
        {
            cout << line << "\n";
        }
        inFile.close();
    }
    else
    {
        cout << "No tickets purchased yet!\n";
    }
}

int Run::RunTheApp()
{
    ifstream File("trains.txt");
    if (!File)
    {
        cerr << "Could not open the file!" << endl;
        return 1;
    }

    // Reading trains from file
    vector<Train> trains = Train::readFromFile(File);

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
                break;
            }
        }

        switch (option)
        {
        case 1: // My train-INFO
        {
            Run::CaseInfo(trains);
            break;
        }

        case 2: // Choose route
        {
            Run::CaseChooseRoute(trains);
            break;
        }

        case 3: //Buy ticket
        {
            Run::CaseBuyTicket(trains);
            break;
        }
        case 4:
        {
            Run::CaseMyTickets(trains);
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
}