#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS    13

void *PrintHello(void *arg) {
   long id = (long)arg;
   printf("Alo da thread %ld\n",
          id);
   pthread_exit(NULL);
}

void *GetSquare(void *arg){
	long aux = (long)arg;

	printf("O quadrado de %ld eh %ld\n", aux, aux*aux);
	pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
   pthread_t threads[NUM_THREADS];
   int rc;
   long t;
   for (t=0; t<NUM_THREADS; t++){
      printf("main: criando thread %ld\n", t);
      rc = 	(
		  		(t < 5) ?
		  		pthread_create(&threads[t], NULL, PrintHello, (void *) t) :
				pthread_create(&threads[t], NULL, GetSquare, (void *) t )
				) ;
      if (rc) {
         printf("ERRO - rc=%d\n", rc);
         exit(-1);
      }
   }
   /* Ultima coisa que main() deve fazer */
   pthread_exit(NULL);
}
