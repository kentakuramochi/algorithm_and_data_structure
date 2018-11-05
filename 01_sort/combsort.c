#include <stdio.h>
#include <time.h>
#include "utils.h"

// comb sort
void combSort(int *data, int n, double k)
{
    int tmp, flag, gap;
    // a gap between 2 compared elements
    gap = n;

    do {
        // the gap is divided by k (shrink factor)
        gap = (int)(gap / k);

        if (gap == 0) {
            gap = 1;
        }

        flag = 1;
        for (int i = 0; i < (n - gap); i++) {
            // swap
            if (data[i] > data[i + gap]) {
                flag = 0;
                tmp = data[i];
                data[i] = data[i + gap];
                data[i + gap] = tmp;
            }
        }
    // if gap = 1, it equivalent to bubble sort
    } while ((gap > 1) || (flag != 1));
}

int main(void)
{
    const int N = 10000;
    int array[N];

    clock_t start, end;

    fill_random(array, N);

    START(start);

    combSort(array, N, 1.3);

    FINISH(end);

    print_all(array, N);

    printf("elapsed: %f[s]\n", ELAPSED_SEC(start, end));

    return 0;
}
