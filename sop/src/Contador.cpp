#include "includes/shared.hpp"
#include "includes/Contador.hpp"
#include "includes/utils.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

map<unsigned int,unsigned int> Contador::votos;
Queue * Contador::queue;
bool Contador::done = false;

Contador::Contador(string filename){

  if(this->candidatos.size() > 1){
    return;
  }

  ifstream in(filename,ios::in);
  string line;
  string name;
  string aux;
  unsigned int number = 0x3f3f3f3f;

  if(!in.is_open()){
    cerr << "File not found\n";
    exit(1);
  }
  while(true){
    getline(in,line);
    if(!in.good())
      break;
    int sz = (int)line.size();
    //cout << "READ: " << line << endl;
    for(int i=0; i<sz; i++){
      if(line[i] == ' ' and number == 0x3f3f3f3f){
        while(line[i] == ' ')i++;
        //cout << "NUMBER: " << aux << endl;
        number = stoi(aux);
        aux = "";
      }
      if(line[i] == ' '){
        while(line[i] and line[i] == ' ')i++;
        if(line[i]){
          aux+=' ';
        }
      }
      aux+=line[i];
    }
    name = aux;

    this->candidatos.push_back(Candidato(name, number));
    this->votos.emplace(number,0);
    //cerr << name << " " << number << endl;
    number = 0x3f3f3f3f;
    line = "";
    aux = "";
  }

  for(auto c : this->candidatos){
    cout << c.getName() << " " << c.getNumber() << endl;
  }

  this->queue = new Queue();

}

void Contador::contabiliza_voto(unsigned int voto){

  if(voto != 0x3f3f3f3f){
    Contador::votos.find(voto)->second++;
    printf("Queue-- : Size = %u\n", Contador::queue->getSize());
  }else{
    cout << "Queue is empty, wait for more data\n";
  }

}

bool Contador::isDone(){
  return Contador::done;
}

void Contador::setDone(bool x){
  Contador::done = x;
}

void * Contador::work(void *sla_meu_batman){

  pthread_barrier_wait(&barrier_init);

  while(true){
    unsigned int candidate;
    //Semaforo pra ver se tem elemento na fila
    pthread_mutex_lock(&mtx);
    if(Contador::queue->isEmpty()){
      if(Contador::isDone()){
        pthread_mutex_unlock(&mtx);
        break;
      }
      pthread_cond_wait(&emptyq, &mtx);
    }
    candidate = Contador::queue->getNext();
    printf("removing %u\n", candidate);
    pthread_mutex_unlock(&mtx);
    contabiliza_voto(candidate);
  }

  pthread_exit(NULL);
}

bool comp(Candidato& a, Candidato& b){
  return a.getVotos() > b.getVotos();
}

vector<Candidato> Contador::apura(){
  for(auto v : votos){
    for(auto& c : this->candidatos){
      if(c.getNumber() == v.first){
        c.insereVotos(v.second);
        cout << v.second << endl;
        break;
      }
    }
  }
  sort(this->candidatos.begin(), this->candidatos.end(), comp);
  return this->candidatos;
}
