#ifndef PALINDROME_ROUTINES
#define PALINDROME_ROUTINES

#include <string>

using namespace std;

// the enumerated type 
enum class PalindromeT {PERFECT, NATURAL, REGULAR, NON, UNKNOWN};

// support for the enumerated type
string PalindromeTToString(PalindromeT classification);
PalindromeT StringToPalindromeT(string word);
PalindromeT NextPalindromeT(PalindromeT current);

// names for the different palindrome types.  
// These are for testing routines only.
const string PERFECT_STRING = "perfect palindrome";
const string NATURAL_STRING = "natural palindrome";
const string REGULAR_STRING = "palindrome";
const string NON_STRING = "non-palindrome";
const string UNKNOWN_STRING = "unknown";

// The functions provided by the "library" 
PalindromeT ClassifyPhrase(string phrase);

#endif
