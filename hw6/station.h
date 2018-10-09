#ifndef STATION_DOT_H
#define STATION_DOT_H

#include "spur.h"
#include <string>

const int TOTAL_YARDS = NAMET_COUNT;

struct StationT{
    DestinationT location;
    SpurT yards[TOTAL_YARDS];
};

//initializes all of the yards in the station
void InitStationT(StationT& s);
//sets the location/name of the station
void NameStation(StationT& s, std::string& name);
//handles a train arriving at the station
void Arrive(StationT& s, std::string& name, std::string& trains);
//Adds cars to the train on the specified spur
void AddCarTs(StationT& s, size_t spur, std::string& cars);
//Empties yard
void ResetYard(StationT& s);
//Resets the specified spur
void Depart(StationT& s, std::string& name);
///Sorts the cars on the given spur using the spur and yard
void Sort(StationT& s, std::string name);
//Moves all cars from the source spur to the destination spur
void Move(StationT& s, std::string source, std::string destination);
//Prints all the cars of the given spur
void Print(const StationT& s, std::string name);


#endif
