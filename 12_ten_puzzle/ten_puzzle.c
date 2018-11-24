#include <stdio.h>
#include <stdlib.h>

// 4 numbers
char numbers[5];
// RPN formula: 4 numbers + 3 operators + '\0'
char formula[4 + 3 + 1];

// fraction
// to avoid comuplational errors, denominator and numerator is saved individually
// until result is output
typedef struct {
    int denom; // denominator
    int numer; // numerator
} Fraction;

// stack info
#define N 10
Fraction stack[N];
int stack_top = 0;

void push(Fraction *value)
{
    if (stack_top != N) {
        stack[stack_top].denom = value->denom;
        stack[stack_top].numer = value->numer;
        stack_top++;
    } else {
        printf("stack over flow\n");
        exit(EXIT_FAILURE);
    }
}

void pop(Fraction *ret)
{
    stack_top--;
    if (stack_top >= 0) {
        ret->denom = stack[stack_top].denom;
        ret->numer = stack[stack_top].numer;
        return;
    } else {
        printf("stack under flow\n");
        exit(EXIT_FAILURE);
    }
}

// parse operator and calculate with 2 operand
void calc(const char op, Fraction *st1, Fraction *st2)
{
    switch (op) {
        case '+':
            st2->numer = st2->numer * st1->denom + st1->numer * st2->denom;
            st2->denom = st1->denom * st2->denom;
            break;
        case '-':
            st2->numer = st2->numer * st1->denom - st1->numer * st2->denom;
            st2->denom = st1->denom * st2->denom;
            break;
        case '*':
            st2->numer = st2->numer * st1->numer;
            st2->denom = st1->denom * st2->denom;
            break;
        case '/':
            // convert division to multiplication
            st2->numer = st2->numer * st1->denom;
            st2->denom = st2->denom * st1->numer;
            // zero division error
            if (st2->denom == 0) {
                printf("error: divide by zero\n");
                exit(EXIT_FAILURE);
            }
            break;
        default:
            printf("error: invalid character was input\n");
            exit(EXIT_FAILURE);
            break;
    }

    // push result to stack
    push(st2);
}

int solve(void)
{
    int c;
    Fraction st1, st2;

    c = 0;
    while (formula[c] != '\0') {
        // push integer as operand
        if (formula[c] >= '0' && formula[c] <= '9') {
            st1.denom = 1;  // integer
            st1.numer = formula[c] - '0';
            push(&st1);
        // parse and calculate +, -, *, /
        } else {
            pop(&st1);
            pop(&st2);
            calc(formula[c], &st1, &st2);
        }
        c++;
    }

    pop(&st1);

    if (st1.numer * 10 == st1.denom) {
        return 1;
    }

    return 0;
}

// make RPN formula
// num: num of numbers, op: num of operators
int make_rpn(int num, int op)
{
    // using flag of each number
    static int issued[4] = { 0, 0, 0, 0 };
    int i;

    // finish create formula
    if (num + op == 7) {
        formula[7] = '\0';
        //printf("%s\n", formula);
        if (solve()) {
            return 1;
        }
        return 0;
    } else {
        // if num of numbers are 2 more than operaters, operator can be added
        if (num - op >= 2) {
            // add operator
            formula[num + op] = '+';
            if (make_rpn(num, op + 1)) {
                return 1;
            }
            formula[num + op] = '-';
            if (make_rpn(num, op + 1)) {
                return 1;
            }
            formula[num + op] = '*';
            if (make_rpn(num, op + 1)) {
                return 1;
            }
            formula[num + op] = '/';
            if (make_rpn(num, op + 1)) {
                return 1;
            }
        }
        // if num of numbers are less than 3, number can be added
        if (num <= 3) {
            for (i = 0; i < 4; i++) {
                if (issued[i] == 0) {
                    // add number
                    issued[i] = 1;
                    formula[num + op] = numbers[i];
                    if (make_rpn(num + 1, op)) {
                        issued[i] = 0;
                        return 1;
                    }
                    issued[i] = 0;
                }
            }
        }
    }

    return 0;
}

void make_num(int digit, int num)
{
    int i;
    if (digit == 4) {
        numbers[4] = '\0';
        if (make_rpn(0, 0)) {
            printf("%s: %s\n", numbers, formula);
        } else {
            printf("%s: cannot solve\n", numbers);
        }
        return;
    }

    for (i = num; i <= 9; i++) {
        numbers[digit] = i + '0';
        make_num(digit + 1, i);
    }
}

int main(void)
{
    make_num(0, 0);

    return EXIT_SUCCESS;
}