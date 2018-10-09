/*
Rebecca Aloisio
CSCI 230 002
3/9/18
Assignment #4
This is a program for a multi-base calculator.  It can perform base conversion and
	basic mathematics.  This program is also used to help familiarize the programmer
	with arrays.
*/
#include <string>
#include <iostream>
#include <cmath>
	using namespace std;

//The maximum number of memory locations
const int MAX_MEM = 26;
//The maximum number of digits that a number can be
const int MAX_DIG = 100;
//The smallest base
const int MIN_BASE = 2;
//the largest base
const int MAX_BASE = 36;	
	
void FetchCom(string& operation);
void Capitalize(string& phrase);
int DecodeCom(string& operation, string& command, string& num1, string& num2);
void ExecuteCom(int comVal, string& num1, string& num2, bool& on, long& base, long& base2, long& accumulator, long memory[]);

void CommandOff(bool& on);
void CommandReset(long memory[], long& accumulator, long& base);
void CommandSet(long& accumulator, long base, long& base2, long memory[], string& num1);
long TranslateValue(string value, long& base2, const long memory[], long& accumulator);
size_t Find(string phrase, string lookFor, size_t position);
string SubString(string phrase, size_t startPos, int length, char termChar);
long TranslateToNumber(string numStr, long base2);
string ConvertToBase(long base, long number);
void CommandDump(long memory[], long base);
void CommandBase(long& base, string num1);
void CommandLoad(long& accumulator, string num1, long memory[MAX_MEM], long base, long base2);
void CommandStore(long& accumulator, string num1, long memory[], long base);
void CommandPrint(long accumulator, long base);
void CommandAdd(long& accumulator, long memory[], long base, string num1, string num2);
void CommandSubtract(long& accumulator, long memory[], long base, string num1, string num2);
void CommandMult(long& accumulator, long memory[], long base, string num1, string num2);
void CommandDivide(long& accumulator, long memory[], long base, string num1, string num2);

int main(){
	//controls entering the loop
	bool on = true;
	//stores the command and the numbers that the calculator will operate on
    string operation;
	//stores the command that the calculator will perform
	string command;
	//stores the first number to been operated on
    string num1 = "";
	//stores the second number to be operated on
    string num2 = "";
	//stores a numerical value that represents a command
    int comVal;
	//the base the calculator is in
    long base;
	//the base the user enters
	long base2;
	//stores the last computed value
    long accumulator;
	//serves as memory and stores numbers
    long memory[MAX_MEM];
    
    CommandReset(memory, accumulator, base);
	
	while(on){
		FetchCom(operation);
        
        comVal = DecodeCom(operation, command, num1, num2);
        
        ExecuteCom(comVal, num1, num2, on, base, base2, accumulator, memory);
    }
	
	return 0;
}



void FetchCom(string& operation){
//Description: Gets the command and number and capitalizes it
//Input: operation - a string that contains the command, and possibly a number
    cout << "% ";
    getline(cin, operation);
        
    Capitalize(operation);
    
    return;
}
    


void Capitalize(string& phrase){
//Description: Capitalizes all the letters in a string
//Input: phrase -  a string containing what the calculator should be doing
	//stores the new string while it is being modified
    string temp = "";
	//stores the current letter while it is being changed
    char letter;
	//keeps track of the position in the phrase
    size_t i;
    
    for(i = 0; i < phrase.length(); i++){
        if(isalpha(phrase[i])){
            letter = toupper(phrase[i]);
            temp = temp + letter;
        }
        else{
            temp = temp + phrase[i];
        }
    }
    
    phrase = temp;
    
    return;
}



int DecodeCom(string& operation, string& command, string& num1, string& num2){
//Description: breaks down operation into a command and numbers
//Input: operation - a string that contains the command, and possibly a number,
//		command - a string that tells the calculator what to do,
//		num1 & num2 - a string containing the numbers being used in calculations
	//stores the position in the string
    size_t position;
	//keeps track of how long the string is
    size_t opSize = operation.size();
	//stores the command as an integer
    int comVal;
    
    command = SubString(operation, 0, 10, ' ');
    
    position = Find(operation, " ", 0) + 1;
    operation = SubString(operation, position, opSize, '\n');
    opSize = operation.size();
    
	if(command == "OFF"){
        comVal = 0;
    }
    else if(command == "RESET"){
        comVal = 1;
    }
    else if(command == "SET"){
        comVal = 2;
        num1 = SubString(operation, 0, opSize, '\n');
    }
    else if(command == "DUMP"){
        comVal = 3;
    }
    else if(command == "BASE"){
        comVal = 4;
        num1 = SubString(operation, 0, opSize, '\n');
    }
    else if(command == "LOAD"){
        comVal = 5;
        num1 = SubString(operation, 0, opSize, '\n');
    }
    else if(command == "STORE"){
        comVal = 6;
        num1 = SubString(operation, 0, opSize, '\n');
    }
    else if(command == "PRINT"){
        comVal = 7;
    }
    else if(command == "ADD"){
        comVal = 8;
        num1 = SubString(operation, 0, opSize, ' ');
        position = Find(operation, " ", 0) + 1;
        num2 = SubString(operation, position, opSize, '\n');
    }
    else if(command == "SUBTRACT"){
        comVal = 9;
        num1 = SubString(operation, 0, opSize, ' ');
        position = Find(operation, " ", 0) + 1;
        num2 = SubString(operation, position, opSize, '\n');
    }
    else if(command == "MULTIPLY"){
        comVal = 10;
        num1 = SubString(operation, 0, opSize, ' ');
        position = Find(operation, " ", 0) + 1;
        num2 = SubString(operation, position, opSize, '\n');
    }
    else if(command == "DIVIDE"){
        comVal = 11;
        num1 = SubString(operation, 0, opSize, ' ');
        position = Find(operation, " ", 0) + 1;
        num2 = SubString(operation, position, opSize, '\n');
    }
    else{
        comVal = 12;
    }
    
    return comVal;
}



