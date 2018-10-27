#include <stdio.h>
#include <time.h>
#include "utils.h"

// quicksort
void quickSort(int *data, int bottom, int top)
{
    if (bottom >= top) {
        return;
    }

    // set a head value as a pivot
    int pivot = data[bottom];

    int lower_idx = bottom, upper_idx = top;
    int tmp;

    while (lower_idx < upper_idx) {
        while ((lower_idx <= upper_idx) && (data[lower_idx] <= pivot)) {
            lower_idx++;
        }
        while ((lower_idx <= upper_idx) && (data[lower_idx] > pivot)) {
            upper_idx--;
        }

        // swap
        if (lower_idx < upper_idx) {
            tmp = data[lower_idx];
            data[lower_idx] = data[upper_idx];
            data[upper_idx] = tmp;
        }
    }

    tmp = data[bottom];
    data[bottom] = data[upper_idx];
    data[upper_idx] = tmp;

    // recursion
    quickSort(data, bottom, upper_idx -1);
    quickSort(data, upper_idx + 1, top);
}

int main()
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
