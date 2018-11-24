#include <stdio.h>
#include <stdlib.h>

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

int main(void)
{
    char line[256];
    int c;
    Fraction st1, st2;

    printf("input formula in RPN: ");
    scanf("%s", line);

    c = 0;
    while (line[c] != '\0') {
        // push integer as operand
        if (line[c] >= '0' && line[c] <= '9') {
            st1.denom = 1;  // integer
            st1.numer = line[c] - '0';
            push(&st1);
        // parse and calculate +, -, *, /
        } else {
            pop(&st1);
            pop(&st2);
            calc(line[c], &st1, &st2);
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