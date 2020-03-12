#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS    13

void *GetSquare(void *arg){
	long aux = (long)arg;

	printf("O quadrado de %ld eh %ld\n", aux, aux*aux);
	aux *= aux;
	void * a = (void*)aux;
	pthread_exit(a);
}

int main (int argc, char *argv[]) {
	pthread_t threads[NUM_THREADS];
	void * maionese;
	long maioneses=0;
	int rc;
	long t;

	for (t=0; t<NUM_THREADS; t++){
	  printf("main: criando thread %ld\n", t);
	  rc = pthread_create(&threads[t], NULL, GetSquare, (void *) t );
	  if (rc) {
	     printf("ERRO - rc=%d\n", rc);
	     exit(-1);
	  }
	}

	for(t=0; t<NUM_THREADS; t++){
		rc = pthread_join(threads[t], &maionese);
		maioneses += (long)maionese;
	}
	printf("maioneses: %ld\n", maioneses);
	/* Ultima coisa que main() deve fazer */
	pthread_exit(NULL);
}
