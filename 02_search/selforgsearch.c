#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils.h"

#define NOT_FOUND -1

// self organization search
int selfOrganizationSearch(int x, int *data, int num)
{
    int n = 0;

    while ((n < num) && (data[n] != x)) {
        n++;
    }

    if (n < num) {
        // a target value moves forward
        if (n > 0) {
            int tmp = data[n - 1];
            data[n - 1] = data[n];
            data[n] = tmp;
            return n - 1;
        }
        return n;
    }

    return NOT_FOUND;
}

int main(void)
{
    const int N = 10000;
    const int MAX = 100;
    int array[N];
    clock_t start, end;

    fill_random_under(array, N, MAX);

    int x, idx;
    while (true) {
        printf("input search num (0~%d, -1: quit)\n", MAX - 1);
        printf("> ");
        scanf("%d", &x);

        if (x == -1) {
            break;
        }

        START(start);

        idx = selfOrganizationSearch(x, array, N);

        FINISH(end);

        if (idx == NOT_FOUND) {
            printf("not found\n");
        } else {
            printf("index: %d\n", idx);
        }

        printf("elapsed: %f[s]\n", ELAPSED_SEC(start, end));
    }

    return 0;
}

