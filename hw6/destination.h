#ifndef DESTINATION_DOT_H
#define DESTINATION_DOT_H

#include <string>

//This stores the destinations that the cars can be shipped to
enum struct DestinationT:char {ALBION, BRADFORD, CAMBRIDGESPRINGS, EDINBORO, ERIE, UNKNOWN};
const std::string DESTINATION_NAMES[] = {"Albion", "Bradford", "Cambridge Springs", "Edinboro", "Erie", "UNKNOWN"};

const DestinationT FIRST_DESTINATION = DestinationT::ALBION;
const DestinationT LAST_DESTINATION = DestinationT::UNKNOWN;

const int DESTINATION_COUNT = int(LAST_DESTINATION) - int(FIRST_DESTINATION);

//Returns the next destination of the DestinationT type
DestinationT NextDestination(DestinationT dest);
//Returns the previous destination of the DestinationT type
DestinationT PrevDestination(DestinationT dest);
//Converts a DestinationT to a String
std::string DestinationTToString(DestinationT dest);
//Converts a string to a DestinationT
DestinationT StringToDestinationT(std::string name);
//Assigns a random DestinationT value
DestinationT RandomDestination(void);

#endif
