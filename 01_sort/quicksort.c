#include <stdio.h>
#include <time.h>
#include "utils.h"

// quicksort
void quickSort(int *data, int bottom, int top)
{
    // if partition size <= 1, return
    if (bottom >= top) {
        return;
    }

    // pivot: head value
    int *pivot = &data[bottom];

    int lower_idx = bottom, upper_idx = top;
    int tmp;

    while (lower_idx < upper_idx) {
        // search greater value than the pivot from head
        while ((lower_idx <= upper_idx) && (data[lower_idx] <= *pivot)) {
            lower_idx++;
        }
        // search lesser value than the pivot from tail
        while ((lower_idx <= upper_idx) && (data[lower_idx] > *pivot)) {
            upper_idx--;
        }

        // swap
        // move lesser value to forward and greater value to back
        if (lower_idx < upper_idx) {
            tmp = data[lower_idx];
            data[lower_idx] = data[upper_idx];
            data[upper_idx] = tmp;
        }
    }
    // partitioning: split data into 2 partition
    // forward: lesser values than the pivot
    // back: greater values than the pivot
    tmp = *pivot;
    *pivot = data[upper_idx];
    data[upper_idx] = tmp;

    // sort forward partition recursively
    quickSort(data, bottom, upper_idx - 1);
    // sort back partition too
    quickSort(data, upper_idx + 1, top);
}

int main(void)
{
    const int N = 10000;
    int array[N];
    clock_t start, end;

    fill_random(array, N);

    START(start);

    quickSort(array, 0, N - 1);

    FINISH(end);

    print_all(array, N);

    printf("elapsed: %f[s]\n", ELAPSED_SEC(start, end));

    return 0;
}
