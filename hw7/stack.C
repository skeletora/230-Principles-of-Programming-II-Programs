/*
Rebecca Aloisio
CSCI 230 002
4/24/2018
Assignment #7
Manages the functions relating to the StackT class
*/

#include "stack.h"
#include <iostream>
using namespace std;

StackT::StackT(){
    size = 0;
    
    return;
}



void StackT::Push(ItemT i){
    if(size < STACK_MAX){
        data[size] = i;
        size++;
    } else{
    }
    
    return;
}


//Might need to add NO_ITEM back to else
ItemT StackT::Pop(void){
    ItemT item;
    
    if(size > 0){
        size--;
        item = data[size];
    } else{
        item = NO_ITEM;
    }
    
    return item;
}


//Might need to add NO_ITEM back to else
ItemT StackT::Top(void) const{
    ItemT item;
    
    if(size > 0){
        item = data[size - 1];
    }
    
    return item;
}



int StackT::Size(void) const{
    return size;
}



bool StackT::IsEmpty(void) const{
    bool empty = false;
    
    if(size == 0){
        empty = true;
    }
    
    return empty;
}



bool StackT::IsFull(void) const{
    bool full = false;
    
    if(size == STACK_MAX){
        full = true;
    }
    
    return full;
}
