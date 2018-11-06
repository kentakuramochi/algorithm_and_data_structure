#include <stdio.h>
#include <stdlib.h>

// calc GCD of 2 integers
int gcd(int a, int b)
{
    int i;

    for (i = a; i > 0; i--) {
        if ((a % i == 0) && (b % i == 0)) {
            break;
        }
    }

    return i;
}

// calc GCD of integer array
int multi_gcd(int *array, int n)
{
    if (n == 1) {
        return gcd(array[0], array[1]);
    }

    return gcd(array[n], multi_gcd(array, n - 1));
}

int main(void)
{
    const int N = 6;
    int array[] = { 98, 140, 84, 28, 42, 126 };

    printf("GCD of array: %d\n", multi_gcd(array, N - 1));

    return EXIT_SUCCESS;
}
