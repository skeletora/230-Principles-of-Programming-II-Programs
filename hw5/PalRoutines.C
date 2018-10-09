#include <iostream>
#include <string>

#include "PalRoutines.h"

using namespace std;

// many of these routines are not exported and are declared before
// they are used so there is no need for a function prototye.
//
// Furhtermore, the fuction prototype is NOT included in the header file.

string ReverseString(string phrase) {
    string returnValue;
    size_t i;

    for(i=0;i<phrase.size();i++) {
        returnValue = phrase[i] + returnValue;
    }
    return returnValue;
}

// compare two strings.
// An artifact from homework 2
bool CompareStrings(string a, string b) {
    bool rv = false;;
    size_t i;

    if (a.size() == b.size() ) {
       i = 0;
       while (i < a.size() and a[i]== b[i] ) {
          i++;
       }
       rv = i == a.size();
    }

    return rv;
}

// remove punctuation and make the phrase all upper case.
void Strip1(string & phrase) {
    string rv;
    size_t i;

    for(i=0;i<phrase.size();i++) {
       if (not bool(ispunct(phrase[i])) ) {
          rv = rv + char(toupper(phrase[i]));
       }
    }
    phrase = rv;
    return;
}

// remove all but the alphabetic characters (letters). 
// make these all upper case.
void Strip2(string &  phrase) {
    string rv;
    size_t i;
    for(i=0;i<phrase.size();i++) {
       if (bool(isalpha(phrase[i]))) {
          rv = rv + char(toupper(phrase[i]));
       }
    }
    phrase = rv;
    return;
}

// reverse a string and see if it is a palindrome.
bool Check(string phrase) {
     string reverse;

     reverse = ReverseString(phrase);
     return CompareStrings(phrase, reverse);
}


// classify a palindrome
// Return the Enumerated type matching the type
PalindromeT ClassifyPhrase(string phrase){
     PalindromeT classification = PalindromeT::NON;

     if(Check(phrase)) {
        classification = PalindromeT::PERFECT;
     } else {
         Strip1(phrase);
	 if (Check(phrase)) {
             classification = PalindromeT::NATURAL;
	 } else {
	     Strip2(phrase);
	     if (Check(phrase)) {
                 classification = PalindromeT::REGULAR;
	     }
	 }
     }
     return classification;
}

// a routine so you can loop over the palindrome types.
PalindromeT NextPalindromeT(PalindromeT current) {
    switch(current) {
        case PalindromeT::PERFECT: return PalindromeT::NATURAL;
        case PalindromeT::NATURAL: return PalindromeT::REGULAR;
        case PalindromeT::REGULAR: return PalindromeT::NON;
        case PalindromeT::NON: return PalindromeT::UNKNOWN;
        case PalindromeT::UNKNOWN:
	default: return PalindromeT::UNKNOWN;
    }
}

// convert a palindromeT to a string
PalindromeT StringToPalindromeT(string word){
    size_t i;

    // make the phrase lower case, all palindromeT strings are lower case
    for(i=0;i< word.size();i++) {
      word[i] = char(tolower(word[i]));
    }

    // match the case.
    if (word == PERFECT_STRING) {
       return PalindromeT::PERFECT;
    } else if (word == NATURAL_STRING) {
       return PalindromeT::NATURAL;
    } else if (word == REGULAR_STRING) {
       return PalindromeT::REGULAR;
    } else if (word == NON_STRING) {
       return PalindromeT::NON;
    } else {
       return PalindromeT::UNKNOWN;
    }
}

// given a palindromeT return the strng that describes it.
string PalindromeTToString(PalindromeT classification) {
    switch (classification) {
       case PalindromeT::PERFECT: return(PERFECT_STRING);
       case PalindromeT::NATURAL: return(NATURAL_STRING);
       case PalindromeT::REGULAR: return(REGULAR_STRING);
       case PalindromeT::NON: return(NON_STRING);
       case PalindromeT::UNKNOWN:
       default: return(UNKNOWN_STRING);
    }
}
