


#include "barrier.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct thread_param_t {
    int length;
    int firstRow;
    int firstCol;
    barrier_t* barriy;
} thread_param_t;

int splitcode(thread_param_t* threadList, int threadCount, int rows, int columns);
