#include <stdio.h>
#include <stdlib.h>

// previous patterns and queue
typedef struct tagPattern {
    unsigned long hash;  // hash value
    int pattern_from;    // pattern
} Pattern;

Pattern *history;

// current numbers of patterns
int history_count = 0;
int queue_bottom;

// make hash corresponding to pattern
// pattern[i]: 0(0x00) ~ 7(0x07)
// gather 4bit number*8 with 32(+4)bit integer
// pattern[0]  [1]  [2]  [3]  [4]  [5]  [6]  [7]
// hash = 0000|0000|0000|0000|0000|0000|0000|0000
unsigned long make_hash(char *pattern)
{
    unsigned long hash;
    int i;

    hash = 0;
    for (i = 0; i < 8; i++) {
        hash |= ((unsigned long)(pattern[7 - i])) << (i * 4);
    }

    return hash;
}

// retrieve pattern from hash
// divide hash into 4bit block 0(0x00) ~ 7(0x07)
void pattern_from_hash(char *pattern, unsigned long hash)
{
    int i;
    for (i = 0; i < 8; i++) {
        pattern[7 - i] = (char)((hash >> (i * 4)) & 0xf);
    }
}

// save pattern history
void save_history(char *pattern, int pattern_from)
{
    int i;
    unsigned long hash;

    // create new hash
    hash = make_hash(pattern);

    // compare with prevous hashes
    for (i = 0; i < history_count; i++) {
        // if matched, don't save
        if (history[i].hash == hash) {
            return;
        }
    }

    // append new pattern to history
    history_count++;
    history = (Pattern*)realloc(history, sizeof(Pattern) * (history_count));

    if (history == NULL) {
        printf("memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    history[history_count - 1].hash = hash;
    history[history_count - 1].pattern_from = pattern_from;
}

// solve 7-puzzles
// breadth-first search
int solve_7puzzle(void)
{
    // a position of blank panel
    int blank_pos;
    unsigned long hash;
    // panels
    // index represent position as follows
    // 0 1 2 3
    // 4 5 6 7
    char pattern[8];

    queue_bottom = 0;

    // breadth-first search
    // search all patterns can be considered at next 1 turn
    // until all pattern was checked
    while (queue_bottom != history_count) {
        // get from queue
        hash = history[queue_bottom].hash;

        // panels line correctly
        if (hash == 0x12345670) {
            return 1;
        }

        pattern_from_hash(pattern, hash);
        // get blank position
        for (blank_pos = 0; blank_pos < 8; blank_pos++) {
            if (pattern[blank_pos] == 0) {
                break;
            }
        }

        // panel index:
        // 0 1 2 3
        // 4 5 6 7
        // move up: index-4
        // move down: index+4
        // move left: index-1
        // move right: index+1
        if (blank_pos > 3) {
            // move panel from upper
            pattern[blank_pos] = pattern[blank_pos - 4];
            pattern[blank_pos - 4] = 0;
            save_history(pattern, queue_bottom);
            // recovery pattern
            pattern_from_hash(pattern, hash);
        }
        if (blank_pos < 4) {
            // move panel from lower
            pattern[blank_pos] = pattern[blank_pos + 4];
            pattern[blank_pos + 4] = 0;
            save_history(pattern, queue_bottom);
            // recovery pattern
            pattern_from_hash(pattern, hash);
        }
        if ((blank_pos != 0) && (blank_pos != 4)) {
            // move panel from left
            pattern[blank_pos] = pattern[blank_pos - 1];
            pattern[blank_pos - 1] = 0;
            save_history(pattern, queue_bottom);
            // recovery pattern
            pattern_from_hash(pattern, hash);
        }
        if ((blank_pos != 3) && (blank_pos != 7)) {
            // move panel from right
            pattern[blank_pos] = pattern[blank_pos + 1];
            pattern[blank_pos + 1] = 0;
            save_history(pattern, queue_bottom);
        }
        queue_bottom++;
    }

    // the answer was not found
    return 0;
}

int main(void)
{
    int last, i;

    // initial pattern
    char pattern[8] = { 2, 7, 1, 4, 5, 0, 3, 6 };

    history = NULL;

    save_history(pattern, -1);

    if (solve_7puzzle() == 0) {
        printf("the anser was not found\n");
    } else {
        last = -1;

        while (last != queue_bottom) {
            // display answer from first
            for (i = queue_bottom; history[i].pattern_from != last;) {
                i = history[i].pattern_from;
            }
            last = i;

            // print panel
            printf("pattern: %d\n", last);
            pattern_from_hash(pattern, history[last].hash);
            for (i = 0; i < 8; i++) {
                printf("%c ", (pattern[i] ? (pattern[i] + '0') : ' '));
                if (i % 4 == 3) {
                    printf("\n");
                }
            }
            // wait
            getchar();
        }
    }

    free(history);

    return EXIT_SUCCESS;
}