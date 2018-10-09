CXXFLAGS = -g -O3 -Wall -Wextra -Wuninitialized -pedantic -Wshadow -std=c++14

OBJS = RatTest StackTest Calculator BasicTests

all: ${OBJS}

RatTest: rational.o
StackTest: stack.o rational.o
BasicTests: stack.o rational.o

Calculator: rational.o stack.o 

rational.o: rational.h
stack.o: rational.h stack.h

clean:
	rm -f ${OBJS} *.o
