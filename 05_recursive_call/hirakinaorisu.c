#include <stdio.h>
#include <stdlib.h>

// n^n (n=1,2,..,9)
unsigned long power[10] = { 0 };

// the number of '9','8','7',...'1' which specified number contains
int number_using[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

// get a number of specified digit
int NumOfDigit(unsigned long number, unsigned long digit)
{
    int ret = 0;

    if (number == 0) {
        return 0;
    }

    if (number % 10 == digit) {
        ret = 1;
    }

    ret += NumOfDigit(number / 10, digit);

    return ret;
}

// search and print ”hirakinaori-su" (開き直り数)
// ex) "3435"
// 3435 = 3^3 + 4^4 + 3^3 + 5^5
void CheckNumber(void)
{
    unsigned long result = 0;

    // sum powers of each digit
    for (int i = 1; i <= 9; i++) {
        result += power[i] * number_using[i];
    }

    // check whether all digits are equal or not
    for (int i = 1; i <= 9; i++) {
        if (NumOfDigit(result, i) != number_using[i]) {
            return;
        }
    }

    printf("%lu \n", result);
    return;
}

// make and check number
void MakeNumbers(int start, int kosuu)
{
    // hirakinaori-su is less than 10-digit
    if (kosuu > 10) {
        return;
    }

    for (int i = start; i <= 9; i++) {
        // create new number
        number_using[i]++;
        // check the number
        CheckNumber();
        MakeNumbers(i, kosuu + 1);
        // delete
        number_using[i]--;
    }
}

int main(void)
{
    unsigned long i, j, k;

    // calculate n^n (n=1 to 9)
    for (i = 1; i <= 9; i++) {
        k = 1;
        for (j = 0; j < i; j++) {
            k *= i;
        }
        power[i] = k;
    }

    MakeNumbers(1, 1);

    return EXIT_SUCCESS;
}
