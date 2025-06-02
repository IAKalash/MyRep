#include <stdlib.h>
#include <stdio.h>

typedef struct Edge {
    int from;
    int to;
    long long weight;
}Edge;

typedef struct Graph{
    int vertices_num;
    int edges_num;
    Edge *edges;
}Graph;

void getEdge(Edge *edges, int from, int to, long long weight, int i) {
    edges[i].from = from - 1;
    edges[i].to = to - 1;
    edges[i].weight = weight;
}

int Bellman_Ford(Graph *graph, int start, long long *distances, int *nulls) {

    for (int i = 0; i < graph->vertices_num; ++i) {
        distances[i] = __LONG_LONG_MAX__;
    }
    distances[start] = 0;

    for (int i = 0; i < graph->vertices_num - 1; ++i) {
        for (int j = 0; j < graph->edges_num; ++j) {
            if (distances[graph->edges[j].from] != __LONG_LONG_MAX__ && 
                distances[graph->edges[j].from] + graph->edges[j].weight < distances[graph->edges[j].to]) {
                distances[graph->edges[j].to] = distances[graph->edges[j].from] + graph->edges[j].weight;
            }
        }
    }

    for (int j = 0; j < graph->edges_num; ++j) {
        if (distances[graph->edges[j].from] != __LONG_LONG_MAX__ && 
            distances[graph->edges[j].from] + graph->edges[j].weight < distances[graph->edges[j].to]) {
            nulls[graph->edges[j].to] = 1;
        }
    }

    for (int i = 0; i < graph->vertices_num - 1; ++i) {
        for (int j = 0; j < graph->edges_num; ++j) {
            if (nulls[graph->edges[j].from]) nulls[graph->edges[j].to] = 1;
        }
    }

    return 1;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m, s;
    int from, to;
    long long weight;
    scanf("%d %d %d", &n, &m, &s);

    Edge *edges = (Edge *)malloc(m * sizeof(Edge));

    for (int i = 0; i < m; ++i) {
        scanf("%d %d %lld", &from, &to, &weight);
        getEdge(edges, from, to, weight, i);
    }

    Graph graph;
    graph.edges_num = m;
    graph.vertices_num = n;
    graph.edges = edges;

    long long *distances = (long long *)malloc(n * sizeof(long long));
    int *nulls = (int *)calloc(n, sizeof(int));

    Bellman_Ford(&graph, s - 1, distances, nulls);

    for (int i = 0; i < n; ++i) {
        
        if (distances[i] == __LONG_LONG_MAX__) {
            printf("*\n");
        }
        else if (nulls[i]) {
            printf("-\n");
        }
        else {
            printf("%lld\n", distances[i]);
        }
    }

    free(edges);
    free(distances);
    free(nulls);

    fclose(stdin);
    fclose(stdout);
    return 0;
}