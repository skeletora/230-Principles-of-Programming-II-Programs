#ifndef RATIONAL_DOT_H
#define RATIONAL_DOT_H

class RationalT{
    public:
        RationalT();
        RationalT(int n);
        RationalT(int n, int d);
        ~RationalT();
        
        RationalT Add(const RationalT& other) const;
        RationalT Sub(const RationalT& other) const;
        RationalT Mul(const RationalT& other) const;
        RationalT Div(const RationalT& other) const;
        
        int Num(void) const;
        int Denom(void) const;
        double Value(void) const;
    private:
        int numerator;
        int denominator;
        
        void Reduce();
        int GCD(int a, int b) const;
        int LCM(int a, int b) const;
};

#endif
