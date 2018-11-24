#include <stdio.h>
#include <stdlib.h>

// 4 numbers
char numbers[] = "1234";
// RPN formula: 4 numbers + 3 operators + '\0'
char formula[4 + 3 + 1];

// make RPN formula
// num: num of numbers, op: num of operators
void make_rpn(int num, int op)
{
    // using flag of each number
    static int issued[4] = { 0, 0, 0, 0 };
    int i;

    // finish create formula
    if (num + op == 7) {
        formula[7] = '\0';
        printf("%s\n", formula);
        return;
    } else {
        // if num of numbers are 2 more than operaters, operator can be added
        if (num - op >= 2) {
            // add operator
            formula[num + op] = '+';
            make_rpn(num, op + 1);
            formula[num + op] = '-';
            make_rpn(num, op + 1);
            formula[num + op] = '*';
            make_rpn(num, op + 1);
            formula[num + op] = '/';
            make_rpn(num, op + 1);
        }
        // if num of numbers are less than 3, number can be added
        if (num <= 3) {
            for (i = 0; i < 4; i++) {
                if (issued[i] == 0) {
                    // add number
                    issued[i] = 1;
                    formula[num + op] = numbers[i];
                    make_rpn(num + 1, op);
                    issued[i] = 0;
                }
            }
        }
    }
}

int main(void)
{
    make_rpn(0, 0);

    return EXIT_SUCCESS;
}