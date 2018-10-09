/*
Rebecca Aloisio
CSCI 230 002
4/14/2018
Assignment #6
*/

#include "spur.h"
#include "car.h"
#include <string>
#include <iomanip>
    using namespace std;
    
string NameTToString(const NameT n){
    return NAMET_NAMES[int(n)];
}



NameT StringToNameT(string& name){
    size_t i;
    bool found = false;
    NameT spur = NameT::UNKNOWN;
    string temp;
    
    for(i = 0; i < name.size(); i++){
        if(i != 0 and isalpha(name[i])){
            temp += tolower(name[i]);
        } else if(isalpha(name[i])){
            temp += toupper(name[i]);
        } else{
            temp += name[i];
        }
    }
    
    for(i = 0; i < NAMET_COUNT and not found; i++){
        if(temp == NAMET_NAMES[i]){
            found = true;
            spur = NameT(i);
        }
    }
    
    return spur;
    
}



string SpurTName(const SpurT s){
    return NameTToString(s.name);
}



void InitSpur(SpurT& s){
    s.name = FIRST_NAME;
    InitStack(s.trains);
    
    return;
}
