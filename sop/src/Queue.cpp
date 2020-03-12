#include "includes/Queue.hpp"
#include <iostream>

using namespace std;

unsigned int Queue::size = 0;
unsigned int Queue::maxSize = 0;
Node ** Queue::last;

Queue::Queue(){
  this->node = NULL;
  last = &this->node;
  cerr << "Lived, still oK\n";
}

unsigned int Queue::getNext(){
  if(this->isEmpty()){
    return 0x3f3f3f3f;
  }
  size--;
  unsigned int returner = this->node->n;
  Node * nexter = this->node->next;
  delete this->node;
  this->node = nexter;

  return returner;
}

unsigned int Queue::getSize(){
  return Queue::size;
}

void Queue::add(unsigned int n){
  //cerr << "add\n";
  if(this->isEmpty()){
    // cerr << "node is null\n";
    this->node = new Node();
    this->node->n = n;
    this->node->next = NULL;
    last = &this->node->next;
    size++;
  }
  else{
    // cerr << "Why you here\n";
    *last = new Node();
    (*last)->n = n;
    (*last)->next = NULL;
    last = &((*last)->next);
    size++;
  }
  maxSize = max(size, maxSize);
  // cerr << "hmm\n";
}

bool Queue::isEmpty(){
  return size == 0;
}

unsigned int Queue::getMax(){
  return Queue::maxSize;
}
