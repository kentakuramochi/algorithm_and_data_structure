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

    // search and remove node
    do {
        printf("search integer (0: quit) > ");
        scanf("%d", &buf);

        // linear search
        if (buf) {
            for (thisNode = firstNode; thisNode != NULL;
                    thisNode = thisNode->next) {
                if (thisNode->data == buf) {
                    printf("*** found ***\n");

                    // remove the node to switch next pointer
                    printf("remove %d\n", buf);
                    if (thisNode->prev != NULL) {
                        thisNode->prev->next = thisNode->next;
                    // first node
                    } else {
                        firstNode = thisNode->next;
                    }

                    // if this node isn't last, switch prev pointer
                    if (thisNode->next != NULL) {
                        thisNode->next->prev = thisNode->prev;
                    }

                    free(thisNode);
                    break;
                }
            }

            if (thisNode == NULL) {
                printf("*** not found ***\n");
            }
        }
    } while (buf != 0);

    // remove all residual nodes
    for (thisNode = firstNode; thisNode != NULL;) {
        removeNode = thisNode;
        thisNode = thisNode->next;
        free(removeNode);
    }

    return 0;
}
