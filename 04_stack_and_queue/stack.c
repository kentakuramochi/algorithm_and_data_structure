#include <stdlib.h>
#include "stack.h"

#define STACK_ERROR 0

void stack_init(stack *s, int length)
{
    if (s->vals != NULL) {
        free(s->vals);
    }

    s->vals = (double*)malloc(sizeof(double) * length);
    s->top = 0;
    s->max = length;
}

int stack_push(double val, stack *s)
{
    if (s->top == s->max) {
        return STACK_ERROR;
    } else {
        s->vals[s->top] = val;
        s->top++;
    }

    return 1;
}

double stack_pop(stack *s)
{
    if (s->top == 0) {
        return STACK_ERROR;
    } else {
        s->top--;
        return s->vals[s->top];
    }
}

void stack_free(stack *s)
{
    if (s->vals != NULL) {
        free(s->vals);
    }
}
