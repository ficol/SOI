#ifndef QUEUE_H
#define QUEUE_H

class Queue
{
private:
  struct Element
  {
	Element *next;
	Element *prev;
	int data;
    Element(int newData):next(nullptr), prev(nullptr), data(newData)
    {};
  };
  Element *head;
  Element *tail;
  int even;
  int odd;
public:
    Queue();
    ~Queue();

    int read();
    void put(int newElement);
    int get();
    int getEven();
    int getOdd();
};

#endif
