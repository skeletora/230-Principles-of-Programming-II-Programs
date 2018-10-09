/*
Rebecca Aloisio
CSCI 230 002
5/4/2018
Assignment #7
Tests the RationalT class.  For the sake of reducing the amount outputted,
    tests for each operation has been commented out until needed.
*/

#include "rational.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
    using namespace std;
    
bool ERROR = false;
    
int GCD(int a, int b);
bool TestValues(RationalT r, int num, int denom);
bool ConstructorTest(void);
void ValueTest(int nstart, int nend, int dstart, int dend);
void Add(RationalT a, RationalT b, int num1, int denom1, int num2, int denom2);
void Subtract(RationalT a, RationalT b, int num1, int denom1, int num2, int denom2);
void Multiply(RationalT a, RationalT b, int num1, int denom1, int num2, int denom2);
void Divide(RationalT a,   RationalT b, int num1, int denom1, int num2, int denom2);
void FloatTest(RationalT r, int num, int denom);
void MathTest(int nstart, int nend, int dstart, int dend);

    
int main(){
    int nstart = -10;
    int nend = 10;
    int dstart = -10;
    int dend = 10;
    
    ConstructorTest();
    cout << endl;
    ValueTest(nstart, nend, dstart, dend);
    
    dstart = 1;
    
    MathTest(nstart, nend, dstart, dend);
    cout << endl;
    
    if(ERROR){
        cout << "Finished with errors" << endl;
    } else{
        cout << "All tests Successful" << endl;
    }
    
    
    return 0;
}


int GCD(int a, int b) {
   if (a ==0 and b == 0) {
      return 1;
   }
   a = abs(a);
   b = abs(b);
   if (a < b) {
      return GCD(b,a);
   } else if (b == 0) {
      return a;
   } else {
      return GCD(b,a%b);
   }
}

bool TestValues(RationalT r, int num, int denom) {

     int gcd = GCD(num, denom);
     if (gcd == 0) {
        cout << "GCD ERROR" << endl;
	    gcd = 1;
     }
     num = num / gcd;
     denom = denom / gcd;
     if (denom < 0) {
        denom = -denom;
	    num = -num;
     } 

     if (r.Num() != num) {
         cout << "Numerator Error" << endl;
	     cout << "\tShould be " << num << endl;
	     cout << "\tIs        " << r.Num() << endl;
	     ERROR = true;
	     return false;
     }

     if (r.Denom() != denom) {
         cout << "Denominator Error" << endl;
	     cout << "\tShould be " << denom << endl;
	     cout << "\tIs        " << r.Denom() << endl;
	     ERROR = true;
	     return false;
     }

     double value = double(num)/double(denom);
     if (r.Value() != value) {
         cout << "Value Error" << endl;
	     cout << "\tShould be " << value << endl;
	     cout << "\tIs        " << r.Value() << endl;
	     ERROR = true;
	     return false;
     }

     return true;
}

bool ConstructorTest(void) {
    RationalT a;

    cout << endl;
    cout << "Constructor Test ";

    cout << ".";
    cout.flush();
    if (a.Num() != 0) {
       cout << "Numerator not 0 in default constructor " << endl;
       ERROR = true;
       exit(1);
    }

    cout << ".";
    if (a.Denom() != 1) {
       cout << "Denominator not 1 in default constructor " << endl;
       ERROR = true;
       exit(1);
    }

    cout << ".";
    RationalT b(1);
    if (b.Num() != 1 and b.Denom() != 1) {
        cout << "Error for RationalT b(1) " << endl;
        ERROR = true;
	    exit(1);
    }

    cout << " success" << endl;

    return true;
}

void ValueTest(int nstart, int nend, int dstart, int dend) {
    int num, denom;

    cout << "Value Test " ;

    for(num=nstart;num<=nend;num++) {

       if (num % 100 == 0) {
           cout <<".";
	       cout.flush();
       }

       for(denom = dstart;denom <= dend; denom ++) {
          if(denom != 0) {
	          RationalT r(num,denom);
              TestValues(r,num, denom); 
	     }
       }
    }

    cout << " Success" << endl;
    return ;
}

