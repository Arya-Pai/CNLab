#include <stdio.h>

#define INF 99
#define MAX 20

struct rtable {
    int dist[MAX];
    int nextnode[MAX];
} table[MAX];

int cost[MAX][MAX], n;

void distvector() {
    int i, j, k, count;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            table[i].dist[j] = cost[i][j];
            table[i].nextnode[j] = j;
        }
    }

    do {
        count = 0;
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                for (k = 0; k < n; k++) {
                    if (table[i].dist[j] > cost[i][k] + table[k].dist[j]) {
                        table[i].dist[j] = table[i].dist[k] + table[k].dist[j];
                        table[i].nextnode[j] = k;
                        count++;
                    }
                }
            }
        }
    } while (count != 0);
}

int main() {
    int i, j;

    printf("\nEnter the number of routers (vertices): ");
    scanf("%d", &n);

    printf("\nEnter the cost matrix (use 99 for INF/no direct link):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            if (i == j)
                cost[i][j] = 0;  // distance to itself is always 0
        }
    }

    distvector();

    for (i = 0; i < n; i++) {
        printf("\nState table for router %c:\n", i + 65);
        printf("Destination\tNext Hop\tDistance\n");
        for (j = 0; j < n; j++) {
            printf("    %c\t\t  ", j + 65);
            if (table[i].dist[j] == INF)
                printf("-\t\tINFINITE\n");
            else
                printf("%c\t\t%d\n", table[i].nextnode[j] + 65, table[i].dist[j]);
        }
    }

    return 0;
}