void ExecuteCom(int comVal, string& num1, string& num2, bool& on, long& base, long& base2, long& accumulator, long memory[MAX_MEM]){
//Description: Executes the proper operation
//Input: comVal - an int that stores the command as an integer, num1 & num2 - a string
//		 containing the numbers being used in calculations, on - controls entering
//		 the loop, base - the base the calculator is in, base2 - the base the user enters
//		accumulator - stores the last computed value, memory - serves as memory and stores numbers
	if(comVal == 0){
        CommandOff(on);
    }
    else if(comVal == 1){
        cout << "Reset" << endl;
        CommandReset(memory, accumulator, base);
    }
    else if(comVal == 2){
        CommandSet(accumulator, base, base2, memory, num1);
    }
    else if(comVal == 3){
        CommandDump(memory, base);
    }
    else if(comVal == 4){
        CommandBase(base, num1);
    }
    else if(comVal == 5){
        CommandLoad(accumulator, num1, memory, base, base2);
    }
    else if(comVal == 6){
        CommandStore(accumulator, num1, memory, base);
    }
    else if(comVal == 7){
        CommandPrint(accumulator, base);
    }
    else if(comVal == 8){
        CommandAdd(accumulator, memory, base, num1, num2);
    }
    else if(comVal == 9){
        CommandSubtract(accumulator, memory, base, num1, num2);
    }
    else if(comVal == 10){
        CommandMult(accumulator, memory, base, num1, num2);
    }
    else if(comVal == 11){
        CommandDivide(accumulator, memory, base, num1, num2);
    }
    else{
        cout << "invalid command" << endl;
    }
    
    return;
}



void CommandOff(bool& on){
//Description: Ends the loop and turns “off” the calculator
//Input: on - controls entering the loop
    cout << "Exiting" << endl;
    on = false;
    
    return;
}



void CommandReset(long memory[MAX_MEM], long& accumulator, long& base){
//Description: : Resets the values in memory, the accumulator, and sets the base to 2
//Input: : memory – an array storing long data types, accumulator – stores the last 
//			value entered/calculated, base – stores the base the numbers are currently in
	//keeps track of the current position in the array
    size_t i;
    
    for(i = 0; i < MAX_MEM; i++){
        memory[i] = 0;
    }
    accumulator = 0;
    base = 2;
    
    return;
}



void CommandSet(long& accumulator, long base, long& base2, long memory[MAX_MEM], string& num1){
//Description: Sets the accumulator to be the specified value
//Input: num1 & num2 - a string containing the numbers being used in calculations, 
//		 on - controls entering the loop, base - the base the calculator is in, 
//		 base2 - the base the user enters, accumulator - stores the last computed value,
//		 memory - serves as memory and stores numbers 
	accumulator = TranslateValue(num1, base2, memory, accumulator);
	num1 = ConvertToBase(base, accumulator);
	
	cout << "$0=" << num1 << "@" << base << endl;
    
    return;
}



long TranslateValue(string value, long& base2, const long memory[MAX_MEM], long& accumulator){
//Description: Translates value from a string to a long
//Input: value – a string containing the value being stored into the accumulator, 
//		 base2 – the base the user entered, memory -  an array containing longs
	//The position in the string
    size_t position = 0;
	//The number that is returned
	long number = accumulator;
	//stores the new value while it is being calculated
	string temp;
    
    if(value[0] == '$'){
		if(value[1] != '0'){
			position = int(value[1]) - int('A');
            if(position < MAX_MEM){
                number = memory[position];
            }
		}
    }
    else{ 
        position = Find(value, "@", 1);
		if(position != string::npos){
			temp = SubString(value, position + 1, 2, ' ');
			base2 =  10;
			base2 = TranslateToNumber(temp, base2);
			if(value[0] == '-'){
				temp = SubString(value, 1, position - 2, '\n');
				number =  0 - TranslateToNumber(temp, base2);
			} else if(value[0] == '+'){
				temp = SubString(value, 1, position - 1, '\n');
				number = TranslateToNumber(temp, base2);
			} else{
				temp = SubString(value, 0, position - 1, '\n');
				number = TranslateToNumber(temp, base2);
			}
		}
		else{
			cout << "Invalid number" << endl;
		}
    }
    return number;
}