void Add(RationalT a, RationalT b, int num1, int denom1, int num2, int denom2){
      RationalT sum = a.Add(b);

      int g = GCD(denom1, denom2);
      int num = num1 * denom2/g + num2*denom1/g;
      int denom = denom1/g*denom2;
      g = GCD(num,denom);
      num /= g;
      denom /= g;
      if (not TestValues(sum, num, denom)) {
          cout << "Error in add test " ;
	      cout << a.Num() << "/" << a.Denom() << " + " <<  b.Num() <<  "/" << b.Denom() << endl;
	      cout << "\t Should be: " << num << "/" << denom << endl;
	      cout << "\t Is       : " << sum.Num() << " / " << sum.Denom() << endl;
	      ERROR=true;
	      exit(0);
      }
      return;
}

void Subtract(RationalT a, RationalT b, int num1, int denom1, int num2, int denom2){
      RationalT sum = a.Sub(b);

      int g = GCD(denom1, denom2);
      int num = num1 * denom2/g - num2*denom1/g;
      int denom = denom1/g*denom2;
      g = GCD(num,denom);
      num /= g;
      denom /= g;
      if (not TestValues(sum, num, denom)) {
          cout << "Error in Subtract test " ;
	      cout << a.Num() << "/" << a.Denom() << " - " <<  b.Num() <<  "/" << b.Denom() << endl;
	      cout << "\t Should be: " << num << "/" << denom << endl;
	      cout << "\t Is       : " << sum.Num() << " / " << sum.Denom() << endl;
	      ERROR=true;
	      exit(0);
      }
      return;
}


void Multiply(RationalT a, RationalT b, int num1, int denom1, int num2, int denom2){
      int num = num1*num2;
      int denom = denom1*denom2;
      int g = GCD(num, denom);
      RationalT prod = a.Mul(b);

      num/=g;
      denom/=g;
      if (not TestValues(prod, num, denom)) {
          cout << "Error in Multiply test " ;
	      cout << a.Num() << "/" << a.Denom() << " * " <<  b.Num() <<  "/" << b.Denom() << endl;
	      cout << "\t Should be: " << num << "/" << denom << endl;
	      cout << "\t Is       : " << prod.Num() << " / " << prod.Denom() << endl;
	      ERROR=true;
	      exit(0);
      }
      return;
}


void Divide(RationalT a,   RationalT b, int num1, int denom1, int num2, int denom2){
      int num = num1*denom2;
      int denom = denom1*num2;
      int g = GCD(num, denom);

      if (num2 == 0 or denom2 == 0) {
         return;
      }
      RationalT prod = a.Div(b);

      num/=g;
      denom/=g;

      if (denom == 0) {
         return;
      }
      if (not TestValues(prod, num, denom)) {
          cout << "Error in Divide test " ;
	      cout << a.Num() << "/" << a.Denom() << " / " <<  b.Num() <<  "/" << b.Denom() << endl;
	      cout << "\t Should be: " << num << "/" << denom << endl;
	      cout << "\t Is       : " << prod.Num() << " / " << prod.Denom() << endl;
          ERROR=true;
	      exit(0);
      }
      return;
}


void FloatTest(RationalT r, int num, int denom) {
   int g =GCD(num, denom);
   num /= g;
   denom /= g;

   double f = static_cast<double>(num)/static_cast<double>(denom);
   if (fabs(r.Value() - f) > 0.0005) {
       cout << "Error in Value test " << endl;
       cout << "\t Should Be: " << f << endl;
       cout << "\t Is       : " << r.Value() << endl;
       ERROR=true;
       exit(0);
   }
}


void MathTest(int nstart, int nend, int dstart, int dend) {
    int num1, num2, denom1, denom2;

    cout << endl;
    cout << "Math Test ";

 
    for(num1 = nstart;num1<nend;num1++) {
       for(denom1 =dstart;denom1<dend;denom1++) {
          cout << ".";
          for(num2 = nstart;num2<nend;num2++) {
             for(denom2 =dstart;denom2<dend;denom2++) {
	             RationalT a(num1, denom1), b(num2, denom2);
 		         Add(a,b,num1, denom1, num2, denom2);
		         Subtract(a,b,num1, denom1, num2, denom2);
		         Multiply(a,b,num1, denom1, num2, denom2);
		         Divide(a,b,num1, denom1, num2, denom2);
		         FloatTest(a, num1, denom1);
 		         FloatTest(b, num2, denom2);
             }
          }
       }
    }
    cout << " Success" << endl;
    return;
}
