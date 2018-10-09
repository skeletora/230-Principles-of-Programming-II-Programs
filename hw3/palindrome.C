/*
Rebecca Aloisio
CSCI 230 002
2/21/18
Assignment #3
Recursively determines if a string or set of strings is a perfect palindrome.
*/
#include <string>
#include <fstream>
#include <iostream>
	using namespace std;

void ManageFile(string& fileName, ifstream& inFile);
void ReverseString(string phrase, string& reverse, int& i, int& pass);
bool DetIfPalindrome(string phrase, string reverse, int& i, bool& trigger);
void ReportResults(bool palindrome, string phrase);
void Reset(int& i, int& pass, string& reverse, bool& trigger);

int main(){
    //stores the word or phrase being checked
    string phrase;
    //stores the name of the input file
    string fileName;
    //stores the reverse of phrase
	string reverse;
    //the input file
    ifstream inFile;
    //stores the current position in the string
	int i;
    //stores the number of passes through a function
	int pass;
    //stores the truth value of a string being a palindrome or not
	bool palindrome;
	//To prevent recursion from changing a false value to a true one due to how recursion works 
	bool trigger = true;
    
    ManageFile(fileName, inFile);
    
    getline(inFile, phrase);
    while(inFile){
		i = int(phrase.length()) - 1;
        ReverseString(phrase, reverse, i, pass);
		i = 0;
        
        palindrome = DetIfPalindrome(phrase, reverse, i, trigger);
		ReportResults(palindrome, phrase);
		Reset(i, pass, reverse, trigger);
		
        getline(inFile, phrase);
    }

    inFile.close();
    return 0;
}



void ManageFile(string& fileName, ifstream& inFile){
//Description: Prompts the user for an input file name and attempts
//  to open the file.  If it cannot, it will output a message.
//Input: fileName - stores the name of the input file
//       inFile - the input file
    cout << "Enter the file name -> ";
    cin >> fileName;
    cout << endl;

    inFile.open(fileName.c_str());
	
    if(!inFile){
        cout << "The file " << fileName << " does not exist." << endl;
    }

	return;
}



void ReverseString(string phrase, string& reverse, int& i, int& pass){
//Description: Recursively stores the reverse of a string in a new string
//Input: phrase - the original string, reverse - the reverse of phrase,
//      i - the current position in phrase, pass - the number of times the
//      function has been called.
    
	if(i < 0 && pass == 0){
			reverse = phrase;
    }
	else{
		if(i >= 0){
			reverse = reverse + phrase[i];
			i--;
			pass++;
			ReverseString(phrase, reverse, i, pass);
		}
	}
	return;
	
}



bool DetIfPalindrome(string phrase, string reverse, int& i, bool& trigger){
//Description: Recursively determines if the phrase is a perfect palindrome
//Input: phrase - the string being tested, reverse - the reverse of phrase,
//      i - the current position in the strings
//		trigger - bool value to stop recursion from producing incorrect truth values
//					due to the way recursive functions execute
    //stores the truth value of phrase being a perfect palindrome that is returned
	bool palindrome;
	
	palindrome = phrase.length() == reverse.length();
	
	if(i < int(phrase.length()) && palindrome){
		if(phrase[i] == reverse[i]){
			i++;
			DetIfPalindrome(phrase, reverse, i, trigger);
		}
		else{
			trigger = false;
		}
	}
	if(trigger == false){
		palindrome = trigger;
	}
	return palindrome;
}



void ReportResults(bool palindrome, string phrase){
//Description: outputs whether phrase is a perfect palindrome or not.
//Input: palindrome - a bool that determines if the phrase is a palindrome or not
//		phrase - a string with the phrase in it
    
	if(palindrome){
		cout << "\"" << phrase << "\" YES!" << endl;
	}
	else{
		cout << "\"" << phrase << "\" no." << endl;
	}
	
	return;
}



void Reset(int& i, int& pass, string& reverse, bool& trigger){
//Description: resets certain values for the next iteration of the loop
//Input: i - an integer that stores position in a string
//		pass - an integer that stores the number of passes through a function
//		reverse - a string that holds the reverse of another string
//		trigger - bool value to stop recursion from producing incorrect truth values
//					due to the way recursive functions execute
	i = 0;
	pass = 0;
	reverse = "";
	trigger = true;
	
	return;
}