size_t Find(string phrase, string lookFor, size_t position){
//Description: Searches a phrase for lookFor and returns the 
//		position of the first character of the first instance
//Input: phrase – the string being searched, 
//		 lookFor – the string being searched for in phrase, 
//		 position – the position to start searching the string.
	//keeps track of the position in phrase
	size_t i;
	//keep track of the characters in lookFor that have been found
	size_t j = 0;
	
	for(i = position; i < phrase.size() and j < lookFor.size(); i++){
		if(phrase[i] == lookFor[0] && j == 0){
			position = i;
			j++;
		}
		else if(phrase[i] == lookFor[j]){
				j++;
		}
		else{
			j = 0;
		}
	}
	
	if(j == 0){
		position = string::npos;
	}
	
	return position;
}



string SubString(string phrase, size_t startPos, int length, char termChar){
//Description: Takes a starting position and length and returns that portion 
//			of the string phrase
//Input: phrase -  the string that a portion is being copied from, 
//		 startPos – a size_t that controls where in phrase the function starts 
//		 copying from, length -  an integer that states the size of the copied 
//		 string, termChar – a char that, if it is encountered, stops copying at 
//		 that position
	string subStr = "";
	size_t i;
	size_t stopPos = startPos + length;
	bool found = false;
	
	
	for(i = startPos; i < phrase.size() and i <= stopPos and not found; i++){
		if(phrase[i] != termChar){
			subStr = subStr + phrase[i];
		}
		else{
			found = true;
		}
	}
	
	return subStr;
}



long TranslateToNumber(string numStr, long base2){
//Description: Turns the value listed in the string into a long
//Input: numStr -  the number in string form, base2 - the base
//		 entered by the user
	int numOfPlaces = numStr.size();
	int i;
	int j;
	long digits[MAX_DIG];
	long number = 0;
    long finalNum = 0;
    
	
	for(i = numOfPlaces - 1, j = 0; i >= 0 and j < MAX_DIG; i--, j++){
		if(numStr[i] - '0' < 10){
			number = long(numStr[i]) - long('0');
		}
		else{
			number = long(numStr[i]) - long('A') + 10;
		}
		digits[j] = number * pow(base2, j);
        
	}
	
	for(i = 0; i < numOfPlaces and i < MAX_DIG; i++){
		finalNum = finalNum + digits[i];
	}
	
	return finalNum;
}



string ConvertToBase(long base, long number){
//Description: converts a number to the current base
//Input: base – a long that is the base the calculator is currently in, 
//		 number – a long that is the number being converted, 
	long wholeVal = abs(number);
	long remainder = 0;
	char digits[MAX_DIG];
	int i;
	char value;
	string finNum = "";
	
	if(number == 0){
        finNum = '0';
    }
    if(number < 0){
        finNum = '-';
    }
    for(i = 0; i < MAX_DIG and wholeVal != 0; i++){
		remainder = wholeVal % base;
		
		if(remainder >= 10){
			value = char(remainder - 10 + 'A');
			digits[i] = value;
		} 
		else{
			value = remainder + long('0');
			digits[i] = value;
		}
		
		wholeVal = wholeVal / base;
	}
	
	for(i = i - 1; i < MAX_DIG and i >= 0; i--){
		finNum = finNum + digits[i];
	}
	
	return finNum;
}



void CommandDump(long memory[MAX_MEM], long base){
//Description: Prints everything in memory
//Input: memory – an array of longs that stores values, base - the current base
//		 of the calculator
	char letter = 'A';
	int i;
	string number;
	
	cout << "Memory Dump" << endl;
	
	for(i = 0; i < MAX_MEM; i++){
		number = ConvertToBase(base, memory[i]);
		cout << "$" << char(letter + i) << "=" << number << "@" << base << endl;
	}
	
	cout << endl;
	
	return;
}



void CommandBase(long& base, string num1){
//Description: Changes the base of the calculator
//Input: base – a long that is the base of all the numbers used for calculations,
//		 num1 - a string that holds the number to be calculated
    long temp;
    
    temp = TranslateToNumber(num1, 10);
    
    if(MIN_BASE <= temp and temp <= MAX_BASE){
        base = temp;
        cout << "New base " << base << endl;
    }
    else{
        cout << "Invalid base" << endl;
    }
    
    return;
}



