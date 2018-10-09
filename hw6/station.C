/*
Rebecca Aloisio
CSCI 230 002
4/14/2018
Assignment #6
*/

#include "station.h"
#include "car.h"
#include <string>
#include <iostream>
#include <iomanip>
    using namespace std;

void InitStationT(StationT& s){
    size_t i;
    
    s.location = FIRST_DESTINATION;
    
    for(i = 0; i < TOTAL_YARDS; i++){
        s.yards[i].name = NameT(i);
        InitStack(s.yards[i].trains);
    }
    
    return;
}



void NameStation(StationT& s, string& name){
    s.location = StringToDestinationT(name);
    
    return; 
}



size_t FindSpur(const StationT& s, NameT n){
//Description: Returns the index of a spur in the station
    size_t i;
    bool found = false;
    
    for(i = 0; i < TOTAL_YARDS and not found; i++){
        if(n == s.yards[i].name){
            found = true;
        }
    }
    
    if(not found){
        i = string::npos;
    }
    
    return i - 1;
}




void Announce(SpurT& moving, SpurT& still, bool arrive){
//Description: Displays the movement of cars
    if(arrive){
        cout << "Remove " << CarName(Top(moving.trains)) << " from the arriving train and place it on the " << NameTToString(still.name) << " spur." << endl;
    } else{
        cout << "Remove " << CarName(Top(moving.trains)) << " from the " << NameTToString(moving.name) << " spur and place it on the " << NameTToString(still.name) << " spur." << endl;
    }
    
    return;
}



void MoveYard(SpurT& moving, SpurT& still, bool arrive, size_t noCars){
//Description: moves cars between two spurs
    size_t i;
    
    for(i = 0; not IsEmpty(moving.trains) and i < noCars; i++){
        Announce(moving, still, arrive);
        Push(still.trains, Pop(moving.trains));
    }
    
    return;
}



void Arrive(StationT& s, std::string& name, std::string& trains){
    NameT id;
    size_t spur;
    size_t yard;
    bool arrive = true;
    
    id = StringToNameT(name);
    spur = FindSpur(s, id);
    yard = FindSpur(s, NameT::YARD);
    
    //moves any cars that may already be on the spur to yard
    if(Size(s.yards[spur].trains) > 0){
        MoveYard(s.yards[spur], s.yards[yard], false, Size(s.yards[spur].trains));
    }
    
    AddCarTs(s, spur, trains);
    
    MoveYard(s.yards[spur], s.yards[yard], arrive, Size(s.yards[spur].trains));
    MoveYard(s.yards[yard], s.yards[spur], false, Size(s.yards[yard].trains));
    
    return;
    
}



void AddCarTs(StationT& s, size_t spur, string& cars){
    size_t i;
    
    for(i = Size(s.yards[spur].trains); i < MAX_ITEMS and cars != ""; i++){
        Push(s.yards[spur].trains, CSVToCarT(cars));
    }
    
    return;
}



void ResetYard(StationT& s){
    s.yards[FindSpur(s, NameT::YARD)].trains.size = 0;
    return;
}
    
    

void Depart(StationT& s, string& name){
    NameT spur;
    
    spur = StringToNameT(name);
    
    s.yards[FindSpur(s, spur)].trains.size = 0;
    
    return;
}



void Sort(StationT& s, std::string name){
    NameT spur;
    size_t source;
    size_t local;
    size_t yard;
    
    spur = StringToNameT(name);
    source = FindSpur(s, spur);
    local = FindSpur(s, NameT::LOCAL);
    yard = FindSpur(s, NameT::YARD);
    
    MoveYard(s.yards[local], s.yards[source], false, Size(s.yards[local].trains));
    

    while(not IsEmpty(s.yards[source].trains)){
        MoveYard(s.yards[source], s.yards[local], false, 1);
        if(CarDestination(Top(s.yards[local].trains)) != s.location){
            while(not IsEmpty(s.yards[yard].trains) and IsSmaller(Top(s.yards[yard].trains), Top(s.yards[local].trains))){
                MoveYard(s.yards[yard], s.yards[source], false, 1);
            }
            MoveYard(s.yards[local], s.yards[yard], false, 1);
        }
    }
    
    MoveYard(s.yards[yard], s.yards[source], false, Size(s.yards[yard].trains));
    
    return;
}



void Move(StationT& s, std::string source, std::string destination){
    NameT srcName;
    NameT destName;
    size_t src;
    size_t dest;
    
    srcName = StringToNameT(source);
    destName = StringToNameT(destination);
    src = FindSpur(s, srcName);
    dest = FindSpur(s, destName);
    
    MoveYard(s.yards[src], s.yards[dest], false, Size(s.yards[src].trains));
    
    return;
}



void Print(const StationT& s, std::string name){
    NameT sprName;
    SpurT spur;
    size_t yard;

    
    sprName = StringToNameT(name);
    yard = FindSpur(s, sprName);
    spur = s.yards[yard];
    
    
    while(not IsEmpty(spur.trains)){
        cout << "\t" << CarTToString(Pop(spur.trains)) << endl;
    }
    
    return;
}
