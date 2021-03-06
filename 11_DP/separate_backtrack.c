#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "utils.h"

#define N 10
#define SEPARATOR 3

// separate values into (SEPARATOR + 1) group and accumulate numbers of each group
// minimize max of each sum
int value[N] = { 15, 3, 7, 6, 10, 4, 13, 2, 3, 6 };
int sep_pos[SEPARATOR] = { 0 };

// best separation
int best_sep_pos[SEPARATOR] = { 0 };
// max of sum
int best_sep_max_value = INT_MAX;

// separate values into groups
void separate(int pos, int num)
{
    int i, j, sum, start, end, max;

    // set separator
    sep_pos[num++] = pos;

    // if all separator is set
    if (num == SEPARATOR) {
        max = 0;

        // calculate max of sum of each group: value[sep_pos[i - 1]] to value[sep_pos[i]]
        for (i = 0; i <= SEPARATOR; i++) {
            start = (i == 0) ? 0 : sep_pos[i - 1];
            end = (i == SEPARATOR) ? N : sep_pos[i];
            sum = 0;
            for (j = start; j < end; j++) {
                sum += value[j];
            }
            if (sum > max) {
                max = sum;
            }
        }

        // if max of each sum is less than the current max, save the position
        if (max < best_sep_max_value) {
            best_sep_max_value = max;
            for (i = 0; i < SEPARATOR; i++) {
                best_sep_pos[i] = sep_pos[i];
            }
        }

        return;
    }

    // try next separation
    for (i = (pos + 1); i < (N - SEPARATOR + num + 1); i++) {
        separate(i, num);
    }
}

int main(void)
{
    int i, j, start, end;
    clock_t c_start, c_finish;

    START(c_start);

    // separate from head
    for (i = 0; i < (N - SEPARATOR); i++) {
        separate(i, 0);
    }

    FINISH(c_finish);
    printf("elapsed: %f[s]\n", ELAPSED_SEC(c_start, c_finish));

    // print separation
    printf("values: ");
    for (i = 0; i < N; i++) {
        printf("%d ", value[i]);
    }
    printf("\n\n");
    for (i = 0; i <= SEPARATOR; i++) {
        start = (i == 0) ? 0 : best_sep_pos[i - 1];
        end = (i == SEPARATOR) ? N : best_sep_pos[i];
        for (j = start; j < end; j++) {
            printf("%d ", value[j]);
        }
        if (end != N) {
            printf("|");
        }
    }
    printf("\n");

    return EXIT_SUCCESS;
}