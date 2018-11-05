#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NOT_FOUND -1

// book information
typedef struct {
    char *title;
    char *author;
    int id;
    bool lending;
} Book;

void initBooks(Book *books[], int n)
{
    for (int i = 0; i < n; i++) {
        books[i] = (Book*)malloc(sizeof(Book));
    }
}

void freeBooks(Book *books[], int n)
{
    for (int i = 0; i < n; i++) {
        if (books[i] != NULL) {
            free(books[i]);
        }
    }
}

// register book information
void registerBook(Book *books[], int n,
        char *title, char* author, int id, bool lending)
{
    static int i = 0;

    books[i]->title = title;
    books[i]->author = author;
    books[i]->id = id;
    books[i]->lending = lending;

    i++;

    if (i == n) {
        n = 0;
    }
}

// sort book informations (quick sort) with its id
void sortBooks(Book *books[], int bottom, int top)
{
    int lower, upper;

    if (bottom >= top) {
        return;
    }

    int div = books[bottom]->id;

    for (lower = bottom, upper = top; lower < upper;) {
        while (books[lower]->id < div) {
            lower++;
        }
        while (books[upper]->id > div) {
            upper--;
        }

        if (lower < upper) {
            Book *tmp = books[lower];
            books[lower] = books[upper];
            books[upper] = tmp;
            lower++;
            upper--;
        }
    }

    sortBooks(books, bottom, upper);
    sortBooks(books, upper + 1, top);
}

// search book information (binary search) with its id
int searchBook(Book *books[], int size, int key)
{
    int left, mid, right;

    left = 0;
    right = size;
    while (left < right) {
        mid = (left + right) / 2;
        if (books[mid]->id < key) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    if (books[left]->id == key) {
        return left;
    }

    return NOT_FOUND;
}

int main(void)
{
    const int N = 10;
    Book *books[N];

    initBooks(books, N);

    // register books
    registerBook(books, N, "book0", "Alice", 1000, false);
    registerBook(books, N, "book1", "Bob", 502, true);
    registerBook(books, N, "book2", "Chris", 731, true);
    registerBook(books, N, "book3", "Dick", 628, false);
    registerBook(books, N, "book4", "Eliza", 1, false);

    // quick sort
    sortBooks(books, 0, N - 1);

    int key, position;

    // while key != -1
    while (true) {
        printf("***************\n");
        printf("* book search *\n");
        printf("***************\n");
        printf("input book id (-1: quit) > ");

        // input book id
        scanf("%d", &key);

        if (key == -1) {
            break;
        }

        // binary search
        position = searchBook(books, N - 1, key);

        if (position != NOT_FOUND) {
            printf("**** FOUND ****\n");
            printf("[title]:  %s\n", books[position]->title);
            printf("[author]: %s\n", books[position]->author);
            printf("[id]:     %d\n", books[position]->id);
            if (books[position]->lending == true) {
                printf("(On loan)\n");
            } else {
                printf("(free)\n");
            }
        } else {
            printf("** NOT FOUND **\n");
        }
    }

    freeBooks(books, N);

    return 0;
}
