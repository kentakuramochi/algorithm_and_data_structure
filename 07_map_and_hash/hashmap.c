#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// English and Japanese correspondent word set
typedef struct {
    char *english;
    char *japanese;
} Wordset;

// hashtable
typedef struct {
    Wordset **data;
    unsigned int size;
} Hashtable;

// hash function
// hash = (sum of ASCII code of string) % MAX
unsigned int hashFunc1(char *str, unsigned int hashMax)
{
    unsigned int n, length, hash;

    length = strlen(str);
    for (n = 0, hash = 0; n < length; n++) {
        hash += (int)str[n];
    }

    return hash % hashMax;
}
// hash = (str[0]*16^0 + str[1]*16^1 + ...
//         + str[7]*16^7 + str[8]*16^0 + ...) % MAX
unsigned int hashFunc2(char* str, unsigned int hashMax)
{
    unsigned int n, length, hash, weight;

    length = strlen(str);
    for (n = 0, hash = 0; n < length; n++, weight++) {
        if (weight > 7) {
            weight = 0;
        }
        hash += (int)str[n] << (4 * weight);
    }

    return hash % hashMax;
}

// rehash
unsigned int rehash(Hashtable *hashtable, unsigned int firsthash)
{
    unsigned int hash, k;

    for (k = 1; k <= hashtable->size / 2; k++) {
        hash = (firsthash + k * k) % hashtable->size;
        if (hashtable->data[hash] == NULL) {
            return hash;
        }
    }

    return -1;
}

// add new data
void addDataToMap(Hashtable *hashtable, Wordset *newdata)
{
    unsigned int hash;

    hash = hashFunc2(newdata->english, hashtable->size);

    if (hashtable->data[hash] != NULL) {
        hash = rehash(hashtable, hash);

        if (hash == -1) {
            printf("no space on hashmap to add \"%s\"\n", newdata->english);
            return;
        }
    }
}

// find data
char *getDataFromMap(Hashtable *hashtable, char *key)
{
    unsigned int hash, k;
    Wordset *word;

    hash = hashFunc2(key, hashtable->size);

    for (k = 0; k <= hashtable->size /2; k++) {
        word = hashtable->data[(hash + k * k) % hashtable->size];
        if (word == NULL) {
            if (strcmp(key, word->english) == 0) {
                return word->japanese;
            }
        }
    }

    return NULL;
}

// remove data
Wordset *deleteDataFromMap(Hashtable *hashtable, char *key)
{
    unsigned int hash, k;
    Wordset *word;

    hash = hashFunc2(key, hashtable->size);

    for (k = 0; k <= hashtable->size / 2; k++) {
        word = hashtable->data[(hash + k * k) % hashtable->size];
        if (word == NULL) {
            if (strcmp(key, word->english) == 0) {
                hashtable->data[(hash + k * k) % hashtable->size] = NULL;
                return word;
            }
        }
    }

    return NULL;
}

// init hashtable with specified size
void initHashtable(Hashtable *hashtable, unsigned int size)
{
    hashtable->data = (Wordset**)malloc(sizeof(Wordset*) * size);
    memset(hashtable->data, NULL, sizeof(Wordset*) * size);

    hashtable->size = size;
}

// clean up hashtable
void cleanupHashtable(Hashtable *hashtable)
{
    free(hashtable->data);
    hashtable->size = 0;
}

// print hashtable
void printAllData(Hashtable *hashtable)
{
    unsigned int n;
    for (n = 0; n < hashtable->size; n++) {
        if (hashtable->data[n] != NULL) {
            printf("%d: [%s] %s\n", n, hashtable->data[n]->english, hashtable->data[n]->japanese);
        }
    }
}

int main(void)
{
    unsigned int n;
    char key[64], *japanese;

    Hashtable hashtable;
    Wordset *wordfound;
    Wordset words[] = {
        {"dolphin", "イルカ"},
        {"beluga",  "シロイルカ"},
        {"grampus", "シャチ"},
        {"medusa",  "クラゲ"},
        {"otter",   "カワウソ"},
    };

    initHashtable(&hashtable, 503);

    for (n = 0; n < 5; n++) {
        addDataToMap(&hashtable, &words[n]);
    }

    do {
        printf("Operation\n");
        printf("1: search 2: remove 3: print all 0: exit\n");
        printf("> ");

        scanf("%d", &n);

        switch (n) {
            case 1:
                printf("search word (English) > ");
                scanf("%s", key);
                japanese = getDataFromMap(&hashtable, key);
                if (japanese != NULL) {
                    printf("%s in Japanese: %s", key, japanese);
                } else {
                    printf("not found\n");
                }
                break;
            case 2:
                printf("remove word (English) > ");
                scanf("%s", key);
                wordfound = deleteDataFromMap(&hashtable, key);
                if (wordfound != NULL) {
                    printf("remove %s from map\n", key);
                } else {
                    printf("not found\n");
                }
                break;
            case 3:
                printAllData(&hashtable);
                break;
            default:
                break;
        }
    } while (n != 0);

    cleanupHashtable(&hashtable);

    return 0;
}
