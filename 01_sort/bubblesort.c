#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ELAPSED_SEC(cs, ce) ((double)(ce - cs) / CLOCKS_PER_SEC)

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

// fill array with random integer
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

int main()
{
    const int N = 10000;
    int array[N];

    fill_random(array, N);

    printf("start ... ");
    clock_t c_start = clock();

    bubbleSort(array, N);

    clock_t c_end = clock();
    printf("finished\n");

    print_all(array, N);

    printf("elapsed: %f[s]\n", ELAPSED_SEC(c_start, c_end));

    return 0;
}
