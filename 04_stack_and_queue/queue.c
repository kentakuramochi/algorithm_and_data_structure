#include <stdlib.h>
#include "queue.h"

#define QUEUE_ERROR 0
#define QUEUE_EMPTY -1

void queue_init(queue *q, int length)
{
    if (q->vals != NULL) {
        free(q->vals);
    }

    q->vals = (double*)malloc(sizeof(double) * length);
    q->first = 0;
    q->last = 0;
    q->max = length;
}

// enqueue
int queue_enqueue(queue *q, double val)
{
    // queue is full
    if ((q->last + 1) % q->max == q->first) {
        return QUEUE_ERROR;
    } else {
        // implemented by ring buffer
        q->vals[q->last] = val;
        q->last = (q->last) % q->max;
    }

    return 1;
}

// dequeue
double queue_dequeue(queue *q)
{
    double ret;

    // queue is empty
    if (q->first == q->last) {
        return QUEUE_EMPTY;
    } else {
        ret = q->vals[q->first];
        q->first = (q->first + 1) % q->max;
        return ret;
    }
}

void queue_free(queue *q)
{
    if (q->vals != NULL) {
        free(q->vals);
    }
}
