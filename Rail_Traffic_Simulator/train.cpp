#include "train.h"
#include <sstream>
#include <fstream>

Train::Train() : trainType(""), id(0), route(""), carriageCount(0), kilometers(0), departureTime(""), arrivalTime("") {}

Train::Train(const string& trainType, int id, const string& route, int carriageCount, float kilometers, const string& departureTime, const string& arrivalTime, const vector<Station>& intermediateStations)
    : trainType(trainType), id(id), route(route), carriageCount(carriageCount), kilometers(kilometers),
    departureTime(departureTime), arrivalTime(arrivalTime), intermediateStations(intermediateStations) {}

vector<Train> Train::readFromFile(ifstream& file)
{
    vector<Train> trains;
    string line;

    while (getline(file, line))
    {
        // Skip empty lines
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);

        // Read the first train information
        string trainType, departureTime, arrivalTime, route;
        int id, carriageCount;
        float kilometers;

        // Read train type, id, and number of carriages and kilometers
        ss >> trainType >> id;

        // Read the route, which in quotes
        getline(ss, route, '\"'); // Ignore the first double quote
        getline(ss, route, '\"'); // Read route up to the second double quote

        // Continue reading remaining information
        ss >> carriageCount >> kilometers >> departureTime >> arrivalTime;

        // Read stations
        vector<Station> intermediateStations;
        while (getline(file, line) && line != "STOP")
        {
            // Skip any empty lines between stations
            if (line.empty())
            {
                continue;
            }

            stringstream ss_station(line);
            string stationName, arrivalTimeForStation;
            int stationLine;

            getline(ss_station, stationName, ',');  // Read station name
            getline(ss_station, arrivalTimeForStation, ','); // Read arrival time
            ss_station >> stationLine; // Read station line

            // Add station to the vector
            intermediateStations.push_back(Station(stationName, arrivalTimeForStation, stationLine));
        }

        // Create Train object with all information
        Train train(trainType, id, route, carriageCount, kilometers, departureTime, arrivalTime, intermediateStations);

        // Add train to the list of trains
        trains.push_back(train);
    }

    return trains;
}


void Train::display() const
{
    cout << "\nTrain " << trainType << " " << id << ", operates on route " << route
        << ", with " << carriageCount << " carriages, covering a distance of "
        << kilometers << " kilometers.\nIt departs the station at "
        << departureTime << " and will arrive at the destination at "
        << arrivalTime << ".\n Intermediate stations: \n";

    if (intermediateStations.empty())
    {
        cout << "No intermediate stations." << endl;
    }
    else
    {
        for (const auto& station : intermediateStations)
        {
            cout << "- " << station.getName() << " at " << station.getArrivalTime()
                << " (line " << station.getStationLine() << ")\n";
        }
        cout << endl;
    }
}

string Train::getType() const
{
    return trainType;
}

void Train::setType(string trainType)
{
    this->trainType = trainType;
}

int Train::getID() const
{
    return id;
}

void Train::setID(int id)
{
    this->id = id;
}

string Train::getRoute() const
{
    return route;
}

void Train::setRoute(string route)
{
    this->route = route;
}

int Train::getCarriagesCount() const
{
    return carriageCount;  //num of Wagons-from file
}

float Train::getKilometers() const
{
    return kilometers;
}

void Train::setKilometers(float kilometers)
{
    this->kilometers = kilometers;
}

string Train::getDepartureTime() const
{
    return departureTime;
}

void Train::setDepartureTime(string departureTime)
{
    this->departureTime = departureTime;
}

string Train::getArrivalTime() const
{
    return arrivalTime;
}

void Train::setArrivalTime(string arrivalTime)
{
    this->arrivalTime = arrivalTime;
}

// For carriages
const vector<Carriage>& Train::getCarriages() const
{
    return carriages;
}

void Train::generateRandomCarriages()   //for entire train,generate and display all the carriages
{
    srand(static_cast<unsigned int>(time(0))); // seed random number generator
    cout << "\nThe available carriages for train " << getType() << " " << getID() << " are: \n" << endl;
    for (int i = 0; i < getCarriagesCount(); ++i)
    {
        int carriageClass = (rand() % 2) + 1; // Class 1 or 2
        int occupiedSeats = rand() % 107; // Occupied seats between 0 and 106
        Carriage generatedCarriage(i + 1, carriageClass, occupiedSeats, 106 - occupiedSeats); // Create carriage
        carriages.push_back(generatedCarriage); // Add carriage to vector

        // Display carriage information
        generatedCarriage.displayCarriages(); // Calls display method to show carriage details
    }
}

//For stations
vector<Station> Train::getStations() const
{
    return intermediateStations;
}

void Train::setStations(const std::vector<Station>& intermediateStations)
{
    this->intermediateStations = intermediateStations;
}


string Train::getArrivalTimeForStation(const string& stationName) const
{
    for (const auto& station : intermediateStations)  //search in intermediate sstations vector
    {
        if (station.getName() == stationName)   //if station found ,display arrival time
        {
            return station.getArrivalTime();
        }
    }
    return "N/A"; // If station not found
}