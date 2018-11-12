#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char original_text[] = "Team Swift";
unsigned char original_pattern[] = "if";

unsigned char *simple_search(unsigned char *text,
        unsigned char *pattern)
{
    int i;

    while ((*text) != '\0') {
        // while end of pattern
        for (i = 0; pattern[i] != '\0'; i++) {
            // not match
            if (pattern[i] != text[i]) {
                break;
            }
        }

        // match totally
        if (pattern[i] == '\0') {
            return text;
        }

        text++;
    }

    return NULL;
}

int main(void)
{
    unsigned char *result;

    result = simple_search(original_text, original_pattern);

    if (result == NULL) {
        printf("\"%s\" was not found\n", original_pattern);
    } else {
        printf("\"%s\" was found\n", original_pattern);
    }

    return EXIT_SUCCESS;
}
