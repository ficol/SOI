CXX=g++
CXXFLAGS= -Wall -pthread -std=c++11

all: queue.o main.o
	$(CXX) $(CXXFLAGS) queue.o main.o -o monitor

queue.o: queue.cpp
	$(CXX) $(CXXFLAGS) -c queue.cpp

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm *.o


