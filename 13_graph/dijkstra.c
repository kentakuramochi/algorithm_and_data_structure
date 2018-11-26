#include <stdio.h>

#define STATION_NUMBER 6
#define START_STATION 0

char *stations[] = {
    "Yokohama", "Musashikosugi", "Shinagawa", "Shibuya", "Shinbashi", "Tameike-Sanno"
};

// required time from start station
int current_cost[STATION_NUMBER];
// fixed flag
int fixed[STATION_NUMBER];

// weighted graph
// weight: required time
int adjacency_matrix[STATION_NUMBER][STATION_NUMBER] = {
    { 0, 12, 28, 0, 0, 0 },
    { 12, 0, 10, 13, 0, 0 },
    { 28, 10, 0, 11, 7, 0 },
    { 0, 13, 11, 0, 0, 9 },
    { 0, 0, 7, 0, 0, 4 },
    { 0, 0, 0, 9, 4, 0 }
};

// Dijkstra's algorithm
void dijkstra()
{
    int i, min_station, min_time, new_time;

    // init
    for (i = 0; i < STATION_NUMBER; i++) {
        current_cost[i] = -1;
        fixed[i] = 0;
    }

    // cost of start station: 0
    current_cost[0] = 0;

    while (1) {
        min_time = -1;
        for (i = 0; i < STATION_NUMBER; i++) {
            // check station which required time is not fixed
            if (fixed[i] == 0 && current_cost[i] != -1) {
                if (min_time == -1 || min_time > current_cost[i]) {
                    min_time = current_cost[i];
                    min_station = i;
                }
            }
        }

        // all required time is fixed
        if (min_time == -1) {
            break;
        }

        // check required time from this station to all other stations
        for (i = 0; i < STATION_NUMBER; i++) {
            if (fixed[i] == 0 && adjacency_matrix[min_station][i] > 0) {
                // required time via this station
                new_time = min_time + adjacency_matrix[min_station][i];

                // if the required time is shorter than registered time, renew time
                if (current_cost[i] == -1 || current_cost[i] > new_time) {
                    current_cost[i] = new_time;
                }
            }
        }

        // fix
        fixed[min_station] = 1;
    }
}

int main(void)
{
    dijkstra();

    // required time from Yokohama to Tameike-Sanno
    printf("%s -> %s (%d min)\n", stations[0], stations[5], current_cost[5]);

    return 0;
}