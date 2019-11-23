CC=g++
CFLAGS= -Wall -pthread -std=c++11

all: queue.o semaphore.o main.o 
	$(CC) $(CFLAGS) queue.o semaphore.o main.o -o semaphore

queue.o: queue.cpp
	$(CC) $(CFLAGS) -c queue.cpp
	
semaphore.o: semaphore.cpp
	$(CC) $(CFLAGS) -c semaphore.cpp
	
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp
	
run:
	./semaphore
	
clean:
	rm -f *.o

