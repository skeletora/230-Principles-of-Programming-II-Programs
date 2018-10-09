CXXFLAGS =  -g -O3 -Wall -Wextra -Wuninitialized -pedantic -Wshadow -Weffc++ -std=c++14

OBJS = palindrome palSorter

all: ${OBJS}

palindrome: PalRoutines.o
palSorter: PalRoutines.o sort.o

PalRoutines.o: PalRoutines.h
sort.o: sort.h

clean:
	rm -f ${OBJS} *.o 
