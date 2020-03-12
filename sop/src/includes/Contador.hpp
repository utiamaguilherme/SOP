#pragma once
#include <cstdlib>
#include <vector>
#include <map>
#include "Queue.hpp"
#include "Candidato.hpp"

class Contador {
private:
  static std::map<unsigned int,unsigned int> votos; // map<numero_candidato,qtd_votos>
  std::vector<Candidato> candidatos;
  static bool done;
public:
  static Queue * queue;
  Contador(std::string);
  static void contabiliza_voto(unsigned int);
  static void * work(void*);
  static void setDone(bool);
  static bool isDone();
  std::vector<Candidato> apura();
  // static std::vector<Candidato> candidatos;

};
