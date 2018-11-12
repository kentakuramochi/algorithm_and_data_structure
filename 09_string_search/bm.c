#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATTERN_LENGTH 4

unsigned char original_text[] =
    "On a dark desert highway, cool wind in my hair,";
unsigned char original_pattern[] = "wind";

// BM (Boyer-Moore) method
unsigned char *bm_search(unsigned char *text,
        unsigned char *pattern)
{
    // shift table
    // if a pattern is not match with character which ASCII code is i,
    // pattern shifts by (table[i]) characters
    int table[256];
    int text_index, pattern_index, text_len, i;

    // most characters: shift by length of pattern
    for (i = 0; i < 256; i++) {
        table[i] = PATTERN_LENGTH;
    }
    // characters in pattern: shift as same characters are same position
    for (i = 0; i < PATTERN_LENGTH; i++) {
        table[pattern[i]] = PATTERN_LENGTH - i - 1;
    }

    // get text length
    for (text_len = 0; text[text_len] != '\0'; ++text_len);

    text_index = PATTERN_LENGTH - 1;

    while (text_index < text_len) {
        // compare with tail of pattern
        pattern_index = PATTERN_LENGTH - 1;
        while (text[text_index] == pattern[pattern_index]) {
            if (pattern_index == 0) {
                // pattern matches all
                return text + text_index;
            }
            text_index--;
            pattern_index--;
        }

        if (table[text[text_index]] > PATTERN_LENGTH - pattern_index) {
            // shift compare position
            text_index += table[text[text_index]];
        } else {
            // pattern must not shift left
            text_index += PATTERN_LENGTH - pattern_index;
        }
    }

    return NULL;
}

int main(void)
{
    unsigned char *result;

    result = bm_search(original_text, original_pattern);

    if (result == NULL) {
        printf("\"%s\" was not found\n", original_pattern);
    } else {
        printf("\"%s\" was found\n", original_pattern);
    }

    return EXIT_SUCCESS;
}
