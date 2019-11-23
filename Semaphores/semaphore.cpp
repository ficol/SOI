#include "semaphore.h"

Semaphore::Semaphore(int value)
{
  sem_init(&sem, 0, value);
}

Semaphore::~Semaphore()
{
  sem_destroy(&sem);
}

void Semaphore::P()
{
  sem_wait(&sem);
}

void Semaphore::V()
{
  sem_post(&sem);
}
