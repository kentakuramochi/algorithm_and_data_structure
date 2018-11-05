#include <stdio.h>
#include <stdlib.h>

#define STACK_LENGTH 100

// stack by array
double stack[STACK_LENGTH];
// stack offset
int stack_top = 0;

void push(double val)
{
    if (stack_top == STACK_LENGTH) {
        printf("stack overflow\n");
        exit(EXIT_FAILURE);
    } else {
        stack[stack_top++] = val;
    }
}

double pop(void)
{
    if (stack_top == 0) {
        printf("stack underflow\n");
        exit(EXIT_FAILURE);
        return 0;
    } else {
        return stack[--stack_top];
    }
}

int main(void)
{
    char buffer[256];

    do {
        printf("current stack (%d):", stack_top);

        for (int i = 0; i < stack_top; i++) {
            printf("%0.3f ", stack[i]);
        }

        printf("\n> ");
        fgets(buffer, 256, stdin);

        double cal1, cal2;
        switch (buffer[0]) {
            // operator: calculate 2 numbers
            case '+':
                cal1 = pop();
                cal2 = pop();
                push(cal2 + cal1);
                break;
            case '-':
                cal1 = pop();
                cal2 = pop();
                push(cal2 - cal1);
                break;
            case '*':
                cal1 = pop();
                cal2 = pop();
                push(cal2 * cal1);
                break;
            case '/':
                cal1 = pop();
                cal2 = pop();
                push(cal2 / cal1);
                break;
            case '=':
                break;
            default:
                // push number to stack
                push(atoi(buffer));
                break;
        }
    // finish with '='
    } while (buffer[0] != '=');

    printf("result = %f\n", pop());

    if (stack_top != 0) {
        printf("number is left on stack\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
