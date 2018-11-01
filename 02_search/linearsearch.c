#include <stdio.h>
#include <time.h>
#include "utils.h"

#define NOT_FOUND -1

// linear search
int linearSearch(int x, int *data, int n)
{
    int i = 0;

    // search till end
    while ((i < n) && (data[i] != x)) {
        i++;
    }

    if (i < n) {
        return i;
    }

    return NOT_FOUND;
}

int main()
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
