/*
Rebecca Aloisio
CSCI 230 002
4/25/2018
Assignment #7
Tests the StackT class
*/

#include "stack.h"
#include "rational.h"
#include <iostream>
    using namespace std;

int main(){
    StackT s;
    int i;
    
    for(i = 0; !s.IsFull() ; i++){
        RationalT a(i);
        s.Push(a);
        cout << (s.Top()).Value() << endl;
        cout << "S's size is: " << s.Size() << endl;
    }
    
    cout << endl << "Stack is full" << endl << endl;
    
    while(!s.IsEmpty()){
        cout << (s.Pop()).Value() << endl;
        cout << "S's size is: " << s.Size() << endl;
    }
    
    cout << endl << "Stack is empty" << endl << endl;

    return 0;
}
