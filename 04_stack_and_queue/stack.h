#ifndef _STACK_H_
#define _STACK_H_

// stack
typedef struct {
    double *vals;
    int top;
    int max;
} stack;

void stack_init(stack *s, int length);

int stack_push(stack *s, double val);

double stack_pop(stack *s);

void stack_free(stack *s);

#endif
