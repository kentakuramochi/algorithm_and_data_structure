#include <stdio.h>
#include <time.h>
#include "utils.h"

// mergeSort
void mergeSort(int *data, int *buffer, int n)
{
    // if partition size <= 1, return
    if (n <= 1) {
        return;
    }

    // split data into 2 sublists recursively
    int m = n / 2;
    mergeSort(data, buffer, m);
    mergeSort(data + m, buffer, n - m);

    int i, j, k;
    // copy to buffer
    for (i = 0; i < m; i++) {
        buffer[i] = data[i];
    }

    j = m;
    i = k = 0;
    // compare and sort neighboring sublists
    while ((i < m) && (j < n)) {
        if (buffer[i] <= data[j]) {
            data[k++] = buffer[i++];
        } else {
            data[k++] = data[j++];
        }
    }
    while (i < m) {
        data[k++] = buffer[i++];
    }
}

int main()
{
    const int N = 10000;
    int array[N];
    int buffer[N];

    clock_t start, end;

    fill_random(array, N);

    START(start);

    mergeSort(array, buffer, N);

    FINISH(end);

    print_all(array, N);

    printf("elapsed: %f[s]\n", ELAPSED_SEC(start, end));

    return 0;
}
