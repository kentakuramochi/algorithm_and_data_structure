#include <stdio.h>
#include <stdlib.h>

// num, size, value of items
#define N 5
int size[N] = { 2, 3, 5, 7, 9 };
int value[N] = { 2, 4, 7, 10, 14 };

// napzack size
#define NAP_SIZE 10

int main(void)
{
    // current value of napzack
    int nap_value[NAP_SIZE + 1] = { 0 };

    int i, j, new_value;

    printf("a size of napzack: ");
    for (i = 1; i < NAP_SIZE + 1; i++) {
        printf("%2d ", i);
    }
    printf("\n\n");

    // extend type of using item
    for (i = 0; i < N; i++) {
        // pack item[i] into napzack which size is j
        for (j = size[i]; j < NAP_SIZE + 1; j++) {
            new_value = nap_value[j - size[i]] + value[i];

            // if the value is higher, pack item[i]
            if (new_value > nap_value[j]) {
                nap_value[j] = new_value;
            }
        }

        printf("   use item 1 ~ %d: ", i + 1);
        for (j = 1; j < NAP_SIZE + 1; j++) {
            printf("%2d ", nap_value[j]);
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}