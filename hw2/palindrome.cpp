/*
Rebecca Aloisio
CSCI 230 002
February 9, 2018
Homework #2 - Palindromes
Description: Reads in a word or phrase and determines if it is a palindrome, and
	if it is, determines what kind of palindrome it is
*/
#include <string>
#include <fstream>
#include <iostream>
	using namespace std;

void IsPalindrome(string line);
bool IsPerfect(string line);
bool CompareString(string line, string reverse);
string ReverseLine(string line);
void IsNatural(string line, bool& palindrome, string& modPhrase);
string RemovePunct(string line);
void Capitalize(string& modPhrase);
void IsNormal(string line, bool& palindrome, string& modPhrase);
void RemoveSpaces(string& modPhrase);
	
int main()
{
	string fileName;  //stores the name of the input file
	string line;  //stores the string of the word or phrase being tested
	ifstream inFile;  //stores the input file
	
	cout << "Enter the file name => ";
	cin >> fileName;
	cout << endl;
	
	inFile.open(fileName.c_str());

	if (inFile){
		//tests all of the data in the file and determines if it is a
		//   palindrome
		getline(inFile, line);
		while (inFile){
			IsPalindrome(line);
			getline(inFile, line);
		}
	}

	else{
		cout << "The file " << fileName << " does not exist.";
	}
	
	inFile.close();
	return 0;

}



void IsPalindrome(string line){
//Description: Determines if the line is a palindrome, and if it is, what type and
//  outputs a message.
//Variables: palindrome, modPhrase
//Input: A string containing a word or phrase
//Output: A message stating whether or not the string is a palindrome

	bool palindrome;  //stores whether the word or phrase is a palindrome
	string modPhrase;  //stores the modified version of the original string
	
	palindrome = IsPerfect(line);
	if (not palindrome){
		IsNatural(line, palindrome, modPhrase);
		if (not palindrome){
			IsNormal(line, palindrome, modPhrase);
			if (not palindrome){
				cout << "\"" << line << "\" is a non-palindrome." << endl;
			}
		}
	}
	
	return;
}

						
						
bool IsPerfect(string line){
//Description: Determines if the line is a perfect palindrome and outputs a message
//	if it is.
//Variables: returnValue, reverse
//Input: A string containing a word or phrase
//Output: A message stating whether or not the string is a palindrome and a boolean
//	value

	bool returnValue;  //stores the value that will eventually be returned
	string reverse;  //stores the reverse of the line
	
	if (line.size() <= 1){
		cout << "\"" << line << "\" is a perfect palindrome." << endl;
		returnValue = true;
	}
	else{
		reverse = ReverseLine(line);
		returnValue = CompareString(line, reverse);
		if (returnValue){
			cout << "\"" << line << "\" is a perfect palindrome."
			     << endl;
		}
	}
				
	return returnValue;
}
		
		
		
bool CompareString(string line, string reverse){
//Description: Compares the line with its reverse to see if they are the same
//Variables: i, returnValue
//Input: two strings, one containing a word or phrase and the other the reverse of
//	the first
//Output: A boolean value that is "true" if the two strings are the same and "false"
//	otherwise.

	bool returnValue = false;  //stores the value that will eventually be returned 
	size_t i;  //keeps track of the number of iterations of the for loop
	
	if (line.size() == reverse.size()){
		for (i = 0; i < line.size(); i++){
			if (line[i] == reverse[i]){
				returnValue = true;
			}
			else{
				returnValue = false;
				i = line.size();
			}
		}
	}
				
	return returnValue;
}
		
		
string ReverseLine(string line){
//Description: Reverses the letters in the line
//Variables: i, reverse
//Input: A string containing a word or phrase
//Output: A string that is the reverse of the input string

	int position = line.length() - 1;  //stores the position in the string
	string reverse;  //stores the reverse of the string
	
	for(; position >= 0; position--){
		reverse = reverse + line.at(position);
	}

	return reverse;
}



void IsNatural(string line, bool& palindrome, string& modPhrase){
//Description: Determines if the line is a natural palindrome and outputs a message
//	if it is.
//Variables: reverse
//Input: A string containing a word or phrase, a boolean value, and a string that is the
//	modified version of the first string
//Output: A message stating whether or not the string is a palindrome and a boolean
//	value

	string reverse;//stores the reverse of the string
	
	modPhrase = RemovePunct(line);
	Capitalize(modPhrase);
	reverse =  ReverseLine(modPhrase);
	palindrome = CompareString(modPhrase, reverse);
	if (palindrome){
		cout << "\"" << line << "\" is a natural palindrome." << endl;
	}
	
	return;
}
	
	
	
string RemovePunct(string line){
//Description: Removes punctuation from the string
//Variables: returnValue, i
//Input: A string containing a word or phrase
//Output: A new string without punctuation

   string returnValue;  //holds the modified string
   size_t i;  //counter for the loop

   for(i = 0; i < line.size(); i++) {
       if(not ispunct(line[i])) {
           returnValue = returnValue + line[i];
       }
   }


   return returnValue;
}
   


void Capitalize(string& modPhrase){
//Description: Capitalizes all of the letters in the string
//Variables: i, letter, temp
//Input: A string containing a word or phrase
//Output: A new string that is the capitalized version of the input string

	size_t i;  //counter for the loop
	char letter;  //stores the letter being modified
	string temp;  //stores the modified phrase
	
	 for(i = 0; i < modPhrase.size(); i++) {
		if (modPhrase.at(i) != ' ') {
			letter = toupper(modPhrase.at(i));
			temp = temp + letter;
	    }
		else{
			temp = temp + modPhrase.at(i);
		}
	 }
	 
	 modPhrase = temp;

	return;
}
	
	
	
void IsNormal(string line, bool& palindrome, string& modPhrase){
//Description: Determines if the line is a normal palindrome and outputs a message
//	if it is.
//Variables: reverse
//Input: A string containing a word or phrase, a boolean value, and a string that is the
//	modified version of the first string
//Output: A message stating whether or not the string is a palindrome and a boolean
//	value

	string reverse;
	
	RemoveSpaces(modPhrase);
	reverse = ReverseLine(modPhrase);
	palindrome = CompareString(modPhrase, reverse);
	if (palindrome){
		cout << "\"" << line << "\" is a palindrome." << endl;
	}
	
	return;
}
	
	
	
void RemoveSpaces(string& modPhrase){
//Description: Removes spaces from the line
//Variables: i, temp
//Input: A string containing a word or phrase
//Output: A new string without spaces

   size_t i;  //counter for the loop
   string temp;  //stores the modified string

   for(i=0; i< modPhrase.size(); i++) {
       if(modPhrase[i] != ' ') {
           temp = temp + modPhrase[i];
       }
   }

	modPhrase = temp;
	
   return;
}