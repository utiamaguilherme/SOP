#pragma once
#include <string>

class Candidato {
private:
    std::string name;
    unsigned int number;
    unsigned int votos;
public:
    Candidato(std::string name, unsigned int number);
    std::string getName();
    unsigned int getNumber();
    unsigned int getVotos();
    void insereVotos(unsigned int);
};
