#include "includes/shared.hpp"
#include "includes/utils.hpp"
#include "includes/Validator.hpp"
#include "includes/Contador.hpp"
#include "includes/Queue.hpp"
#include <pthread.h>
#include <cstdio>

using namespace std;

set<unsigned int> Validator::candidates;
unsigned int Validator::lidos;
unsigned int Validator::validos;

Validator::Validator(string arq){

  fstream in(arq,ios::in);

  while(true){
    string line;
    unsigned int candidate = 0x3f3f3f3f;
    string aux;
    getline(in, line);
    // cerr << line;
    if(!in.good())
      break;
    for(auto c : line){
      if(c == ' '){
        candidate = (unsigned int)stoi(aux);
        break;
      }
      aux+=c;
    }
    // cout << " = " << candidate << endl;
    if(candidate != 0x3f3f3f3f){
      candidates.insert(candidate);
      // cout << "insert: " << candidate << endl;
    }else{
      break;
    }

  }

}

Validator::Validator(string arq, unsigned int ntr){
    this->arq = arq;
    this->threadId = ntr;
}

bool Validator::isValid(unsigned int n){
  return (Validator::candidates.find(n) != Validator::candidates.end());
}

void * Validator::work(void* data){
  // *(arguments *) (args);
  Data data_w = *(Data*) (data);
  string arq = data_w.file;
  Queue ** queue = data_w.queue;
  ifstream in(arq, ios::in);

  //Avisa as demais Threads que esta pronto
  printf("%s Ready\n", arq.c_str());
  // cout << arq << " Ready\n";
  pthread_barrier_wait(&barrier_init);
  //Aguarda as demais Threads se necessario

  while(true){
    unsigned int n;
    string line;

    getline(in,line);

    if(!in.good())
      break;

    bool flag = true;
    for(char c : line){
      if((c < '0' or c > '9')){
        n = 0x3f3f3f3f;
        flag = false;
        break;
      }
    }
    if(!flag){
      pthread_mutex_lock(&mtx);
      Validator::lidos++;
      pthread_mutex_unlock(&mtx);
    }else{
      bool valid = Validator::isValid(n);
      pthread_mutex_lock(&mtx);
      if(valid){
        printf("adding %d\nSize %d\n", n, (*queue)->getSize());
        Validator::lidos++;
        Validator::validos++;
        (*queue)->add(n);
        if((*queue)->getSize() == 1){
          pthread_cond_signal(&emptyq);
        }
      }else{
        Validator::lidos++;
      }
      pthread_mutex_unlock(&mtx);
    }
  }

  pthread_barrier_wait(&barrier_end);
  Contador::setDone(true);
  //Avisa as demais Threads que terminou de
  //validar os votos referentes a seu arquivo
  pthread_exit(NULL);
}

string Validator::getArq(){
    return this->arq;
}
