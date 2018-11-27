#include <stdio.h>

#define STATION_NUMBER 6
#define START_STATION 0
#define GOAL_STATION 5

// node
typedef struct TagNode {
    char *name;
    int *weights;           // weights with connected nodes
    int cost;               // cost (required time)
    int fixed;              // fixed flag
    struct TagNode *prev;   // previous node
} Node;


Node nodes[STATION_NUMBER];

// required time from start station
//int current_cost[STATION_NUMBER];
// fixed flag
//int fixed[STATION_NUMBER];

char *stations[] = {
    "Yokohama", "Musashikosugi", "Shinagawa", "Shibuya", "Shinbashi", "Tameike-Sanno"
};

// adjacendy matrix
int adjacency_matrix[STATION_NUMBER][STATION_NUMBER] = {
    { 0, 12, 28, 0, 0, 0 },
    { 12, 0, 10, 13, 0, 0 },
    { 28, 10, 0, 11, 7, 0 },
    { 0, 13, 11, 0, 0, 9 },
    { 0, 0, 7, 0, 0, 4 },
    { 0, 0, 0, 9, 4, 0 }
};

void init_nodes()
{
    int i;
    for (i = 0; i < STATION_NUMBER; i++) {
        nodes[i].name = stations[i];
        nodes[i].weights = adjacency_matrix[i];
        nodes[i].cost = -1;
        nodes[i].fixed = 0;
        nodes[i].prev = NULL;
    }
}

// Dijkstra's algorithm
void dijkstra(int start, int goal)
{
    Node *nearest;
    int i, new_cost;

    // init
    init_nodes();

    // cost of start station: 0
    nodes[start].cost = 0;

    while (1) {
        nearest = NULL;
        for (i = 0; i < STATION_NUMBER; i++) {
            // check station which required time is not fixed
            if (nodes[i].fixed == 0 && nodes[i].cost != -1) {
                if (nearest == NULL || nearest->cost > nodes[i].cost) {
                    nearest = &nodes[i];
                }
            }
        }

        // all required time is fixed
        if (nearest == NULL) {
            break;
        }

        for (i = 0; i < STATION_NUMBER; i++) {
            if (nearest->fixed == 0 && nearest->weights[i] > 0) {
                // required time via this station
                new_cost = nearest->cost + nearest->weights[i];

                // if the required time is shorter than registered time, renew time
                if (nodes[i].cost == -1 || nodes[i].cost > new_cost) {
                    nodes[i].cost = new_cost;
                    nodes[i].prev = nearest;
                }
            }
        }

        // fix
        nearest->fixed = 1;
    }
}

int main(void)
{
    Node *station;

    dijkstra(START_STATION, GOAL_STATION);

    station = &nodes[GOAL_STATION];

    // required time from Yokohama to Tameike-Sanno
    while (1) {
        printf("%s (%d min)", station->name, station->cost);
        if (station->prev == NULL) {
            break;
        }
        station = station->prev;
        printf(" <- ");
    }
    printf("\n");

    return 0;
}