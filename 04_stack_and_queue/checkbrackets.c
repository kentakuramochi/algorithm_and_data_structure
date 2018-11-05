#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_LENGTH 4096

// type of bracket
#define BRACKET_SMALL  1
#define BRACKET_MEDIUM 2
#define BRACKET_LARGE  3

// bracket struct
typedef struct _tagbracket {
    int line;   // line of sentence
    int column; // column of sentence
    int type;   // type of bracket
    // list
    struct _tagbracket *next;
    struct _tagbracket *prev;
} bracket;

bracket *head = NULL;
bracket *last = NULL;

// push to stack
void push(int line, int column, int type)
{
    bracket *new = (bracket*)malloc(sizeof(bracket));

    if (new == NULL) {
        printf("memory allocation error\n");
        exit(EXIT_FAILURE);
        return;
    }

    new->line = line;
    new->column = column;
    new->type = type;

    new->next = NULL;
    new->prev = last;
    last = new;
    if (head == NULL) {
        head = new;
    }
}

// pop from stack
int pop(bracket *ret)
{
    // stack is empty
    if (head == NULL) {
        return 0;
    }

    ret->line = last->line;
    ret->column = last->column;
    ret->type = last->type;
    ret->next = ret->prev = NULL;

    // remove from list
    bracket *tmp = last;
    if (last->prev == NULL) {
        head = NULL;
    } else {
        last->prev->next = NULL;
    }
    last = last->prev;
    free(tmp);

    return 1;
}

// check brackets
int check_bracket(int type, int line, int carryover)
{
    bracket open;

    if (pop(&open) == 0) {
        printf("no open bracket: col %d, row %d\n", line, carryover);
        return 0;
    }
    if (open.type != type) {
        printf("bracket doesn't match: col %d, row %d and col %d, row %d\n", open.line, open.column, line, carryover);
        return 0;
    }

    return 1;
}

int main()
{
    // stack
    char buffer[STACK_LENGTH];
    int line = 1, carryover = 0;

    for (;;) {
        // read till end
        if (fgets(buffer, STACK_LENGTH, stdin) == NULL) {
            break;
        }

        int len = strlen(buffer);
        if (len == 0) {
            continue;
        }

        for (int i = 0; i < len; i++) {
            switch (buffer[i]) {
                case '(':
                    push(line, carryover + i + 1, BRACKET_SMALL);
                    break;
                case '{':
                    push(line, carryover + i + 1, BRACKET_MEDIUM);
                    break;
                case '[':
                    push(line, carryover + i + 1, BRACKET_LARGE);
                    break;
                case ')':
                    if (check_bracket(BRACKET_SMALL, line, carryover + i + 1) == 0) {
                        return EXIT_FAILURE;
                    }
                    break;
                case '}':
                    if (check_bracket(BRACKET_MEDIUM, line, carryover + i + 1) == 0){
                        return EXIT_FAILURE;
                    }
                    break;
                case ']':
                    if (check_bracket(BRACKET_LARGE, line, carryover + i + 1) == 0){
                        return EXIT_FAILURE;
                    }
                    break;
                default:
                    break;
            }
        }

        if (buffer[len - 1] == '\n') {
            carryover = 0;
            line++;
        } else {
            // if there is no LF while reading STACK_LENGTH chars
            carryover += len;
        }
    }

    if (head != NULL) {
        printf("too much close bracket\n");
        return EXIT_FAILURE;
    }

    printf("bracket matchs\n");

    return EXIT_SUCCESS;
}
