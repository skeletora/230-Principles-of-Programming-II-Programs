/*
Rebecca Aloisio
CSCI 230 002
2/21/18
Assignment #3
Calculates Fibonacci numbers through both looping and recursion in order to
    demonstrate how inefficient recursion is.
*/
#include <iostream>
#include <iomanip>
#include <time.h>
	using namespace std;

int NumberOfFib();
long RecursiveFib(int n, long& count);
long LoopingFib(long& oldest, long& old, long count);
void TimeCalc(clock_t start, clock_t stop);
void PrintResults(int i, long number, long count, char type);

const int US_TO_SEC = 1000000;

int main() {
    //Stores the number of Fibonacci numbers the user wants
	int number;
	//Loop control variable
	int i;
	//Keeps track of the number of recursive calls made
	long count = 0;
	//Stores the Fibonacci number value so that it can be properly outputted
    long temp;
	//Stores the value of the Fibonacci number two times the current number's predecessor
	long oldest = 1;
	//Stores the value of the Fibonacci number that is the current's predecessor
	long old = 1;
	//Stores the start time for calculating the Fibonacci numbers
	clock_t start;
	//Stores the end time for calculating the Fibonacci numbers
	clock_t stop;
	//stores the type of call being made
	char type;
	
	number = NumberOfFib();
   
	start = clock();
	
	//Calculates Fibonacci numbers recursively
	cout << "Recusive version" << endl;
	for(i = 1; i <= number; i++) {
        count = 0;
		type = 'r';
        temp = RecursiveFib(i, count);
		PrintResults(i, temp, count, type);
	}
	stop = clock();
	
	TimeCalc(start, stop);
	
	start = clock();
	
	//Calculates Fibonacci numbers through looping
	cout << endl << "Non-recursive version" << endl;
	count = 0;
	for(i = 1; i <= number; i++) {
		type = 'l';
		if(i >= 3){
			count++;
			temp = LoopingFib(old, oldest, count);
			PrintResults(i, temp, count, type);
		}
		else{
			PrintResults(i, oldest, count, type);
		}
	}
	stop = clock();
	
	TimeCalc(start, stop);

	return 0;
}



int NumberOfFib(){
//Description: Prompts the user for the number of Fibonacci numbers they would like
//  and returns an integer of the value they enter
//Variables: number
	//The number of Fibonacci numbers the user wants
	int number;
	
	cout << "Enter the number of Fibonacci numbers you would like calculated: ";
	cin >> number;
	
	return number;
}




long RecursiveFib(int n, long& count){
//Description: Recursively calculates Fibonacci numbers
//Input: n - the number of desired Fibonacci numbers
//      count - the number of times the function has been called

	count++;
	if (n == 1 or n == 2) {
		return 1;
	}

	return RecursiveFib(n-1, count) + RecursiveFib(n-2, count);
}



long LoopingFib(long& oldest, long& old, long count){
//Description: Calculates Fibonacci numbers through looping
//Input: number - the number of Fibonacci numbers to be calculated
//Variables: i, fib, oldest, old
	//Stores the value of the current Fibonacci number
	long fib;

		fib = old + oldest;
			
		if(count % 2 == 0){
			oldest = fib;
		} else{
			old = fib;
		}
	
	return fib;
}



void PrintResults(int i, long number, long count, char type){
//Description: Outputs information about the current Fibonacci number
//Input: i - the current Fibonacci number being calculated,
//		number - the value of the Fibonacci number, count - the number
//		of iterations in the calculation, type - the method used to calculate
//		the number.
	cout << "Fib(" << i << ")" << " = " << number;
	if(type == 'r'){
		cout << " calls " << count << endl;
	}
	else{
		cout << " loops " << count << endl;
	}
	
	return;
}



void TimeCalc(clock_t start, clock_t stop){
//Description: Calculates the time it took for a function to run and outputs it
//  in seconds.
//Input: start - a clock_t that contains the start time of the calculation
//		stop - a clock_t that contains the stop time of the calculation
	//Stores the total time for calculating the Fibonacci numbers
	clock_t time;

	time = stop - start;
	
	cout << "That took " << time  << " microseconds or " << time/US_TO_SEC 
		<< " seconds." << endl;
		
	return;
}
