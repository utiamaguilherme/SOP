#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

#define T_PAR 1
#define T_IMPAR 2

#define NELEM 2000000

int v[NELEM];

int conta_lenta(int tipo)
{
     int i, total = 0;

     for (i = 0; i < NELEM; i++) {
	  if ((tipo == T_PAR) && ((v[i] % 2) == 0))
	      total++;
	  else if ((tipo == T_IMPAR) && ((v[i] % 2) != 0))
	       total++;
     }
     return total;
}


void * conta(void * arg){

	long i, total = 0;
	long t = (long)arg;

	if(t == T_PAR){
		for (i = 0; i < NELEM; i++) {
			total += (v[i] % 2 == 0);
		}
	}
	else if(t == T_IMPAR){
		for(i = 0; i < NELEM ; i++){
			total += (v[i] % 2 != 0);
		}
	}
    pthread_exit((void*) total);
}

int main(int argc, char *argv[])
{
     int i, rc;
     struct timeval tv_ini, tv_fim;
     unsigned long time_diff, sec_diff, usec_diff, msec_diff;

     srandom(time(NULL));
     for (i = 0; i < NELEM; i++) {
	  v[i] = (int)random();
/*	  v[i] = i*2;*/
     }

     /* marca o tempo de inicio */
     rc = gettimeofday(&tv_ini, NULL);
     if (rc != 0) {
	  perror("erro em gettimeofday()");
	  exit(1);
     }

	 pthread_t pairs, odds;
	 void * pares, *impares;
	 int rcc = pthread_create(&pairs, NULL, conta, (void*) 1);
 	 if(rcc){
 		 printf("ERRO AO CRIAR THREAD PAIRS %ld", pairs);
 		 exit(1);
 	 }
     rcc = pthread_create(&odds, NULL, conta, (void*) 2);
 	 if(rcc){
 		 printf("ERRO AO CRIAR THREAD ODDS %ld", odds);
 		 exit(1);
 	 }

	 pthread_join(pairs, &pares);

	 pthread_join(odds, &impares);


     /* marca o tempo de final */
     rc = gettimeofday(&tv_fim, NULL);
     if (rc != 0) {
	  perror("erro em gettimeofday()");
	  exit(1);
     }
     /* calcula a diferenca entre os tempos, em usec */
     time_diff = (1000000L*tv_fim.tv_sec + tv_fim.tv_usec) -
  	         (1000000L*tv_ini.tv_sec + tv_ini.tv_usec);
     /* converte para segundos + microsegundos (parte fracion�ria) */
     sec_diff = time_diff / 1000000L;
     usec_diff = time_diff % 1000000L;

     /* converte para msec */
     msec_diff = time_diff / 1000;
	 printf("\n------------COM MULTITHREAD------------\n");
     printf("O vetor tem %ld numeros pares e %ld numeros impares.\n", (long)pares,
	    (long)impares);
/*     printf("Tempo de execucao: %lu.%06lu seg\n", sec_diff, usec_diff);*/
     printf("Tempo de execucao: %lu.%03lu mseg\n", msec_diff, usec_diff%1000);

	 printf("\n------------SEM MULTITHREAD------------\n");

	 rc = gettimeofday(&tv_ini, NULL);
	 int parr = conta_lenta(1);
	 int imparr = conta_lenta(2);
	 rc = gettimeofday(&tv_fim, NULL);

	 time_diff = (1000000L*tv_fim.tv_sec + tv_fim.tv_usec) -
  	         (1000000L*tv_ini.tv_sec + tv_ini.tv_usec);
     /* converte para segundos + microsegundos (parte fracion�ria) */
     sec_diff = time_diff / 1000000L;
     usec_diff = time_diff % 1000000L;

     /* converte para msec */
     msec_diff = time_diff / 1000;

	 printf("O vetor tem %d numeros pares e %d numeros impares.\n", parr,
	    imparr);
/*     printf("Tempo de execucao: %lu.%06lu seg\n", sec_diff, usec_diff);*/
     printf("Tempo de execucao: %lu.%03lu mseg\n\n", msec_diff, usec_diff%1000);

     return 0;
}
