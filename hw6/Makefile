CXXFLAGS =  -g -O3 -Wall -Wextra -Wuninitialized -pedantic -Wshadow -std=c++14

OBJS = main BasicTests

all: ${OBJS}

main: station.o spur.o stack.o car.o destination.o
BasicTests: station.o spur.o stack.o car.o destination.o

station.o: station.h spur.h stack.h car.h destination.h
spur.o: spur.h stack.h car.h destination.h
stack.o: stack.h car.h destination.h
car.o: car.h destination.h
destination.o: destination.h

clean:
	rm -f ${OBJS} *.o
