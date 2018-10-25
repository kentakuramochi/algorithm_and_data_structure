// utils.h
// utility functions and macros

#ifndef _UTILS_H_
#define _UTILS_H_

// print message and get current clock_t
#define START(c)  { fputs("start ... ", stdin); (c) = clock(); }
#define FINISH(c) { fputs("finished\n", stdin); (c) = clock(); }

// calculate elapsed time[s] between 2 clock_t
#define ELAPSED_SEC(c_str, c_end) ((double)(c_end - c_str) / CLOCKS_PER_SEC)

// fill integer array with random value
void fill_random(int *array, int n);

// print all elements of array
void print_all(int *array, int n);

#endif
