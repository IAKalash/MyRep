#include "sol.h"
#include <stdlib.h>

typedef struct Vert {
    int n;
    Edge edges[300001];
} Vert;

Vert *vertices;
int vertices_num;

void pushEdge (Vert *vert, int from, int to, int weight) {
    vert->edges[vert->n].from = from;
    vert->edges[vert->n].to = to;
    vert->edges[vert->n].weight = weight;
    vert->n++;
}

void init () {
    vertices_num = getVerticesCount();
    vertices = (Vert *)calloc(vertices_num, sizeof(Vert));

    Edge edge;
    while (readEdge(&edge)) {
        pushEdge(&vertices[edge.from], edge.from, edge.to, edge.weight);
        pushEdge(&vertices[edge.to], edge.to, edge.from, edge.weight);
    }
}

int getEdgesCount (int iVertex) {
    return vertices[iVertex].n;
}

Edge getIncidentEdge (int iVertex, int iIndex) {
    return vertices[iVertex].edges[iIndex];
}