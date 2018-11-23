#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

// num of data
#define N 10
// num of separator
#define SEPARATOR 3

// separate values into (SEPARATOR + 1) group and accumulate numbers of each group
// minimize max of each sum
const int value[N] = { 15, 3, 7, 6, 10, 4, 13, 2, 3, 6 };

// max macro
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

// solve the best separation with table
// table cell
typedef struct {
    int solution; // best solution
    int num;      // num of values in group
} cell;

int main(void)
{
    cell solutions[N][SEPARATOR + 1];
    int i, j, s, sum;
    clock_t start, finish;

    START(start);

    // from tail of values
    for (i = N - 1; i >= 0; i--) {
        // check sum of each group with adding separator
        for (j = 0; j < SEPARATOR + 1; j++) {
            solutions[i][j].num = 0;
            for (sum = 0, s = i; s < N; s++) {
                sum += value[s];
                if (j == 0 || i == N - 1 || solutions[i][j].num == 0
                    || (s != N - 1 && solutions[i][j].solution > MAX(sum, solutions[s + 1][j - 1].solution))) {
                    // if first column/last row, the best solution is sum
                    if (j == 0 || i == N - 1) {
                        solutions[i][j].solution = sum;
                    // compare and save better solution
                    } else {
                        solutions[i][j].solution = MAX(sum, solutions[s + 1][j - 1].solution);
                    }
                    solutions[i][j].num = s - i + 1;
                }
            }
        }
    }

    FINISH(finish);
    printf("elapsed: %f[s]\n", ELAPSED_SEC(start, finish));

    // display table
    printf("separator");
    for (i = 0; i < N; i++) {
        printf("%6d ", value[i]);
    }
    printf("\n");
    for (j = 0; j < SEPARATOR + 1; j++) {
        printf("%8d ", j);
        for (i = 0; i < N; i++) {
            printf("(%2d,%2d)", solutions[i][j].num, solutions[i][j].solution);
        }
        printf("\n");
    }

    printf("\nmax sum: %d\nseparation: ", solutions[0][SEPARATOR].solution);
    for (i = 0, j = SEPARATOR; j >= 0 && i != N; j--) {
        printf("[%d] ", solutions[i][j].num);
        i += solutions[i][j].num;
    }
    printf("\n");

    return EXIT_SUCCESS;
}