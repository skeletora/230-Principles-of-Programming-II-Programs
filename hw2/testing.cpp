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
	string line = "[]";
	size_t i;  //counter for the loop
	string returnValue;
	
	cout << "String before loop : " << line << endl << endl;

	for(i = 0; i < line.size(); i++) {
       if(not ispunct(line[i])) {
           returnValue = returnValue + line[i];
       }
   }
   
   cout << "String after loop : " << returnValue << endl << endl;


	return 0;

}



void IsPalindrome(string line){
//Description: Determines if the line is a palindrome, and if it is, what type and
//  outputs a message.
//Variables: palindrome, modPhrase

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
   string returnValue;
   size_t i;

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

	size_t i;
	char letter;
	string temp;
	
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

   size_t i;
   string temp;

   for(i=0; i< modPhrase.size(); i++) {
       if(modPhrase[i] != ' ') {
           temp = temp + modPhrase[i];
       }
   }

	modPhrase = temp;
	
   return;
}