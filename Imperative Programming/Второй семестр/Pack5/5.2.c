#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int from, to;
} Edge;

typedef struct Vert {
    int edges_num;
    int distance;
    Edge edges[200001];
} Vert;

void getEdge (Vert *vert, int from, int to) {
    vert->edges[vert->edges_num].from = from;
    vert->edges[vert->edges_num].to = to;
    vert->edges_num++;
}

void bfs_init(Vert *verts, int verts_num) {
    for (int i = 1; i <= verts_num; ++i) {
        verts[i].distance = -1;
    }
    verts[1].distance = 0;
}

void BFS(Vert *vertices, int num, int curr) {
    for (int i = 0; i < vertices[curr].edges_num; ++i) {
        int next = vertices[curr].edges[i].to;
        if (vertices[next].distance == -1 || vertices[next].distance > vertices[curr].distance + 1) {
            vertices[next].distance = vertices[curr].distance + 1;
            BFS(vertices, num, next);
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int m, n, dest, src;
    scanf ("%d %d", &m, &n);

    Vert *verts = (Vert *)calloc(m + 1, sizeof(Vert));

    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &src, &dest);
        getEdge(&verts[src], src, dest);
    }

    bfs_init(verts, m);

    BFS(verts, m, 1);

    for (int i = 1; i <= m; ++i) {
        printf("%d\n", verts[i].distance);
    }

    fclose(stdin);
    fclose(stdout);
}