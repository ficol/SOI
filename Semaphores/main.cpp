#include <thread>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <unistd.h>
#include "queue.h"
#include "semaphore.h"

#define NUMBER_OF_PROCESSES 100
Queue a;

Semaphore mutex(1);
Semaphore mutex_A1(0);
Semaphore mutex_A2(0);
Semaphore mutex_B1(0);
Semaphore mutex_B2(0);

int A1Waiting = 0;
int A2Waiting = 0;
int B1Waiting = 0;
int B2Waiting = 0;

void produceEven()
{
  usleep(100000);
  int random = std::rand() % 100;
  if(random % 2 == 1)
    --random;
  a.put(random);
  std::cout<<"A1 number of even: "<<a.getEven()<<" number of odd: "<<a.getOdd()<<std::endl;
}

void produceOdd()
{
  usleep(100000);
  int random = std::rand() % 100;
  if(random % 2 == 0)
    ++random;
  a.put(random);
  std::cout<<"A2 number of even: "<<a.getEven()<<" number of odd: "<<a.getOdd()<<std::endl;
}

void consumeEven()
{
  usleep(100000);
  a.get();
  std::cout<<"B1 number of even: "<<a.getEven()<<" number of odd: "<<a.getOdd()<<std::endl; 
}

void consumeOdd()
{
  usleep(100000);
  a.get();
  std::cout<<"B2 number of even: "<<a.getEven()<<" number of odd: "<<a.getOdd()<<std::endl;
}

void *prod_A1(void*)
{
while(1)
{
  mutex.P();
  std::cout<<"Entered A1\n";
  if(a.getEven() >= 10)
  {
	  ++A1Waiting;
	  std::cout<<"Leave A1\n";
	  mutex.V();
    usleep(10000);
	  mutex_A1.P();
	  std::cout<<"Entered A1\n";
	  --A1Waiting;
  }
  produceEven();
  std::cout<<"Leave A1\n";
  if(a.getEven() > a.getOdd() && A2Waiting > 0)
    mutex_A2.V();
  else if(a.getEven() + a.getOdd() >= 3 && B1Waiting > 0 && a.read() % 2 == 0)
    mutex_B1.V();
  else if(a.getEven() + a.getOdd() >= 7 && B2Waiting > 0 && a.read() % 2 == 1)
    mutex_B2.V();
  else mutex.V();
}
}

void *prod_A2(void*)
{
  mutex.P();
  std::cout<<"Entered A2\n";
  if(a.getEven() <= a.getOdd())
  {
	  ++A2Waiting;
	  std::cout<<"Leave A2\n";
	  mutex.V();
	  mutex_A2.P();
	  std::cout<<"Entered A2\n";
	  --A2Waiting;
  }
  produceOdd();
  std::cout<<"Leave A2\n";
  if(a.getEven() <= 9 && A1Waiting > 0)
    mutex_A1.V();
  else if(a.getEven() + a.getOdd() >= 3 && B1Waiting > 0 && a.read() % 2 == 0)
    mutex_B1.V();
  else if(a.getEven() + a.getOdd() >= 7 && B2Waiting > 0 && a.read() % 2 == 1)
    mutex_B2.V();
  else mutex.V();
}

void *cons_B1(void*)
{
while(1)
{
  mutex.P();
  std::cout<<"Entered B1\n";
  if(a.getEven() + a.getOdd() <= 3 || a.read() % 2 == 1)
  {
	  ++B1Waiting;
	  std::cout<<"Leave B1\n";
	  mutex.V();
	  mutex_B1.P();
	  std::cout<<"Entered B1\n";
	  --B1Waiting;
  }
  consumeEven();
  std::cout<<"Leave B1\n";
  if(a.getEven() <= 9 && A1Waiting > 0)
    mutex_A1.V();
  else if(a.getEven() > a.getOdd() && A2Waiting > 0)
    mutex_A2.V();
  else if(a.getEven() + a.getOdd() >= 7 && B2Waiting > 0 && a.read() % 2 == 1)
    mutex_B2.V();
  else mutex.V();
}
}

void *cons_B2(void*)
{
while(1)
{
  mutex.P();
  std::cout<<"Entered B2\n";
  if(a.getEven() + a.getOdd() <= 7 || a.read() % 2 == 0)
  {
	  ++B2Waiting;
	  std::cout<<"Leave B2\n";
	  mutex.V();
	  mutex_B2.P();
	  std::cout<<"Entered B2\n";
	  --B2Waiting;
  }
  consumeOdd();
  std::cout<<"Leave B2\n";
  if(a.getEven() <= 9 && A1Waiting > 0)
    mutex_A1.V();
  else if(a.getEven() > a.getOdd() && A2Waiting > 0)
    mutex_A2.V();
  else if(a.getEven() + a.getOdd() >= 3 && B1Waiting > 0 && a.read() % 2 == 0)
    mutex_B1.V();
  else mutex.V();
}
}

int main() 
{ 
  std::srand(std::time(nullptr));
  pthread_t thread[NUMBER_OF_PROCESSES];
  int random;
  for(int i = 0; i != NUMBER_OF_PROCESSES; ++i)
  {
	random = rand() % 4;
	switch(random)
	{
	  case 0:  pthread_create(&thread[i], nullptr, &prod_A1, nullptr);
	  break;
	  case 1:  pthread_create(&thread[i], nullptr, &prod_A2, nullptr);
	  break;
	  case 2:  pthread_create(&thread[i], nullptr, &cons_B1, nullptr);
	  break;
	  default:  pthread_create(&thread[i], nullptr, &cons_B2, nullptr);
    }
  }
  std::cin.ignore();
  return 0;
} 
