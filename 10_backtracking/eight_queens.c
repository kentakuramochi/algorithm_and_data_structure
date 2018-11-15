#include <stdio.h>
#include <stdlib.h>

// chess board
int board[8][8];

// check queen can be put on (x, y)
// 1: OK 0: NG
int check(int x, int y)
{
    int p, q;

    // put queen sequentially from left, so there is no queen on right
    // check left
    for (p = 0; p < x; p++) {
        if (board[p][y] == 1) {
            return 0;
        }
    }

    // check upper left
    p = x; q = y;
    while ((p > 0) && (q > 0)) {
        if (board[--p][--q] == 1) {
            return 0;
        }
    }

    // check lower left
    p = x; q = y;
    while ((p > 0) && (q < 7)) {
        if (board[--p][++q] == 1) {
            return 0;
        }
    }

    return 1;
}

void showboard(void)
{
    int x, y;
    for (y = 0; y < 8; y++) {
        for (x = 0; x < 8; x++) {
            printf("%c ", board[x][y] ? 'Q' : '.');
        }
        printf("\n");
    }
}

// solve 8-queens
// backtraking (depth-first search)
int solve(int x)
{
    int i;

    // finish putting 8 queens
    if (x == 8) {
        return 1;
    }

    // backtracking
    for (i = 0; i < 8; i++) {
        // check right (row first)
        if (check(x, i)) {
            board[x][i] = 1;

            if (solve(x + 1)) {
                return 1;
            } else {
                board[x][i] = 0;
            }
        }
    }

    return 0;
}

int main(void)
{
    // start with first row
    if (solve(0)) {
        showboard();
    }

    return EXIT_SUCCESS;
}
