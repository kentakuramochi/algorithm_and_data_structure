#include <stdio.h>
#include <stdlib.h>

// queue size + 1: for check capacity
#define QUEUE_MAX (5 + 1)
#define QUEUE_EMPTY -1

// queue by array
int queue[QUEUE_MAX];
int queue_first = 0;
int queue_last = 0;

// enqueue
void enqueue(int val)
{
    if ((queue_last + 1) % QUEUE_MAX == queue_first) {
        printf("job is full\n");
    } else {
        queue[queue_last] = val;
        queue_last = (queue_last + 1) % QUEUE_MAX;
    }
}

// dequeue
int dequeue(void)
{
    int ret;

    if (queue_first == queue_last) {
        return QUEUE_EMPTY;
    } else {
        ret = queue[queue_first];
        queue_first = (queue_first + 1) % QUEUE_MAX;
        return ret;
    }
}

void queue_print(void)
{
    int i;
    for (int i = queue_first; i != queue_last; i = (i + 1) % QUEUE_MAX) {
        printf("%d ", queue[i]);
    }
}

int main(void)
{
    int i, j;

    do {
        printf("current queue: ");
        queue_print();

        printf("\ncommmand 0:quit 1:store job 2:exec job\n> ");
        scanf("%d", &i);

        switch (i) {
            case 1:
                printf("input job's unique number (1~1000) > ");
                scanf("%d", &j);
                if ((j >= 1) && (j <= 1000)) {
                    enqueue(j);
                }
                break;
            case 2:
                j = dequeue();

                // check queue
                if (j == QUEUE_EMPTY) {
                    printf("no jobs\n");
                } else {
                    printf("running job[%d] ...\n", j);
                }
                break;
            default:
                break;
        }
    } while (i != 0);

    return EXIT_SUCCESS;
}
