#ifndef TRAIN_H
#define TRAIN_H

#include <iostream>
#include <vector>
#include <string>
#include "station.h"
#include "carriage.h"

using namespace std;

class Train
{
private:
	string trainType;
	int id;
	string route;
	int carriageCount;  //num of wagons
	float kilometers;
	string departureTime;
	string arrivalTime;
	vector<Station> intermediateStations;

	// For carriages
	vector<Carriage> carriages;

public:
	// Constructors:

	// Default constructor
	Train();

	// Constructor with parameters
	Train(const string& trainType, const int id, const string& route, int carriageCount, float kilometers, const string& departureTime, const string& arrivalTime, const vector<Station>& intermediateStations);

	// Getters & Setters
	string getType() const;
	void setType(string trainType);

	int getID() const;
	void setID(int id);

	string getRoute() const;
	void setRoute(string route);

	float getKilometers() const;
	void setKilometers(float kilometers);

	string getDepartureTime() const;
	void setDepartureTime(string departureTime);

	string getArrivalTime() const;
	void setArrivalTime(string arrivalTime);

	//void saveToFile(std::ofstream& outFile);

	void display() const;

	static vector<Train> readFromFile(ifstream& file);

	// Extraction operator for reading a train from file
	friend istream& operator>>(istream& in, Train& train)
	{
		in >> train.trainType >> train.id >> train.route >> train.carriageCount >> train.kilometers >> train.departureTime >> train.arrivalTime;
		return in;
	}

	// For carriages
	int getCarriagesCount() const;   //num of carriges(from file)
	const vector<Carriage>& getCarriages() const;
	void generateRandomCarriages();   // Function for generating carriages

	//For stations
	vector<Station> getStations() const;
	void setStations(const std::vector<Station>& intermediateStations);
	string getArrivalTimeForStation(const string& stationName) const;
};
#endif
