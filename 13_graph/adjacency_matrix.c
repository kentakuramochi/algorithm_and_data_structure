#include <stdio.h>

#define STATION_NUMBER 6

char *stations[] = {
    "Kamakura", "Fujisawa", "Yokohama", "Yokosuka", "Chigasaki", "Tokyo" 
};

// adjacency matrix
int adjacency_matrix[STATION_NUMBER][STATION_NUMBER] = {
    { 0, 1, 0, 1, 0, 0 },
    { 0, 0, 1, 0, 1, 0 },
    { 1, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 0 }
};

int main(void)
{
    int i, j;
    for (i = 0; i < STATION_NUMBER; i++) {
        printf("%s: ", stations[i]);
        for (j = 0; j < STATION_NUMBER; j++) {
            if (adjacency_matrix[i][j] == 1) {
                printf("-> %s ", stations[j]);
            }
        }
        printf("\n");
    }

    return 0;
}