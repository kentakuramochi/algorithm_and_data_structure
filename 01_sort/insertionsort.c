#include <stdio.h>
#include <time.h>
#include "utils.h"

// insertion sort
void insertionSort(int *data, int n)
{
    int i, sorted, insert;

    for (sorted = 0; sorted < (n - 1); sorted++) {
        // get next value of sorted list
        insert = data[sorted++];

        // search a position to insert
        for (i = 0; i <= sorted; i++) {
            if (data[i] > insert) {
                break;
            }
        }

        // insert and shift
        while (i <= (sorted + 1)) {
            int tmp = data[i];
            data[i] = insert;
            insert = tmp;
            i++;
        }
    }
}

int main(void)
{
    const int N = 10000;
    int array[N];

    clock_t start, end;

    fill_random(array, N);

    START(start);

    insertionSort(array, N);

    FINISH(end);

    print_all(array, N);

    printf("elapsed: %f[s]\n", ELAPSED_SEC(start, end));

    return 0;
}
