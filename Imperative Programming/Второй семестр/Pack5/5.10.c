#include <stdlib.h>
#include <stdio.h>

typedef struct Edge {
    int to;
    int edge_num;
    int mult;
} Edge;

typedef struct Vertex {
    int edges_num;
    int colour;
    int enter;
    int ret;
    Edge edges[10000];
} Vert;

void getEdge(Vert *verts, int from, int to, int edge_num) {
    if (from != to) {
        int mult = 1; 
        for (int i = 0; i < verts[from].edges_num; ++i) {
            if (verts[from].edges[i].to == to) {
                mult = verts[from].edges[i].mult + 1;
                verts[from].edges[i].mult = mult;
                for (int j = 0; j < verts[to].edges_num; ++j) {
                    if (verts[to].edges[j].to == from) {
                        verts[to].edges[j].mult = mult;
                        break;
                    }
                }
                break;
            }
        }
        verts[from].edges[verts[from].edges_num].to = to;
        verts[from].edges[verts[from].edges_num].edge_num = edge_num;
        verts[from].edges[verts[from].edges_num].mult = mult;
        verts[from].edges_num++;
        verts[to].edges[verts[to].edges_num].to = from;
        verts[to].edges[verts[to].edges_num].edge_num = edge_num;
        verts[to].edges[verts[to].edges_num].mult = mult;
        verts[to].edges_num++;
    }
}

void DFS(Vert *verts, int start, int parent_edge_num, int *bridges, int *time) {
    (*time)++;
    verts[start].enter = verts[start].ret = *time;
    verts[start].colour = 1;

    for (int i = 0; i < verts[start].edges_num; ++i) {
        int next_vert = verts[start].edges[i].to;
        int edge_num = verts[start].edges[i].edge_num;

        if (edge_num != parent_edge_num) {
            if (verts[next_vert].colour == 0) {
                DFS(verts, next_vert, edge_num, bridges, time);
                verts[start].ret = verts[start].ret < verts[next_vert].ret ? verts[start].ret : verts[next_vert].ret;
                if (verts[next_vert].ret > verts[start].enter && verts[start].edges[i].mult == 1) {
                    bridges[edge_num] = 1;
                }
            } else {
                verts[start].ret = verts[start].ret < verts[next_vert].enter ? verts[start].ret : verts[next_vert].enter;
            }
        }
    }

    verts[start].colour = 2;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    scanf("%d %d", &n, &m);

    Vert *verts = (Vert *)calloc(n + 1, sizeof(Vert));
    int *bridges = (int *)calloc(m + 1, sizeof(int));
    int time = 0;

    for (int i = 0; i < m; ++i) {
        int from, to;
        scanf("%d %d", &from, &to);
        getEdge(verts, from, to, i + 1);
    }

    for (int i = 1; i <= n; ++i) {
        if (verts[i].colour == 0) {
            DFS(verts, i, -1, bridges, &time);
        }
    }

    int c = 0;
    for (int i = 1; i <= m; ++i) {
        if (bridges[i]) {
            c++;
        }
    }

    printf("%d\n", c);
    for (int i = 1; i <= m; ++i) {
        if (bridges[i]) {
            printf("%d ", i);
        }
    }

    free(verts);
    free(bridges);
    fclose(stdin);
    fclose(stdout);
    return 0;
}