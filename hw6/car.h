#ifndef CAR_DOT_H
#define CAR_DOT_H

#include <string>
#include "destination.h"

struct CarT{
    std::string name;
    DestinationT destination;
};

const CarT ERROR_CAR {"ERROR", DestinationT::UNKNOWN};

//Returns a string containing the car name and destination
std::string CarTToString(const CarT& c);
//Turns a string into a CarT
CarT StringToCarT(const std::string& car);
//Determines if a car has the "lesser" destination
bool IsSmaller(const CarT& a, const CarT& b);
//Returns the name of the car
std::string CarName(const CarT& c);
//Returns the destination of a car
DestinationT CarDestination(const CarT& c);
//Reverses the trains
void ReverseCSV(std::string& s);
//Turns a CSV into a CarT
CarT CSVToCarT(std::string& s);

#endif
