/*
Rebecca Aloisio
CSCI 230 002
4/17/2018
Assignment #7 - Fractional Calculator
Description: This programs is a postfix notation (also called Reverse Polish Notation)
    calculator for rational numbers. This also provides the programmer experience with 
    classes.
*/

#include "rational.h"
#include "stack.h"
#include <string>
#include <iostream>
#include <stdlib.h>
    using namespace std;

int NumOfTokens(const string& s);
void Prompt(const StackT& stack, string& s, int& n);
void CheckCom(string& s, int& n, bool& off, StackT& stack, bool& isCom, bool& error);
void Capitalize(string& s);
void Off(bool& off);
void Print(const RationalT& r);
void FPrint(const RationalT& r);
void Clear(StackT& s);
void Dump(StackT s);
bool IsOper(const char& c);
bool IsNeg(const string& op);
void ExOper(const string& s, StackT& stack, bool& error);
void Error(const string& s, const StackT& stack, bool& error);
void ExRat(const string& op, size_t& i, StackT& stack, bool& error);
void MakeFract(const string& s, RationalT& r, const int& num, size_t& i);
void Reset(size_t& i, bool& isCom, bool& neg, bool& error);
    
int main(){
    bool off = false;
    bool isCom = false;
    bool neg = false;
    bool error = false;
    StackT stack;
    string op;
    //Keeps track of positions in op string.  Used to modify op.
    size_t i = 0;
    int noOfTok;
    
    while(not off){
        Prompt(stack, op, noOfTok);
        CheckCom(op, noOfTok, off, stack, isCom, error);
        
        while(noOfTok > 0 and not isCom and not error){
            neg = IsNeg(op);
            if(IsOper(op[i]) and not neg){
                ExOper(op, stack, error);
                noOfTok--;
                i++;
            } else if(isdigit(op[i]) or neg){
                ExRat(op, i, stack, error);
                noOfTok--;
            } else if(isspace(op[i])){
                i++;
            } else{
                Error(op, stack, error);
            }
            if(noOfTok > 0 and not error){
                op = op.substr(i + 1, string::npos);

            }
            i = 0;
        }
        
        Reset(i, isCom, neg, error);
    }
    
    return 0;
}



int NumOfTokens(const string& s){
//Description: Determines the amount of items in the command
    int no = 0;
    size_t pos;
    string temp;
    
    pos = s.find(' ');
    temp = s.substr(pos + 1, string::npos);
    while(pos != string::npos){
        no++;
        pos = temp.find(' ');
        temp = temp.substr(pos + 1, string::npos);
    }
    
    no = no + 1;
    
    return no;
}



void Prompt(const StackT& stack, string& s, int& n){
    cout << "(" << stack.Size() << ") % ";
    getline(cin, s);
    cout << endl;
        
    n = NumOfTokens(s);
    
    return;
}



void CheckCom(string& s, int& n, bool& off, StackT& stack, bool& isCom, bool& error){
    string temp = s;
    
    if(n == 1 and isalpha(s[0])){
        isCom = true;
        Capitalize(temp);
        
        if(temp == "OFF"){
            Off(off);
        } else if(temp == "PRINT"){
            Print(stack.Top());
            cout << endl;
        } else if(temp == "FPRINT"){
            FPrint(stack.Top());
            cout << endl;
        } else if(temp == "CLEAR"){
            Clear(stack);
        } else if(temp == "DUMP"){
            Dump(stack);
            cout << endl;
        } else{
            Error(s, stack, error);
        }

    }
    
    return;
}



void Capitalize(string& s){
    string temp;
    size_t i;
    
    for(i = 0; i < s.size(); i++) {
        if (s[i] != ' ') {
            temp += toupper(s[i]);
        }
        else{
            temp += s[i];
        }
    }
	 
    s = temp;
	 
    return;
}



void Off(bool& exit){
    exit = true;
    
    return;
}



void Print(const RationalT& r){
    if(r.Denom() != 1){
        cout << r.Num() << "/" << r.Denom();
    } else{
        cout << r.Num();
    }
    
    return;
}



void FPrint(const RationalT& r){
    cout << r.Value();
    
    return;
}



void Clear(StackT& s){
    while(not s.IsEmpty()){
        s.Pop();
    }
    
    return;
}



void Dump(StackT s){
    RationalT r;
    
    if(not s.IsEmpty()){
        r = s.Pop();
        Dump(s);
        Print(r);
        cout << " ";
    }
    
    return;
}



bool IsOper(const char& c){
    bool yes = false;
    
    if(c == '+' or c == '-' or c == '/' or c == '*'){
        yes = true;
    }
    
    return yes;
}



bool IsNeg(const string& op){
    bool val = false;
    
    if(op.size() > 1){
        if(op[0] == '-' and isdigit(op[1])){
            val = true;
        }
    }
    
    return val;
}



void ExOper(const string& s, StackT& stack, bool& error){
    RationalT arg1;
    RationalT arg2;
    RationalT result;
    
    if(stack.Size() >= 2){
        arg2 = stack.Pop();
        arg1 = stack.Pop();
        if(s[0] == '+'){
            result = arg1.Add(arg2);
        } else if(s[0] == '-'){
            result = arg1.Sub(arg2);
        } else if(s[0] == '/'){
            result = arg1.Div(arg2);
            if(arg2.Num() == 0){
                Clear(stack);
                error = true;
            }
        } else{
            result = arg1.Mul(arg2);
        }
        stack.Push(result);
    } else{
        Error(s, stack, error);
    }
    
    return;
}



void Error(const string& s, const StackT& stack, bool& error){
    if(IsOper(s[0])){
        cout << "Error: Insufficient Stack for ";
        if(s[0] == '+'){
            cout << "Add." << endl;
        } else if(s[0] == '-'){
            cout << "Subtract." << endl;
        } else if(s[0] == '/'){
            cout << "Divide." << endl;
        } else{
            cout << "Multiply." << endl;
        }
    } else if(stack.IsFull() and s == "FULL"){
        cout << "Error: Stack Overflow." << endl;
    } else{
        cout << "Error: Invalid Input " << s << "." << endl;
    }
    
    error = true;
    
    return;
}



void ExRat(const string& op, size_t& i, StackT& stack, bool& error){
    RationalT arg1;
    int num;
    string full = "FULL";
    
    num = stoi(op, &i);
    if(stack.IsFull() and not (isalpha(op[i]) or ispunct(op[i]))){
        Error(full, stack, error);
    } else if((isalpha(op[i]) or ispunct(op[i])) and op[i] != '/'){
        Error(op, stack, error);
    } else if(op[i] == '/'){
        MakeFract(op, arg1, num, i);
        stack.Push(arg1);
    } else{
        arg1 = num;
        stack.Push(arg1);
    }
    
    return;
}



void MakeFract(const string& s, RationalT& r, const int& num, size_t& i){
    int den;
    size_t j;
    string denStr = s.substr(i + 1, string::npos);
    
    den = stoi(denStr, &j);
    i += j + 1;
    
    RationalT temp(num, den);
    
    r = temp;
    
    
    return;
}



void Reset(size_t& i, bool& isCom, bool& neg, bool& error){
    i = 0;
    isCom = false;
    neg = false;
    error = false;
    
    return;
}
