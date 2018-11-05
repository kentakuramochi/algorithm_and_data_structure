#include <stdio.h>
#include <stdlib.h>

// singly linked list
typedef struct tagListNode {
    struct tagListNode *next;
    int data;
} ListNode;

int main(void)
{
    ListNode *firstNode, *lastNode, *newNode, *thisNode;

    firstNode = lastNode = NULL;

    int buf;
    do {
        printf("input integer (0: quit) > ");
        scanf("%d", &buf);

        // append node to list
        if (buf) {
            newNode = (ListNode*)malloc(sizeof(ListNode));
            newNode->data = buf;
            newNode->next = NULL;

            if (lastNode != NULL) {
                lastNode->next = newNode;
                lastNode = newNode;
            // first node
            } else {
                firstNode = lastNode = newNode;
            }
        }
    } while (buf != 0);

    ListNode *tmp;
    do {
        printf("now: ");
        for (thisNode = firstNode; thisNode != NULL;
            thisNode = thisNode->next) {
            printf("%d ", thisNode->data);
        }

        printf("\nsearch integer (0: quit) > ");
        scanf("%d", &buf);

        // linear search
        if (buf) {
            for (thisNode = firstNode; thisNode != NULL;
                    tmp = thisNode, thisNode = thisNode->next) {

                if (thisNode->data == buf) {
                    printf("*** found ***\n");

                    // move the node to head
                    if (thisNode != firstNode) {
                        tmp->next = thisNode->next;

                        if (thisNode == lastNode) {
                            lastNode = tmp;
                        }

                        thisNode->next = firstNode;
                        firstNode = thisNode;
                    }
                    break;
                }
            }

            if (thisNode == NULL) {
                printf("*** not found ***\n");
            }
        }
    } while (buf != 0);

    // remove all nodes
    for (thisNode = firstNode; thisNode != NULL;) {
        tmp = thisNode;
        thisNode = thisNode->next;
        free(tmp);
    }

    return 0;
}
