#ifndef STACK_DOT_H
#define STACK_DOT_H

#include "rational.h"

typedef RationalT ItemT;

const int STACK_MAX = 10;

class StackT{
    public:
        //Creates an empty stack
        StackT();
        //Adds an item to the stack if it is not full
        void Push(ItemT i);
        //Returns the item at the top of the stack and removes it
        ItemT Pop(void);
        //Returns the item at the top of the stack
        ItemT Top(void) const;
        //Returns the size of the stack
        int Size(void) const;
        //Returns true if the stack is empty
        bool IsEmpty(void) const;
        //Returns true if the stack is full
        bool IsFull(void) const;
    private:
        int size;
        ItemT data[STACK_MAX];
        const ItemT NO_ITEM;
};

#endif
