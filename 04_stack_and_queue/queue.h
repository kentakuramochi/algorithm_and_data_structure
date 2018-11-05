#ifndef _QUEUE_H_
#define _QUEUE_H_

// queue
typedef struct {
    double *vals;
    int first;
    int last;
    int max;
} queue;

void queue_init(queue *q, int length);

int queue_enqueue(queue *q, double val);

double queue_dequeue(queue *q);

void queue_free(queue *s);

#endif
