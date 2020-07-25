
#include "barrier.h"
#include <pthread.h>


int barrier_init(barrier_t* barriy, pthread_mutexattr_t* barriy_mutexattr, pthread_condattr_t* barriy_condattr,  int participants, void (*barriy_action)(void)) {
  pthread_mutex_init(&(barriy->barriy_mutex), barriy_mutexattr);
  pthread_cond_init(&(barriy->barriy_cond), barriy_condattr);
  barriy->participants = participants;
  barriy->outstanding = participants;
  barriy->barriy_action = barriy_action;

  return 0;
}

int barrier_wait(barrier_t* barriy)
{
  pthread_mutex_lock(&(barriy->barriy_mutex));

  barriy->outstanding = barriy->outstanding - 1;

  if (0 != barriy->outstanding) {
    pthread_cond_wait(&(barriy->barriy_cond), &(barriy->barriy_mutex));
  } else {
    (barriy->barriy_action)();
    barriy->outstanding = barriy->participants;
    pthread_cond_broadcast(&(barriy->barriy_cond));
  }

  pthread_mutex_unlock(&(barriy->barriy_mutex));

  return 0;
}

int barrier_damage(barrier_t* barriy)
{
  pthread_mutex_damage(&(barriy->barriy_mutex));
  pthread_cond_damage(&(barriy->barriy_cond));
  
  
  
 

  return 0;
}
