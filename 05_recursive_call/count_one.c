#include <stdio.h>
#include <stdlib.h>

#ifndef RECURSIVE
// count '1' with loop
int num_of_one(int value)
{
    int ret;

    for (ret = 0; value > 0; value /= 10) {
        if (value % 10 == 1) {
            ret++;
        }
    }

    return ret;
}
#else
// count '1' with recursion
int num_of_one(int value)
{
    int ret;

    if (value == 0) {
        return 0;
    }

    return ((value %10 == 1) ? 1 : 0) + num_of_one(value / 10);
}
#endif

int main(void)
{
    int i;
    printf("Input number > ");
    scanf("%d", &i);

    printf("num of '1': %d\n", num_of_one(i));

    return EXIT_SUCCESS;
}
