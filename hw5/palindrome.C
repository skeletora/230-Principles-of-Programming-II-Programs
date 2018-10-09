/*
Rebecca Aloisio
CSCI 230 002
3/19/18
Assignment #5 - palindrome
This checks phrases to determine if they are a palindrome and if so, what type.
    This is also to help familiarize the programmer with accessing multiple files.
*/
#include "PalRoutines.h"
#include <iostream>
#include <fstream>
    using namespace std;

void OpenFile(ifstream& inFile, string& filename);
bool GetPhrase(ifstream& inFile, string& phrase);
void PrintResults(string phrase, PalindromeT type);
int main(){
    ifstream inFile;
    string fileName;
    string phrase;
    PalindromeT type;
    bool exists;
    
    OpenFile(inFile, fileName);
    
    exists = GetPhrase(inFile, phrase);
    while(exists){
        type = ClassifyPhrase(phrase);
        
        PrintResults(phrase, type);
        
        exists = GetPhrase(inFile, phrase);
    }
    
    inFile.close();
    
    return 0;
}



void OpenFile(ifstream& inFile, string& fileName){
    cout << "Enter the file name =>";
    cin >> fileName;
    cout << endl;
    
    inFile.open(fileName.c_str());
    
    if(!inFile){
        cout << "The file " << fileName << " does not exist." << endl;
    }
    
    return;
}



bool GetPhrase(ifstream& inFile, string& phrase){
    bool exists = true;
    
    getline(inFile, phrase);
    
    if(!inFile){
        phrase = "";
        exists = false;
    }
    
    return exists;
}



void PrintResults(string phrase, PalindromeT type){
    cout << "\"" << phrase << "\" is a " << PalindromeTToString(type) << "." << endl;
    
    return;
}
