#include <stdlib.h>
#include <stdio.h>

typedef struct Edge {
    int from;
    int to;
    int weight;
}Edge;

typedef struct Graph{
    int vertices_num;
    int edges_num;
    Edge *edges;
}Graph;

void getEdge(Edge *edges, int from, int to, int weight, int i) {
    edges[i].from = from - 1;
    edges[i].to = to - 1;
    edges[i].weight = weight;
}

int Bellman_Ford(Graph *graph, int start, int *distances, int *parent) {

    for (int i = 0; i < graph->vertices_num; ++i) {
        distances[i] = 1000000000;
        parent[i] = -1;
    }
    distances[start] = 0;

    for (int i = 0; i < graph->vertices_num - 1; ++i) {
        for (int j = 0; j < graph->edges_num; ++j) {
            if (distances[graph->edges[j].from] != 1000000000 && 
                distances[graph->edges[j].from] + graph->edges[j].weight < distances[graph->edges[j].to]) {
                distances[graph->edges[j].to] = distances[graph->edges[j].from] + graph->edges[j].weight;
                parent[graph->edges[j].to] = graph->edges[j].from;
            }
        }
    }

    return 1;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m, k;
    int from, to, weight;
    scanf("%d %d %d", &n, &m, &k);

    int *friends = (int *)malloc(sizeof(int) * k);

    for (int i = 0; i < k; ++i) {
        scanf("%d", &friends[i]);
    }

    Edge *edges = (Edge *)malloc(m * sizeof(Edge));

    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &from, &to, &weight);
        getEdge(edges, from, to, weight, i);
    }

    Graph graph;
    graph.edges_num = m;
    graph.vertices_num = n;
    graph.edges = edges;

    int *distances = (int *)malloc(n * sizeof(int));
    int *parent = (int *)malloc(n * sizeof(int));

    int path[100], len = 0, vert;

    Bellman_Ford(&graph, 0, distances, parent);

    for (int i = 0; i < k; ++i) {
        vert = friends[i] - 1;
        while (vert != -1) {
            path[len] = vert + 1;
            ++len;
            vert = parent[vert];
        }
        printf("%d %d", distances[friends[i] - 1], len);
        while (len > 0) {
            printf(" %d", path[--len]);
        }
        printf("\n");
    }

    free(friends);
    free(edges);
    free(distances);
    free(parent);

    fclose(stdin);
    fclose(stdout);
    return 0;
}