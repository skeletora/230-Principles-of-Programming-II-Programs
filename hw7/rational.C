/*
Rebecca Aloisio
CSCI 230 002
4/23/2018
Assignment #7
Manages the functions relating to the RationalT class
*/

#include "rational.h"
#include <iostream>
using namespace std;

int RationalT::GCD(int a, int b) const{
    int c, d;
    
    if(a == 0 and b == 0){
        return 1;
    }
    
    c = abs(a);
    d = abs(b);
    if(c < d){
        return GCD(d,c);
    } else if(d == 0){
        return c;
    } else{
        return GCD(d, c%d);
    }
}



int RationalT::LCM(int a, int b) const{
    int lcm;
    
    lcm = (a * b) / GCD(a,b);
    
    return lcm;
}



void RationalT::Reduce(){
    int gcd;

    gcd = GCD(numerator, denominator);
    
    numerator = numerator / gcd;
    denominator = denominator / gcd;
    
    return;
}



RationalT::RationalT(){
    numerator = 0;
    denominator = 1;
        
    return;
}



RationalT::RationalT(int n){
    numerator = n;
    denominator = 1;
        
    return;
}



RationalT::RationalT(int n, int d){
    if(d != 0 and d >= 0){
        numerator = n;
        denominator = d;
        Reduce();
    } else if(d < 0){
        numerator = n * -1;
        denominator = d * -1;
        Reduce();
    }else{
        numerator = 0;
        denominator = 1;
    }
        
    return;
}



RationalT::~RationalT(){
    return;
}



RationalT RationalT::Add(const RationalT& other) const{
    RationalT rv;
    int lcm;
    
    lcm = LCM(denominator, other.denominator);
        
    rv.numerator = ((numerator * (lcm / denominator)) + (other.numerator * (lcm / other.denominator)));
    rv.denominator = lcm;
    rv.Reduce();
    
    return rv;
}



RationalT RationalT::Sub(const RationalT& other) const{
    RationalT rv;
    int lcm;
    
    lcm = LCM(denominator, other.denominator);
        
    rv.numerator = ((numerator * (lcm / denominator)) - (other.numerator * (lcm / other.denominator)));
    rv.denominator = lcm;
    rv.Reduce();
    
    return rv;
}



RationalT RationalT::Mul(const RationalT& other) const{
    RationalT rv;
    
    rv.numerator = numerator * other.numerator;
    rv.denominator = denominator * other.denominator;
    rv.Reduce();

    
    return rv;
}



RationalT RationalT::Div(const RationalT& other) const{
    RationalT rv;
    
    if(other.numerator != 0){
        if(other.numerator < 0){
            rv.numerator = numerator * other.denominator * -1;
            rv.denominator = denominator * other.numerator * -1;
        } else{
            rv.numerator = numerator * other.denominator;
            rv.denominator = denominator * other.numerator;
        }
        rv.Reduce();
    } else{
        cout << "ERROR - Division by zero" << endl;
    }
    
    return rv;
}
   
   
   
int RationalT::Num(void) const{
    return numerator;
}



int RationalT::Denom(void) const{
    return denominator;
}



double RationalT::Value(void) const{
    return double(numerator) / denominator;
}