void CommandLoad(long& accumulator, string num1, long memory[MAX_MEM], long base, long base2){
//Description: Set the accumulator equal to a value in memory
//Input: accumulator – a long that stores the last processed number, 
//		 memory – an array that contains longs and stores values for later use and
//		 calculations, base – a long containing the current base all numbers used 
//		 for calculations are in, num1 - a string that holds the number to be calculated
    string number;
	accumulator = TranslateValue(num1, base2, memory, accumulator);
	number = ConvertToBase(base, accumulator);
	cout << "$0=" << number << "@" << base << endl;
    
    return;
}



void CommandStore(long& accumulator, string num1, long memory[MAX_MEM], long base){
//Description: Stores the value of the accumulator in memory
//Input: accumulator – a long that stores the last processed number, 
//		 num1 - a string that holds the number to be calculated
//		 memory – an array that contains longs and stores values for later use and calculations, 
//		 base – a long containing the current base all numbers used for calculations are in
	int pos = num1.at(1) - 'A';
	string number = "";
    
	if(0 <= pos and pos < MAX_MEM){
		memory[pos] = accumulator;
		number = ConvertToBase(base, memory[pos]);
		cout << num1 << "=" << number << "@" << base << endl;
	} else{
		cout << "Invalid memory location" << endl;
	}
    
    return;
}



void CommandPrint(long accumulator, long base){
//Description: Prints the current value in the accumulator using the current base
//Input: base – a long storing the current base of the numbers in the calculator,
//		 accumulator - a long that contains the last entered value
	string number;
	
	number = ConvertToBase(base, accumulator);
	
	cout << "$0=" << number << "@" << base << endl;
	
	return;
}



void CommandAdd(long& accumulator, long memory[MAX_MEM], long base, string num1, string num2){
//Description: Adds two values together
//Input: num1 & num2 - a string containing the numbers being used in calculations, 
//		 base - the base the calculator is in, accumulator - stores the last computed value,
//		 memory - serves as memory and stores numbers
    long num1Base;
    long num2Base;
    long number1;
    long number2;
    string finNum;
    
    number1 = TranslateValue(num1, num1Base, memory, accumulator);
    number2 = TranslateValue(num2, num2Base, memory, accumulator);
    accumulator = number1 + number2;
    
    finNum = ConvertToBase(base, accumulator);
    
    cout << "$0=" << finNum << "@" << base << endl;
    
    return;
}



void CommandSubtract(long& accumulator, long memory[MAX_MEM], long base, string num1, string num2){
//Description: Subtract two values from each other
//Input: num1 & num2 - a string containing the numbers being used in calculations, 
//		 base - the base the calculator is in, accumulator - stores the last computed value,
//		 memory - serves as memory and stores numbers
	long num1Base;
    long num2Base;
    long number1;
    long number2;
    string finNum;
    
    number1 = TranslateValue(num1, num1Base, memory, accumulator);
    number2 = TranslateValue(num2, num2Base, memory, accumulator);
    accumulator = number1 - number2;
    
    finNum = ConvertToBase(base, accumulator);
    
    cout << "$0=" << finNum << "@" << base << endl;
    
    return;
}



void CommandMult(long& accumulator, long memory[MAX_MEM], long base, string num1, string num2){
//Description: Multiplies two values together
//Input: num1 & num2 - a string containing the numbers being used in calculations, 
//		 base - the base the calculator is in, accumulator - stores the last computed value,
//		 memory - serves as memory and stores numbers    
	long num1Base;
    long num2Base;
    long number1;
    long number2;
    string finNum;
    
    number1 = TranslateValue(num1, num1Base, memory, accumulator);
    number2 = TranslateValue(num2, num2Base, memory, accumulator);
    accumulator = number1 * number2;
    
    finNum = ConvertToBase(base, accumulator);
    
    cout << "$0=" << finNum << "@" << base << endl;
    
    return;
}



void CommandDivide(long& accumulator, long memory[MAX_MEM], long base, string num1, string num2){
//Description: divides two values by each other
//Input: num1 & num2 - a string containing the numbers being used in calculations, 
//		 base - the base the calculator is in, accumulator - stores the last computed value,
//		 memory - serves as memory and stores numbers    
	long num1Base;
    long num2Base;
    long number1;
    long number2;
    string finNum;
    
    number1 = TranslateValue(num1, num1Base, memory, accumulator);
    number2 = TranslateValue(num2, num2Base, memory, accumulator);
    
    if(number2 != 0){
        accumulator = number1 / number2;
        finNum = ConvertToBase(base, accumulator);
        cout << "$0=" << finNum << "@" << base << endl;
    }
    else{
        cout << "Invalid computation.  Zero divide" << endl;
    }
    
    return;
}
