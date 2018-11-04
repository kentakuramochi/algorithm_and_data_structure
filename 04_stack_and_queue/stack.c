#include <stdlib.h>
#include "stack.h"

#define STACK_ERROR -1

void stack_init(stack *s, int length)
{
    if (s->vals != NULL) {
        free(s->vals);
    }

    s->vals = (double*)malloc(sizeof(double) * length);
    s->top = 0;
    s->max = length;
}

void stack_push(double val, stack *s)
{
    if (s->top == s->max) {
        return;
    } else {
        s->vals[s->top] = val;
        s->top++;
    }
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
