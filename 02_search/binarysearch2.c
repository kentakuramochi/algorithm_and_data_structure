#include <stdio.h>
#include <time.h>
#include "utils.h"

#define NOT_FOUND -1

// binary search
int binarySearch(int x, int *data, int left, int right)
{
    int mid;

    while (left <= right) {
        // check mid point
        mid = (left + right) / 2;

        // halve search range
        if (data[mid] < x) {
            left = mid + 1;
        } else {
            right = mid;
        }

        // return the first index when same values are in array
        if (data[left] == x) {
            return left;
        }
    }

    return NOT_FOUND;
}

int main(void)
{
    const int N = 10000;
    int array[N];
    clock_t start, end;

    // sorted array
    for (int i = 0; i < N; i++) {
        array[i] = i;
    }

    int x;
    printf("search: ");
    scanf("%d", &x);

    START(start);

    int idx = binarySearch(x, array, 0, N - 1);

    FINISH(end);

    if (idx == NOT_FOUND) {
        printf("not found\n");
    } else {
        printf("index: %d\n", idx);
    }

    printf("elapsed: %f[s]\n", ELAPSED_SEC(start, end));

    return 0;
}
