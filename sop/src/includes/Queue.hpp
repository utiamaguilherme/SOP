#pragma once
#include <cstdio>
#include <iostream>
#include <cstdlib>

typedef struct Node{
  unsigned int n;
  Node * next;
} Node;

class Queue {
private:
  static unsigned int size;
  static unsigned int maxSize;
  static Node ** last;
  Node * node;
public:
  Queue();
  unsigned int getNext();
  unsigned int getSize();
  void add(unsigned int n);
  bool isEmpty();
  static unsigned int getMax();

};
