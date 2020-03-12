#include "includes/Candidato.hpp"

Candidato::Candidato(std::string name, unsigned int number){
    this->name = name;
    this->number = number;
    this->votos = 0;
}

std::string Candidato::getName(){
    return this->name;
}

unsigned int Candidato::getNumber(){
    return this->number;
}

unsigned int Candidato::getVotos(){
  return this->votos;
}

void Candidato::insereVotos(unsigned int votos){
  this->votos = votos;
}
