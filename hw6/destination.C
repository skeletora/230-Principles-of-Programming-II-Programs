/*
Rebecca Aloisio
CSCI 230 002
4/10/18
Assignment #6
This program handles managing functions dealing with destinations.
*/

#include "destination.h"
#include <iostream>

DestinationT NextDestination(DestinationT dest){
    if(dest != LAST_DESTINATION){
        dest = DestinationT(int(dest) + 1);
    }
    
    return dest;
}



DestinationT PrevDestination(DestinationT dest){
    if(dest != FIRST_DESTINATION){
        dest = DestinationT(int(dest) - 1);
    }
    
    return dest;
}



std::string DestinationTToString(DestinationT dest){
    std::string name;
    
    name = DESTINATION_NAMES[int(dest)];
    
    return name;
}



DestinationT StringToDestinationT(std::string name){
    std::size_t i;
    bool space = false;
    bool determined = false;
    std::string temp;
    DestinationT dest = DestinationT::UNKNOWN;
    
    for(i = 0; i < name.size(); i++){
        if(i != 0 and isalpha(name[i]) and !space){
            temp += tolower(name[i]);
        } else if(isalpha(name[i])){
            temp += toupper(name[i]);
            space = false;
        } else{
            temp += name[i];
            space = true;
        }
    }
    

    
    for(i = 0; i <= DESTINATION_COUNT and not determined; i++){
        if(temp == DESTINATION_NAMES[i]){
            dest = DestinationT(i);
            determined = true;
        }
    }
    
    return dest;
}



DestinationT RandomDestination(void){
    return DestinationT(drand48()*DESTINATION_COUNT);
}
