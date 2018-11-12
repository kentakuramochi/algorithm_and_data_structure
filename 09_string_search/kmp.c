#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATTERN_LENGTH 13

unsigned char original_text[] = "the eighty-eighty-eighth key";
unsigned char original_pattern[] = "eighty-eighth";

// KMP (Knuth-Morris-Pratt) method
unsigned char *kmp_search(unsigned char *text,
        unsigned char *pattern)
{
    int table[PATTERN_LENGTH + 1] = { 0, 0 };
    int text_index = 1, pattern_index = 0;
    int i = 0, j;

    // create table: compare pattern with itself
    while ((pattern[text_index]) != '\0') {
        // count characters matches previously
        // when searching is stopped at patten[text_index],
        // restart searching at pattern[pattern_index]
        if (pattern[text_index] == pattern[pattern_index]) {
            table[++text_index] = ++pattern_index;
        } else if (pattern_index == 0) {
            // restart searching at pattern[0]
            table[++text_index] = 0;
        } else {
            // set match count
            pattern_index = table[pattern_index];
        }
    }
    // in this example,
    // table[] = {0,0,0,0,0,0,0,0,1,2,3,4,5,0}

    // searching
    while ((*text) != '\0') {
        // if pattern matches text, compare next
        if ((*text) == pattern[i]) {
            text++;
            // pattern matches all
            if (pattern[++i] == '\0') {
                return text - PATTERN_LENGTH;
            }
        // next character
        } else if (i == 0) {
            text++;
        // get compare position from table
        } else {
            i =table[i];
        }
    }

    return NULL;
}

int main(void)
{
    unsigned char *result;

    result = kmp_search(original_text, original_pattern);

    if (result == NULL) {
        printf("\"%s\" was not found\n", original_pattern);
    } else {
        printf("\"%s\" was found\n", original_pattern);
    }

    return EXIT_SUCCESS;
}
