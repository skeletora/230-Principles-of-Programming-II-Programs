/*
Rebecca Aloisio
CSCI 230 002
2/21/18
Assignment #3
Calculates values using Ackermann's function and makes a table of the values.
*/
#include <iostream>
#include <iomanip>
	using namespace std;

long Ackermann(int m, int n);

const int MAX_M = 3;
const int MAX_N = 4;
	
int main(){
    //stores the value of Ackermann's function
	long value = 0;
	//Both hold values to be used in Ackermann's function
    int m = 0;
	int n = 0;
	
	//This creates the column headings
	if(m == 0 and n == 0){
		cout << " m\\n |";
		for(n = 0; n <= MAX_N; n++){
			cout << setw(6) << n;
		}
		
		cout << endl << setfill('-') << setw(6) << "+";
		for(n = 0; n <= MAX_N; n++){
			cout << setw(6) << "-";
		}
		cout << endl << setfill(' ');
	}
	//This fills in the table
	for(m = 0; m <= MAX_M; m++){
		cout << setw(4) << m << " |";
		for(n = 0; n <= MAX_N ; n++){
			value =  Ackermann(m, n);
			
			cout << setw(6) << value;
		}
		
		cout << endl;
	}
	
	return 0;
}



long Ackermann(int m, int n){
//Description: Calculates values using Ackermann's function
//Input: m & n - two integers that are required to calculate
//  values in Ackermann's function.
    //Stores the result of the function
	long value;
	
	if(m == 0){
		value = n + 1;
		return value;
	} else{
		if(m > 0 and n == 0){
			return Ackermann(m - 1, 1);
		} else{
			return Ackermann(m - 1, Ackermann(m, n - 1));
		}
	}
	
	return value;
}
