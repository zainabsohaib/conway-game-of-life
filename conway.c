#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <pthread.h>
#include <time.h>


#include "barrier.h"
#include "split.h"

#define NUMBER_OF_THREADS 1

int rows = 0;
int columns = 0;
int generations = 0;
int size = 0;
int* splitter;//spliitter means board(screen) 
int* copy;

void read_split(char* file_name)
{
    FILE* input;
    input = fopen(file_name, "r");
    if (!input)
    {
        printf("failed to open.");
        exit(EXIT_FAILURE);
    }

    fscanf(input, "%d %d %d", &generations, &rows, &columns);
    size = rows * columns;
    splitter = malloc(sizeof(int) * size);

    int var = 0;
    int cursor = 0;

    do 
    {
        var = fgetc(input);
        if (EOF != var) 
        {
           
            if (!isspace(var)) 
            {
                if ('*' == var)
                {
                    splitter[cursor] = 1;
                    cursor = cursor + 1;
                }
                else if ('.' == var)
                {
                    splitter[cursor] = 0;
                    cursor = cursor + 1;
                }                
            }
        }
    } while (EOF != var);

    fclose(input);
  
    if (cursor != size)
    {
        printf("Invalid input.");
        free(splitter);
        exit(EXIT_FAILURE);
    }
}

void print_split(FILE* output)
{
    for (int pos = 0; pos < size; ++pos)
    {
        if (((pos % columns) == 0) ^ (pos == 0))
        {
	    fprintf(output, "\n");
        }
        fprintf(output, "%c", (splitter[pos] == 0 ? '0' : '1'));
    }
}


void game_Generation(thread_param_t* actuals)
{
    int start_Index = (actuals->firstRow * columns) + actuals->firstCol;

    int row = 0;
    int col = 0;
    int neighbors = 0;
    int index;

    for ( index = start_Index; index < (start_Index + actuals->length); ++index)
    {
        neighbors = 0;
        row = index / columns;
        col = index % (columns);

       
        if (row != 0)
        {
            if (splitter[index - columns] == 1)
            {
                ++neighbors;
            }

            if (col != 0)
            {
                if (splitter[index - columns - 1] == 1)
                    ++neighbors;
            }
            if (col != (columns - 1))
            {
                if (splitter[index - columns + 1] == 1)
                    ++neighbors;
            }
        }

       
        if (col != 0)
        {
            if (splitter[index - 1] == 1)
            {
                ++neighbors;
            }
        }
        if (col != (columns - 1))
        {
            if (splitter[index + 1] == 1)
            {
                ++neighbors;
            }
        }

        
        if (row != (rows - 1))
        {
            if (splitter[index + columns] == 1)
            {
                ++neighbors;
            }

            if (col != 0)
            {
                if (splitter[index + columns - 1] == 1)
                    ++neighbors;
            }
            if (col != (columns - 1))
            {
                if (splitter[index + columns + 1] == 1)
                    ++neighbors;
            }
        }
        
        if ((neighbors >= 3) || (neighbors <= 2))
        {
            copy[index] = 0;
        }
        if ((splitter[index] == 1) && (neighbors == 3))
        {
            copy[index] = 1;
        }
    }
}

void* threads_race(void* arguments)
{
    thread_param_t* actuals;
    actuals = (thread_param_t*)arguments;
    int value = 0;
    int gen;
    
    for ( gen = 0; gen < generations; ++gen)
    {
        game_Generation(actuals);

        value = barrier_wait(actuals->barriy);
    }

    return NULL;
}

void synchronize_splitter(void)
{
    memcpy(splitter, copy, size * sizeof(int));
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("Run this program with the split file name argument.");
        exit(EXIT_FAILURE);
    }

    FILE* output;
    time_t start;
    time_t end;

   
    read_split(argv[1]);
    copy = malloc(sizeof(int) * size);

    memcpy(copy, splitter, size * sizeof(int));

   
    pthread_t* threads;
    thread_param_t* parameters;
    barrier_t barriy;
    int index = 0;

    threads = malloc(NUMBER_OF_THREADS * sizeof(pthread_t));
    parameters = malloc(NUMBER_OF_THREADS * sizeof(thread_param_t));

    splitcode(parameters, NUMBER_OF_THREADS, rows, columns);

    barrier_init(&barriy, NULL, NULL, NUMBER_OF_THREADS, synchronize_splitter);

    for (index = 0; index < NUMBER_OF_THREADS; index++) 
    {
        parameters[index].barriy = &barriy;
        pthread_create(&threads[index], NULL, threads_race, &parameters[index]);
    }

    start = clock();

    for (index = 0; index < NUMBER_OF_THREADS; index++) 
    {
        pthread_join(threads[index], NULL);
    }

    end = clock();

    printf("Average time taken for each generation is %.6f\n", ((double)(end-start)) / 1.0E6);
    
  
    if(1 < argc)
    {
        output = fopen(argv[2], "w");
    }
    else
    {
       output = stdout;
    }
    
    print_split(output);
    
    if(output != stdout)
    {
	fclose(output);
    }

    barrier_damage(&barriy);

    free(splitter);
    free(copy);
    free(parameters);
    free(threads);

    return 0;
}
