#include <stdio.h>
#include <time.h>
#include "utils.h"

// bubblesort
void bubbleSort(int *array, int n)
{
    int tmp, flag;

    do {
        flag = 0;
        for (int i = 0; i < n - 1; i++) {
            // if array[i] is bigger than array[i + 1]
            if (array[i] > array[i + 1]) {
                flag = 1;
                // swap
                tmp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = tmp;
            }
        }
    // while no swapping
    } while (flag == 1);
}

int main()
{
    const int N = 10;
    int array[N];
    clock_t start, end;

    fill_random(array, N);

    START(start);

    bubbleSort(array, N);

    FINISH(end);

    print_all(array, N);

    printf("elapsed: %f[s]\n", ELAPSED_SEC(start, end));

    return 0;
}
