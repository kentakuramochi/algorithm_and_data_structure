#include <stdio.h>
#include <time.h>
#include "utils.h"

#define NOT_FOUND -1

// linear search with sentinel
int linearSearch(int x, int *data, int n)
{
    int i = 0;

    // set sentinel
    int s = data[n - 1];
    data[n - 1] = x;

    // search till end
    while (data[i] != x) {
        i++;
    }

    // retrieve tail value
    data[n - 1] = s;

    if (i < (n - 1)) {
        return i;
    }
    if (x == s) {
        return i;
    }

    return NOT_FOUND;
}

int main(void)
{
    const int N = 10000;
    int array[N];
    clock_t start, end;

    fill_random_under(array, N, 100);

    int x;
    printf("search: ");
    scanf("%d", &x);

    START(start);

    int idx = linearSearch(x, array, N);

    FINISH(end);

    if (idx == NOT_FOUND) {
        printf("not found\n");
    } else {
        printf("index: %d\n", idx);
    }

    printf("elapsed: %f[s]\n", ELAPSED_SEC(start, end));

    return 0;
}
