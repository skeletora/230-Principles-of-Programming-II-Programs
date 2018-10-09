/*
Rebecca Aloisio
CSCI 230 002
4/11/2018
Assignment #6
*/

#include "car.h"
#include <iostream>
#include <string>
    using namespace std;

std::string CarTToString(const CarT& c){
    std::string info;
    
    info = c.name + ", ";
    info += DestinationTToString(c.destination);
    
    return info;
}



CarT StringToCarT(const std::string& car){
    CarT newCar;
    size_t posCol;
    DestinationT destination;
    
    posCol = car.std::string::find(":");
    
    if(posCol != std::string::npos){
        newCar.name = car.std::string::substr(0, posCol);
        destination = StringToDestinationT(car.std::string::substr(posCol + 1, std::string::npos));
        newCar.destination = destination;
    } else{
        std::cout << "Invalid format for car information." << std::endl << std::endl;
    }
    
    return newCar;
}



bool IsSmaller(const CarT& a, const CarT& b){
    bool smaller = false;
    
    if(CarDestination(a) < CarDestination(b)){
        if(CarDestination(a) != DestinationT::UNKNOWN and CarDestination(b) != DestinationT::UNKNOWN){
            smaller = true;
        }
    }
    
    return smaller;
}



std::string CarName(const CarT& c){
    return c.name;
}



DestinationT CarDestination(const CarT& c){
    return c.destination;
}



void ReverseCSV(std::string& s){
    string temp = "";
    size_t current = 0;
    size_t previous = 0;
    int i = 0;
    
    current = s.find(',');
    
    while(s != ""){
        for(i = 0; current != string::npos; i++){
            previous = current;
            current = s.find(',', previous + 1);
        }
    
        if(i == 0){
            temp = temp + s.substr(previous, current);
            s = "";
        } else if(previous == 0){
            temp = temp + s.substr(previous, current);
            s = "";
        } else{
            temp = temp + s.substr(previous + 1, current);
            temp = temp + ',';
            s = s.substr(0, previous);
            previous = 0;
            current = 0;
        }
    }

    s = temp;
    
    return;
}



CarT CSVToCarT(std::string& s){
    size_t posCom;
    CarT car;
    
    posCom = s.find(',');
    if(posCom != string::npos and s != ""){
        car = StringToCarT(s.substr(0, posCom));
        s = s.substr(posCom + 1, string::npos);
    } else if(posCom == string::npos and s != ""){
        car = StringToCarT(s.substr(0, posCom));
        s = "";
    } else{
        car = ERROR_CAR;
    }
    
    
    return car;
}
