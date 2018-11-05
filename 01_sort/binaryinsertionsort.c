#include <stdio.h>
#include <time.h>
#include "utils.h"

// binary insertion sort
void binaryInsertionSort(int *data, int n)
{
    int i, sorted, insert;
    int left, mid, right;

    for (sorted = 1; sorted < n; sorted++) {
        // get next value of sorted list
        insert = data[sorted];

        // search a position to insert
        // with binary search
        left = 0;
        right = sorted;
        while (left < right) {
            mid = (left + right) / 2;
            if (data[mid] < insert) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        i = left;

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

    binaryInsertionSort(array, N);

    FINISH(end);

    print_all(array, N);

    printf("elapsed: %f[s]\n", ELAPSED_SEC(start, end));

    return 0;
}
