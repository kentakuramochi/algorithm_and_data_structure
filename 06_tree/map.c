#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// binary tree node of string
typedef struct _tag_tree_node {
    char *key;
    char *val;
    struct _tag_tree_node *left;
    struct _tag_tree_node *right;
} tree_node;

// tree_root
tree_node *tree_root = NULL;

// create new node
tree_node *create_new_node(char* key, char* val)
{
    tree_node *tree_new = (tree_node*)malloc(sizeof(tree_node));
    if (tree_new == NULL) {
        exit(EXIT_FAILURE);
    }

    // allocate (strlen(key)+1) Byte for NULL termination
    tree_new->key = (char*)malloc(sizeof(char) * strlen(key) + 1);
    tree_new->val = (char*)malloc(sizeof(char) * strlen(val) + 1);
    if ((tree_new->key == NULL) || (tree_new->val == NULL)) {
        exit(EXIT_FAILURE);
    }
    strcpy(tree_new->key, key);
    strcpy(tree_new->val, val);

    tree_new->left = NULL;
    tree_new->right = NULL;

    return tree_new;
}

// insert new node
void insert_tree(char *key, char *val, tree_node *node)
{
    if (node == NULL) {
        tree_root = create_new_node(key, val);
        return;
    }

    // compare and insert
    if (strcmp(node->key, key) > 0) {
        if (node->left != NULL) {
            insert_tree(key, val, node->left);
        } else {
            // insert to left node
            node->left = create_new_node(key, val);
        }
    } else {
        if (node->right != NULL) {
            insert_tree(key, val, node->right);
        } else {
            // insert to right node
            node->right = create_new_node(key, val);
        }
    }

    return;
}

// find node with key
tree_node *find_key(char *key, tree_node *node)
{
    // compare and find
    int cmp = strcmp(node->key, key);

    if (cmp > 0) {
        if (node->left != NULL) {
            return NULL;
        }

        return find_key(key, node->left);
    }
    if (cmp < 0) {
        if (node->right != NULL) {
            return NULL;
        }

        return find_key(key, node->right);
    }

    // find: return node
    return node;
}

// remove value with key
int remove_tree(char *key)
{
    tree_node *node = tree_root, *parent_node = NULL;
    tree_node *left_biggest;
    // -1: left of parent, 1: right of parent
    // 0: root
    int dir = 0, cmp;

    // find value
    while ((node != NULL) &&
           ((cmp = strcmp(node->key, key))!=0)) {
        if (cmp > 0) {
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

        free(node->key);
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

        free(node->key);
        node->key = left_biggest->key;
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

    printf("%s:%s\n", node->key, node->val);

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

    free(node->key);
    free(node->val);
    free(node);
}

int main(void)
{
    int i;
    char tmp[256], tmpval[256];
    tree_node *node_found;

    // operation with binary tree map
    for (;;) {
        print_tree(0, tree_root);
        printf("Operation:\n");
        printf("0: exit 1: add 2: search 3: remove\n> ");
        scanf("%d", &i);

        if (i == 0) {
            break;
        }

        switch (i) {
            case 1:
                printf("key > ");
                scanf("%s", tmp);
                printf("val > ");
                scanf("%s", tmpval);

                insert_tree(tmp, tmpval, tree_root);
                break;
            case 2:
                printf("key > ");
                scanf("%s", tmp);

                node_found = find_key(tmp, tree_root);
                if (node_found != NULL) {
                    printf("found val:%s\n", node_found->val);
                } else {
                    printf("not found\n");
                }
                break;
            case 3:
                printf("key > ");
                scanf("%s", tmp);

                if (remove_tree(tmp) == 1) {
                    printf("delete %s\n", tmp);
                } else {
                    printf("not found\n");
                }
                break;
            default:
                break;
        }
    }

    free_tree(tree_root);

    return EXIT_SUCCESS;
}
