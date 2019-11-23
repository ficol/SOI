#include <cstdlib>
#include <iostream>
#include <ctime>
#include <unistd.h>
#include "monitor.h"
#include "queue.h"

class MyMonitor: public Monitor
{
    Queue buff;
    Condition A1, A2, B1, B2;
public:
    MyMonitor() : Monitor()
    {};

    void produceEven()
    {
        enter();
        std::cout<<"Enter A1\n";
        if(buff.getEven() >= 10)
        {
            std::cout<<"Leave A1\n";
            wait(A1);
            std::cout<<"Enter A1\n";
        }
        usleep(100000);
        int random = std::rand() % 100;
        if(random % 2 == 1)
          --random;
        buff.put(random);
        std::cout<<"A1 number of even: "<<buff.getEven()<<" number of odd: "<<buff.getOdd()<<std::endl;
        std::cout<<"Leave A1\n";
        if(buff.getEven() > buff.getOdd() && A2.signal())
        {}
        else if(buff.getEven() + buff.getOdd() >= 3 && buff.read() % 2 == 0 && B1.signal())
        {}
        else if(buff.getEven() + buff.getOdd() >= 7 && buff.read() % 2 == 1 && B2.signal())
        {}
        else leave();
    }

    void produceOdd()
    {
        enter();
        std::cout<<"Enter A2\n";
        if(buff.getEven() <= buff.getOdd())
        {
            std::cout<<"Leave A2\n";
            wait(A2);
            std::cout<<"Enter A2\n";
        }
        usleep(100000);
        int random = std::rand() % 100;
        if(random % 2 == 0)
            ++random;
        buff.put(random);
        std::cout<<"A2 number of even: "<<buff.getEven()<<" number of odd: "<<buff.getOdd()<<std::endl;
        std::cout<<"Leave A2\n";
        if(buff.getEven() <= 9 && A1.signal())
        {}
        else if(buff.getEven() + buff.getOdd() >= 3 && buff.read() % 2 == 0 && B1.signal())
        {}
        else if(buff.getEven() + buff.getOdd() >= 7 && buff.read() % 2 == 1 && B2.signal())
        {}
        else leave();
    }
    
    void consumeEven()
    {
        enter();
        std::cout<<"Enter B1\n";
        if(buff.getEven() + buff.getOdd() <= 3 || buff.read() % 2 == 1)
        {
            std::cout<<"Leave B1\n";
            wait(B1);
            std::cout<<"Enter B1\n";
        }
        usleep(100000);
        buff.get();
        std::cout<<"B1 number of even: "<<buff.getEven()<<" number of odd: "<<buff.getOdd()<<std::endl;
        std::cout<<"Leave B1\n";
        if(buff.getEven() <= 9 && A1.signal())
        {}
        else if(buff.getEven() > buff.getOdd() && A2.signal())
        {}
        else if(buff.getEven() + buff.getOdd() >= 7 && buff.read() % 2 == 1 && B2.signal())
        {}
        else leave();
    }

    void consumeOdd()
    {
        enter();
        std::cout<<"Enter B2\n";
        if(buff.getEven() + buff.getOdd() <= 7 || buff.read() % 2 == 0)
        {
            std::cout<<"Leave B2\n";
            wait(B2);
            std::cout<<"Enter B2\n";
        }
        usleep(100000);
        buff.get();
        std::cout<<"B2 number of even: "<<buff.getEven()<<" number of odd: "<<buff.getOdd()<<std::endl;
        std::cout<<"Leave B2\n";
        if(buff.getEven() <= 9 && A1.signal())
        {}
        else if(buff.getEven() > buff.getOdd() && A2.signal())
        {}
        else if(buff.getEven() + buff.getOdd() >= 3 && buff.read() % 2 == 0 && B1.signal())
        {}
        else leave();
    }
};