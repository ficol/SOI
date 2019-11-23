#include <thread>
#include "mymonitor.h"

#define NUMBER_OF_PROCESSES 100
MyMonitor a;

void *prod_A1(void*)
{
  while(1)
    a.produceEven();
}

void *prod_A2(void*)
{
  while(1)
    a.produceOdd();
}

void *cons_B1(void*)
{
  while(1)
    a.consumeEven();
}

void *cons_B2(void*)
{
  while(1)
    a.consumeOdd();
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
