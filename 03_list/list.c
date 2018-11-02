#include <stdio.h>
#include <stdlib.h>

// node of list structure
typedef struct tagListNode {
    struct tagListNode *prev;
    struct tagListNode *next;
    int data;
} ListNode;

int main()
{
    ListNode *firstNode, *lastNode, *newNode,
             *thisNode, *removeNode;

    firstNode = lastNode = NULL;

    int buf;
    do {
        printf("input integer (0: quit) > ");
        scanf("%d", &buf);

        // append node to list
        if (buf) {
            // allocate new node
            newNode = (ListNode*)malloc(sizeof(ListNode));
            newNode->data = buf;
            newNode->next = NULL;

            if (lastNode != NULL) {
                lastNode->next = newNode;
                newNode->prev = lastNode;
                lastNode = newNode;
            } else {
                // first node
                firstNode = lastNode = newNode;
                newNode->prev = NULL;
            }
        }
    // while 0 is inputed
    } while (buf != 0);


    // print and sum all nodes
    printf("numbers\n");
    int sum = 0;
    for (thisNode = firstNode; thisNode != NULL; thisNode = thisNode->next) {
        printf("%d\t", thisNode->data);
        sum += thisNode->data;
    }
    printf("\nsum=%d\n", sum);

    // remove all nodes
    for (thisNode = firstNode; thisNode != NULL;) {
        removeNode = thisNode;
        thisNode = thisNode->next;
        free(removeNode);
    }

    return 0;
}
