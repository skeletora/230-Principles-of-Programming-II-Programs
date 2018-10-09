/*
Rebecca Aloisio
CSCI 230 002
3/22/18
Assignment #5 - palsorter
This checks phrases to determine if they are a palindrome and if so, what type.
    They are organized by their type and then outputted in alphabetical order.
    This is also to help familiarize the programmer with accessing multiple files.
*/
#include "PalRoutines.h"
#include "sort.h"
#include <iostream>
#include <fstream>
    using namespace std;
    
void GetData(ifstream& inFile, string palindromes[MAX_PAL], int& items, bool& exists);
void OpenFile(ifstream& inFile, bool& exists);
void PrintMatching(string palindromes[MAX_PAL], PalindromeT type, int items);

int main(){
    ifstream inFile;
    string palindromes[MAX_PAL];
    PalindromeT i;
    int items = 0;
    bool exists = true;
    
    GetData(inFile, palindromes, items, exists);
    
    if(exists){
        Sort(palindromes, items);
    
        for(i = PalindromeT::PERFECT; i != PalindromeT::UNKNOWN; i = NextPalindromeT(i)){
            PrintMatching(palindromes, i, items);
        }
    }
    inFile.close();
    
    return 0;
}



void GetData(ifstream& inFile, string palindromes[MAX_PAL], int& items, bool& exists){
//Description: Read the data in from a file.
    string pal;
    int i;
    
    OpenFile(inFile, exists);
    
    if(exists){
        getline(inFile, pal);
        for(i = 0; inFile and i < MAX_PAL; i++){
            palindromes[i] = pal;
            getline(inFile, pal);
            items++;
        }
    }
    
    return;
}



void OpenFile(ifstream& inFile, bool& exists){
//Description: Ask the user for a file name, open the corresponding file.
    string fileName;
    
    cout << "Enter the file name =>";
    cin >> fileName;
    cout << endl;
    
    inFile.open(fileName.c_str());
    
    if(!inFile){
        cout << "The file " << fileName << " does not exist." << endl;
        exists = false;
    }
    
    return;
}



void PrintMatching(string palindromes[MAX_PAL], PalindromeT type, int items){
//Description: Prints the palindromes organized by type and in alphabetical order
    int i;
    
    cout << "The " << PalindromeTToString(type) << "s in the list are:" << endl;
    
    for(i = 0; i < items and i < MAX_PAL; i++){
        if(type == ClassifyPhrase(palindromes[i])){
            cout << "   \"" << palindromes[i] << "\"" << endl;
        }
    }
    
    cout << endl;
    
    return;
}
