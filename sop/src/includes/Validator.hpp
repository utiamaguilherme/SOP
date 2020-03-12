#pragma once
#include <cstdio>
#include <string>
#include <fstream>
#include <set>
#include "Queue.hpp"

class Validator {
private:
    static std::set<unsigned int> candidates;
    unsigned int threadId;
    std::string arq; //Arquivo de votos !!
public:
    static unsigned int lidos;
    static unsigned int validos;
    Validator(std::string arquivo);
    Validator(std::string arquivo, unsigned int ithread);
    static bool isValid(unsigned int n);
    std::string getArq();
    static void * work(void* queue);
};
