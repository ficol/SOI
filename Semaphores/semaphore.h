#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <semaphore.h>

class Semaphore
{
private:
    sem_t sem;

public:
    Semaphore(int value);
    ~Semaphore();

    void P();
    void V();
};

#endif
