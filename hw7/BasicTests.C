#include <iostream>
#include "rational.h"
#include "stack.h"
#include <cmath>
#include <stack>

#include <string.h>

using namespace std;
const int MY_STACK_MAX = 10;

bool ERROR = false;
bool VERBOSE = false;

void StackTests(void);
void Exit(void) {
    if (ERROR) {
        cout << "Exit with Errors " << endl;
    }  else {
        cout << "All tests Successful" << endl;
    }
    return;
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

     if (VERBOSE) {
        cout <<"\tUser: " << r.Num() << "/" << r.Denom() << endl;
        cout <<"\tTest: " << num << "/" << denom << endl;
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
	          if (VERBOSE) {
	             cout << "Test Values " << num << "/" << denom << endl;
	          }
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

      if (VERBOSE) {
         cout << "Divide" << endl;
      }

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

	             if (VERBOSE) {
		             cout << num1 <<"/" << denom1 << "  " << num2 << "/" << denom2 << endl;
	             }
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



void PrintBool(bool b) {
   if (b) {
      cout << "True";
   } else {
      cout << "False";
   }
}

bool Same(stack<RationalT> s, StackT v) {
    RationalT rS, rV;

    while (s.size() > 0) {
       rS = s.top();
       s.pop();
       rV = v.Pop();
       if (rV.Num() != rS.Num() or rV.Denom() != rS.Denom()) {
          return false;
       }
    }
    return true;
}

void PrintStack(stack<RationalT> s){
    RationalT c;

    while (s.size() > 0) {
       c = s.top();
       s.pop();
       cout << c.Num()<< "/" <<c.Denom() << " ";
    }
    cout << endl;
    return;

}

void PrintStackT(StackT v) {
    RationalT c;

    while (v.Size()> 0) {
       c = v.Pop();
       cout << c.Num()<< "/" <<c.Denom() << " ";
    }
    cout << endl;
    return;
}

void Check(stack<RationalT> s, StackT v) {
     if (int(s.size()) != v.Size()) {
         cout << "Error: Stack Size" << endl;
	     cout << "\tShould be: " << s.size() << endl;
	     cout << "\tIs       : " << v.Size() << endl;
	     ERROR=true;
	     exit(0);
     }

     if ((s.size()==0) !=  v.IsEmpty()) {
         cout << "Error: IsEmpty" << endl;
	     cout << "\tShould be: " ;
	     PrintBool(s.size()==0) ;
	     cout << endl;
	     cout << "\tIs       : " ;
	     PrintBool(v.IsEmpty());
	     cout << endl;
	     ERROR=true;
	     exit(0);
     }

     if ((s.size()==MY_STACK_MAX) !=  v.IsFull()) {
         cout << "Error: IsFull" << endl;
	     cout << "\tShould be: " ;
	     PrintBool(s.size()==MY_STACK_MAX);
	     cout << endl;
	     cout << "\tIs       : ";
         PrintBool(v.IsFull());
	     cout << endl;
	     ERROR=true;
	     exit(0);
     }

     if (not Same(s,v)) {
         cout << "Error: Contents incorrect" << endl;
	     cout << "\tShould be: ";
	     PrintStack(s);
	     cout << "\tIs         ";
	     PrintStackT(v) ;
	     ERROR=true;
	     exit(0);
     }

     return;
}

void CheckRats(RationalT r1, RationalT r2) {
    if (r1.Num() != r2.Num() or r1.Denom()!= r2.Denom()) {
        cout << "Error: " << r1.Num() <<  "/" <<  r1.Denom() << endl;
	    cout << "Is not " << r2.Num() <<  "/"  << r2.Denom() << endl;

        ERROR= true;
	    exit(0);
    }
}

void StackTests(void) {
    stack<RationalT> s;
    RationalT c,c1, c2;
    StackT v;

    cout << " Stack Tests" ;
    Check(s,v);

    string name;

    // fill er up luke
    for(int i=0;i<MY_STACK_MAX;i++) {
        if (VERBOSE) {
            cout << "pushing " << i << endl;
        }
        cout << ".";
        RationalT x(i);
        s.push(x);
        v.Push(x);
        Check(s,v);
    }
    RationalT e(-100);

    v.Push(e);
    Check(s,v);

    // back it down to nothing.
    int i = 9;
    while (s.size() > 0) {
        if (VERBOSE) {
            cout << "popping " << i << endl;
            i--;
        }
        cout << ".";
        c1 = s.top();
        c2 = v.Top();
        CheckRats(c1, c2);
        Check(s,v);
        s.pop();
        v.Pop();
        Check(s,v);
    }

    v.Pop();
    Check(s,v);

    c2 =v.Top();
    CheckRats(c, c2);

    cout << " Success " << endl;
   
    return;  
}

int main(int argc, char * argv[]) {
    int i;
    int nstart = -10;
    int nend = 10;
    int dstart = -10;
    int dend = 10;
    bool doFractions = true;
  
    i = 1;
    while (i < argc) {
       if (strcmp (argv[i],"p") == 0) {
          nstart = 0;
          dstart = 1;
	      i++;
       }else  if (strcmp (argv[i],"f") == 0) {
           doFractions = false;
	       i++;
       }else  if (strcmp (argv[i],"v") == 0) {
           VERBOSE = true;
	       i++;
       } else  {
	       i++;
       }
    }

    atexit(Exit);

    if(doFractions) {
       ConstructorTest();
       ValueTest(nstart, nend, dstart, dend);

       dstart = 1;

       MathTest(nstart, nend, dstart, dend);
    }
    StackTests();

    return 0;
}
