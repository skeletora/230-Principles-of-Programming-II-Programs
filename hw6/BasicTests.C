#include <iostream>
#include "destination.h"
#include "car.h"
#include "stack.h"

using namespace std;

int main() {

     DestinationT d;
     CarT c1,c2;

     StackT s;
     InitStack(s);

     string tmp;

     for(d= FIRST_DESTINATION; d < LAST_DESTINATION; d = NextDestination(d)) {
         cout << DestinationTToString(d) << " ";
     }

     cout << endl << endl;

     for(d=LAST_DESTINATION; d > FIRST_DESTINATION; d = PrevDestination(d)) {
         cout << DestinationTToString(d) << " ";
     }
     cout << DestinationTToString(d);

     cout << endl << endl;

     tmp = "A:Edinboro";
     c1 = StringToCarT(tmp);
     cout << CarTToString(c1) << endl;
     cout << CarName(c1) << endl;
     cout << DestinationTToString(CarDestination(c1)) << endl;


     tmp = "B:Erie";
     c2 = StringToCarT(tmp);
     if (IsSmaller(c1,c2)) {
       cout << CarTToString(c1) << " is smaller than " << CarTToString(c2)
            << endl;
     }

     cout << endl;
    
     Push(s,c1);
     c2= Top(s);
     c1 = Pop(s);
     cout << "The stack has size " << Size(s) << endl;
     cout << "The stack ";

     if (IsFull(s)) {
        cout << "is " ;
     }
     cout << "full." << endl;

     if (IsEmpty(s)) {
        cout << "is " ;
     }
     cout << "empty." << endl;

     cout << endl;

     cout << ITEM_OVERFLOW_ERROR << endl;
     cout << NO_ITEM_ERROR << endl;
     cout << CarTToString(ERROR_CAR) << endl;
     cout << CarTToString(NO_ITEM) << endl;

     return 0;
}
