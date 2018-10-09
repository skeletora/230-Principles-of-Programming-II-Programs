#include "sort.h"

void Swap(string palindrome[], int i, int smallest){
    string temp = palindrome[i];
    
    palindrome[i] = palindrome[smallest];
    palindrome[smallest] = temp;
    
    return;
}




void Sort(string palindromes[MAX_PAL], int items){
    int i;
    int current;
    
    for(i = 0; i < items and i < MAX_PAL; i++){
        for(current = items - 1; current > i and current < MAX_PAL; current--){
            if(palindromes[i] > palindromes[current]){
                Swap(palindromes, i, current);
            }
        }
    }
    
    return;
}
