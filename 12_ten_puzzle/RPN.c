#include <stdio.h>
#include <stdlib.h>

#define N 10

// fraction
// to avoid comuplational errors, denominator and numerator is saved separately
// until output result
typedef struct {
    int denom; // denominator
    int numer; // numerator
} Fraction;

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
int main(void)
{
    char line[256];
    int c;
    Fraction st1, st2;

    printf("input formula in RPN: ");
    scanf("%s", line);

    c = 0;
    while (line[c] != '\0') {
        if (line[c] >= '0' && line[c] <= '9') {
            st1.denom = 1;
            st1.numer = line[c] - '0';
            push(&st1);
        } else {
            pop(&st1);
            pop(&st2);

            if (line[c] == '+') {
                st2.numer = st2.numer * st1.denom + st1.numer * st2.denom;
                st2.denom = st1.denom * st2.denom;
                push(&st2);
            } else if (line[c] == '-') {
                st2.numer = st2.numer * st1.denom - st1.numer * st2.denom;
                st2.denom = st1.denom * st2.denom;
                push(&st2);
            } else if (line[c] == '*') {
                st2.numer = st2.numer * st1.numer;
                st2.denom = st1.denom * st2.denom;
                push(&st2);
            } else if (line[c] == '/') {
                st2.numer = st2.numer * st1.denom;
                st2.denom = st2.denom * st1.numer;
                if (st2.denom == 0) {
                    printf("error: divide by zero\n");
                    exit(EXIT_FAILURE);
                }
                push(&st2);
            } else {
                printf("error: invalid character was input\n");
                exit(EXIT_FAILURE);
            }
        }
        c++;
    }

    pop(&st1);
    if (stack_top != 0) {
        printf("error: invalid formula, too much numbers\n");
        exit(EXIT_FAILURE);
    }

    printf("answer: %f\n", (double)st1.numer / (double)st1.denom);

    return EXIT_SUCCESS;
}