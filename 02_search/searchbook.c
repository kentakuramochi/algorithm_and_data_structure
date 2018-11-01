#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *title;
    char *author;
    int id;
    int available;
} Book;

void initBooks(Book *books, int n)
{
    for (int i = 0; i < n; i++) {
        books[i] = (Book*)malloc(sizeof(Book));
    }
}

void freeBooks(Book *books, int n)
{
    for (int i = 0; i < n; i++) {
        if (books[i] != NULL) {
            free(books[i]);
        }
    }
}

void sortBooks(Book *books, int bottom, int top)
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
            Book tmp = books[lower];
            books[lower] = books[upper];
            books[upper] = tmp;
            lower++;
            upper--;
        }
    }

    sortBooks(bottom, upper);
    sortBooks(upper + 1, top);
}

int searchBook(Book *books, int size, int key)
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

    return -1;
}

int main()
{
    int key, position;

    const int N = 3;
    Book books[N];

    initBooks(books, N);

    sortBooks(books, 0, N - 1);

    while (1) {
        printf("input id (0: end)\n");

        scanf("%d", &key);

        if (key == 0) {
            break;
        }

        position = searchBook(books, N - 1, key);

        if (position != -1) {
            printf("the book was found\n
                    title: %s\n
                    autthor: %s\n
                    id: %d\n",
                    books[position]->title,
                    books[position]->author,
                    books[position]->id);
            if (books[position]->available != 0) {
                prinf("you can lent it\n");
            } else {
                printf("it is lented out\n");
            }
        } else {
            printf("the book was not found\n");
        }
    }

    freeBooks(books);

    return 0;
}
