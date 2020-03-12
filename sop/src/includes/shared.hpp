#pragma once
#include <pthread.h>

extern pthread_mutex_t mtx;
extern pthread_cond_t emptyq;
extern pthread_barrier_t barrier_init;
extern pthread_barrier_t barrier_end;
