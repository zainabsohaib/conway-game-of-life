#ifndef barrier_h
#define barrier_h

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct barrier_t {
  pthread_mutex_t barriy_mutex;
  pthread_cond_t barriy_cond;
  int participants;
  int outstanding;
  void (*barriy_action) (void);
} barrier_t;

int barrier_init(barrier_t* barriy, pthread_mutexattr_t* barriy_mutexattr, pthread_condattr_t* barriy_condattr, int participants, void (*barriy_action)(void));

int barrier_wait(barrier_t* barriy);

int barrier_damage(barrier_t* barriy);

#endif
