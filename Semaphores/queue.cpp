#include "queue.h"

Queue::Queue():head(nullptr), tail(nullptr), even(0), odd(0)
{};

Queue::~Queue()
{
  for(Element *i = head; i != nullptr; i = i->next)
    delete i;
}

int Queue::read()
{
    return tail->data;
}

void Queue::put(int newElement)
{
  if(newElement % 2 == 0)
    ++even;
  else ++odd;
  if(head == tail && head == nullptr)
  {
    head = new Element(newElement);
    tail = head;
    return;
  }
  if(head == tail)
  {
    head = new Element(newElement);
    tail->next = head;
    head->prev = tail;
  }
  Element *tmp = new Element(newElement);
  head->next = tmp;
  tmp->prev = head;
  head = tmp;
}

int Queue::get()
{
  if(head->data % 2 == 0)
    --even;
  else --odd;
  int tmp = head->data;
  if(head == tail)
  {
    delete head;
    tail = head = nullptr;
    return tmp;
  }
  head = head->prev;
  delete head->next;
  head->next = nullptr;
  return tmp;
}

int Queue::getEven()
{
  return even;
}

int Queue::getOdd()
{
  return odd;
}
