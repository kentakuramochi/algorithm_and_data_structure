#include <stdio.h>
#include <string.h>

#define MAX_STATION 10

// stations
// express as undirected graph
typedef struct tag_station {
    char name[256]; // name of station
    struct tag_station *transitions[MAX_STATION]; // connected stations
} Station;

void init_station(Station *station, char *name)
{
    int i;
    for (i = 0; i < MAX_STATION; i++) {
        station->transitions[i] = NULL;
    }
    strncpy(station->name, name, sizeof(station->name) - 1);
    station->name[sizeof(station->name) - 1] = '\0';
}

void add_station(Station *station, Station *transition)
{
    int i;
    
    // check and register connected station
    for (i = 0; i < MAX_STATION; i++) {
        if (station->transitions[i] == NULL) {
            break;
        }
        if (station->transitions[i] == transition) {
            return;
        }
    }

    if (i == MAX_STATION) {
        return;
    }

    station->transitions[i] = transition;
}

void print_station(Station *station)
{
    int i;
    printf("%s: ", station->name);
    for (i = 0; i < MAX_STATION; i++) {
        if (station->transitions[i] == NULL) {
            break;
        }
        printf("-> %s", station->transitions[i]->name);
    }

    printf("\n");
}

int main(void)
{
    int i;

    // set station
    Station stations[6];
    init_station(&stations[0], "Kamakura");
    init_station(&stations[1], "Fujisawa");
    init_station(&stations[2], "Yokohama");
    init_station(&stations[3], "Yokosuka");
    init_station(&stations[4], "Chigasaki");
    init_station(&stations[5], "Tokyo");

    // Kamakura -> Yokosuka, Fujisawa, Yokohama
    add_station(&stations[0], &stations[3]);
    add_station(&stations[0], &stations[1]);
    add_station(&stations[0], &stations[2]);

    // Fujisawa -> Kamakura, Chigasaki, Yokohama
    add_station(&stations[1], &stations[0]);
    add_station(&stations[1], &stations[4]);
    add_station(&stations[1], &stations[2]);

    // Yokohama -> Fujisawa, Kamakura, Tokyo
    add_station(&stations[2], &stations[1]);
    add_station(&stations[2], &stations[0]);
    add_station(&stations[2], &stations[5]);

    // Yokosuka -> Kamakura
    add_station(&stations[3], &stations[0]);
    // Chigasaki st. -> Fujisawa
    add_station(&stations[4], &stations[1]);
    // Tokyo -> Yokohama
    add_station(&stations[5], &stations[2]);

    for (i = 0; i < 6; i++) {
        print_station(&stations[i]);
    }

    return 0;
}