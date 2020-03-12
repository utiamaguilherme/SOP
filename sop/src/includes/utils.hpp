#pragma once
#include <bits/stdc++.h>
#include <pthread.h>
#include "Queue.hpp"
using namespace std;

/* Include para trabalho de apuracao de votos */

typedef struct data{
    Queue ** queue;
    string file;
} Data;

/* string de formato para cabecalho da lista de votos */
#define fmtcabvoto \
     "  Numero  Nome                            Votos validos     %%\n"

/* string de formato para votos de cada candidato */
#define fmtvoto "%8u  %-30s  %13u  %6.2f\n"

bool getFiles(vector<string>& files, const char * name, const char * nthr, unsigned int ithr);
