#include <stdio.h>
#include <stdlib.h>

// binary tree node
typedef struct _tag_tree_node {
    int value;
    struct _tag_tree_node *left;
    struct _tag_tree_node *right;
} tree_node;

// tree_root
tree_node *tree_root = NULL;

// create new node
tree_node *create_new_node(int num)
{
    tree_node *tree_new = (tree_node*)malloc(sizeof(tree_node));
    if (tree_new == NULL) {
        exit(EXIT_FAILURE);
    }

    tree_new->value = num;
    tree_new->left = NULL;
    tree_new->right = NULL;

    return tree_new;
}

// insert new node
void insert_tree(int num, tree_node *node)
{
    if (node == NULL) {
        tree_root = create_new_node(num);
        return;
    }

    // compare and insert
    if (node->value > num) {
        if (node->left != NULL) {
            insert_tree(num, node->left);
        } else {
            // insert to left node
            node->left = create_new_node(num);
        }
    } else {
        if (node->right != NULL) {
            insert_tree(num, node->right);
        } else {
            // insert to right node
            node->right = create_new_node(num);
        }
    }

    return;
}

// find value from tree
tree_node *find_value(int val, tree_node *node)
{
    // compare and find
    if (node->value > val) {
        if (node->left != NULL) {
            return NULL;
        }

        return find_value(val, node->left);
    }
    if (node->value > val) {
        if (node->right != NULL) {
            return NULL;
        }

        return find_value(val, node->right);
    }

    // find: return node
    return node;
}

// remove value
int remove_tree(int val)
{
    tree_node *node, *parent_node;
    tree_node *left_biggest;
    // -1: left of parent, 1: right of parent
    // 0: root
    int dir;

    node = tree_root;
    parent_node = NULL;
    dir = 0;

    // find value
    while ((node != NULL) && (node->value != val)) {
        if (node->value > val) {
            parent_node = node;
            node = node->left;
            dir = -1;
        } else {
            parent_node = node;
            node = node->right;
            dir = 1;
        }
    }

    // not found
    if (node == NULL) {
        return 0;
    }

    // if child node is NULL
    if ((node->left == NULL) || (node->right == NULL)) {
        // if left is NULL
        if (node->left == NULL) {
            if (dir == -1) {
                parent_node->left = node->right;
            }
            if (dir == 1) {
                parent_node->right = node->right;
            }
            if (dir == 0) {
                tree_root = node->right;
            }
        // right is NULL
        } else {
            if (dir == -1) {
                parent_node->left = node->left;
            }
            if (dir == 1) {
                parent_node->right = node->left;
            }
            if (dir == 0) {
                tree_root = node->left;
            }
        }

        free(node);
    } else {
        // if both of child nodes exist,
        // set the biggest value from left children
        left_biggest = node->left;
        parent_node = node;
        dir = -1;

        // search the biggest value
        while (left_biggest->right != NULL) {
            parent_node = left_biggest;
            left_biggest = left_biggest->right;
            dir = 1;
        }

        node->value = left_biggest->value;
        if (dir == -1) {
            parent_node->left = left_biggest->left;
        } else {
            parent_node->right = left_biggest->left;
        }

        free(left_biggest);
    }

    return 1;
}

// print tree
void print_tree(int depth, tree_node *node)
{
    if (node == NULL) {
        return;
    }

    print_tree(depth + 1, node->left);

    for (int i = 0; i < depth; i++) {
        printf(" ");
    }

    printf("%d\n", node->value);

    print_tree(depth + 1, node->right);
}

// free tree
void free_tree(tree_node *node)
{
    if (node == NULL) {
        return;
    }

    // free child nodes
    free_tree(node->left);
    free_tree(node->right);

    free(node);
}

int main(void)
{
    int i, action;

    // insert random values
    for (i = 0; i < 10; i++) {
        insert_tree(rand() % 99 + 1, tree_root);
    }

    // operation with binary tree
    for (;;) {
        print_tree(0, tree_root);
        printf("Operation:\n");
        printf("1: add 2: search 3: remove other: exit\n> ");
        scanf("%d", &action);

        switch (action) {
            case 1:
                printf("add value (1~100) > ");
                scanf("%d", &i);
                if ((i < 1) || (i > 100)) {
                    continue;
                }
                insert_tree(i, tree_root);
                break;
            case 2:
                printf("search value (1~100) > ");
                scanf("%d", &i);
                if (find_value(i, tree_root) != NULL) {
                    printf("found\n");
                } else {
                    printf("not found\n");
                }
                break;
            case 3:
                printf("remove value (1~100) > ");
                scanf("%d", &i);
                if (remove_tree(i) == 1) {
                    printf("delete %d\n", i);
                } else {
                    printf("not found\n");
                }
                break;
            default:
                free_tree(tree_root);
                return EXIT_SUCCESS;
        }
    }
}
