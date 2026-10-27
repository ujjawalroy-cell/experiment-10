
#include <stdio.h>
#include <limits.h>

#define MAX 100
#define INF 999999

struct Edge {
    int src, dest, weight;
};

void bellmanFord(struct Edge edges[], int V, int E, int source) {
    int dist[MAX];

    // Step 1: Initialize distances
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
    }
    dist[source] = 0;

    // Step 2: Relax all edges V-1 times
    for (int i = 1; i <= V - 1; i++) {
        int updated = 0;

        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;

            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                updated = 1;
            }
        }

        // Optimization: stop if no distance changes
        if (!updated) {
            break;
        }
    }

    // Step 3: Detect negative-weight cycles
    for (int j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int w = edges[j].weight;

        if (dist[u] != INF && dist[u] + w < dist[v]) {
            printf("Negative-weight cycle detected!\n");
            return;
        }
    }

    // Step 4: Print shortest distances
    printf("Vertex\tShortest Distance from Source\n");

    for (int i = 0; i < V; i++) {
        if (dist[i] == INF) {
            printf("%d\tUnreachable\n", i);
        } else {
            printf("%d\t%d\n", i, dist[i]);
        }
    }
}

int main() {
    int V, E, source;
    struct Edge edges[MAX * MAX];

    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    printf("Enter edges (source destination weight):\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d",
              &edges[i].src,
              &edges[i].dest,
              &edges[i].weight);
    }

    printf("Enter source vertex: ");
    scanf("%d", &source);

    if (V < 1 || V > MAX || E < 0 ||
        E > MAX * MAX || source < 0 || source >= V) {
        printf("Invalid input!\n");
        return 1;
    }

    bellmanFord(edges, V, E, source);

    return 0;
}
