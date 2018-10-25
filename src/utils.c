// utils.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

// fill integer array with random value
void fill_random(int *array, int n)
{
    srand((unsigned int)time(NULL));

    for (int i = 0; i < n; i++) {
        array[i] = rand();
    }
}

// print all elements of array
void print_all(int *array, int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    putchar('\n');
}
