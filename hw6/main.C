/*
Rebecca Aloisio
CSCI 230 002
4/12/2018
Assignment #6
This program simulates a switching yard of a railroad company.  It also
    provides the programmer with experience with structs and stacks.
*/

#include "destination.h"
#include "car.h"
#include "stack.h"
#include "spur.h"
#include "station.h"
#include <iostream>
#include <fstream>
#include <time.h>
    using namespace std;

    
void OpenFile(ifstream& inFile, string& fileName, bool& exist);
void DecodeAction(string action, string& command, string& trainList, string& spurName1, string& spurName2);
void Capitalize(string& action);
void ExCommand(StationT& station, string& action, string& command, string& trainList, string& spurName1, string& spurName2, bool& exit);
void Exit(bool& exit);

    
int main(){
    bool exit = false;
    ifstream inFile;
    string fileName;
    StationT station;
    string stationLocation;
    string action;
    string command;
    string spurName1;
    string spurName2;
    string trainList;
    
    srand48(time(nullptr));
    
    InitStationT(station);
    
    OpenFile(inFile, fileName, exit);
    
    getline(inFile, stationLocation);
    NameStation(station, stationLocation);
    
    while(inFile and not exit){
        getline(inFile, action);
        DecodeAction(action, command, trainList, spurName1, spurName2);
        
        ExCommand(station, action, command, trainList, spurName1, spurName2, exit);
    }
    
    
    inFile.close();
    
    return 0;
}



void OpenFile(ifstream& inFile, string& fileName, bool& exit){
    cout << "Enter the file name => ";
    cin >> fileName;
    cout << endl;
    
    inFile.open(fileName.c_str());
    
    if(not inFile){
        cout << "The file " << fileName << " does not exist." << endl;
        exit = false;
    }
    
    return;
}



void DecodeAction(string action, string& command, string& trainList, string& spurName1, string& spurName2){
    size_t pos;
    string temp;

    pos = action.find(' ');
    command = action.substr(0, pos);
    action = action.substr(pos + 1, string::npos);
    
    Capitalize(command);
    
    if(command == "EXIT"){
        return;
    } else if(command == "ARRIVE"){
        pos = action.find(' ');
        spurName1 = action.substr(0, pos);
        spurName1 = NameTToString(StringToNameT(spurName1));
        action = action.substr(pos + 1, string::npos);
        trainList = action;
        ReverseCSV(trainList);
    } else if(command == "DEPART" or command == "SORT" or command == "PRINT"){
        spurName1 = action;
        spurName1 = NameTToString(StringToNameT(spurName1));
    } else if(command == "MOVE"){
        pos = action.find(' ');
        spurName1 = action.substr(0, pos);
        spurName1 = NameTToString(StringToNameT(spurName1));
        action = action.substr(pos + 1, string::npos);
        spurName2 = action;
        spurName2 = NameTToString(StringToNameT(spurName2));
    } else{
        cout << "Invalid command" << endl << endl;
    } 
    
    return;
}



void Capitalize(string& action){
    string temp;
    size_t i;
    
    for(i = 0; i < action.size(); i++) {
        if (action[i] != ' ') {
            temp += toupper(action[i]);
        }
        else{
            temp += action[i];
        }
    }
	 
    action = temp;
	 
    return;
}



void ExCommand(StationT& station, string& action, string& command, string& trainList, string& spurName1, string& spurName2, bool& exit){
    cout << "Executing " << action << endl;
    
    if(command == "EXIT"){
        Exit(exit);
        cout << "Thank you for using the " << DestinationTToString(station.location) << " Switching Station" << endl;
        
    } else if(command == "ARRIVE"){
        cout << "New train arriving on the " << spurName1 << " spur." << endl;
        Arrive(station, spurName1, trainList);
        
    } else if(command == "DEPART"){
        cout << "A train departs from the " << spurName1 << " spur." << endl;
        Depart(station, spurName1);
        
    } else if(command == "SORT"){
        cout << "Sorting the " << spurName1 << " spur." << endl;
        Sort(station, spurName1);
        
    } else if(command == "MOVE"){
        cout << "Moving from the " << spurName1 << " spur to the " << spurName2 << " spur." << endl;
        Move(station, spurName1, spurName2);
        
    } else if(command == "PRINT"){
        cout << "The " << spurName1 << " spur contains:" << endl;
        Print(station, spurName1);
    }
    
    ResetYard(station);
    
    cout << endl;
    
    return;
}

void Exit(bool& exit){
    exit = true;
    
    return;
}
