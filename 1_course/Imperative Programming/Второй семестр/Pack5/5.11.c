#include <stdlib.h>
#include <stdio.h>

typedef struct Vertex {
    int edges_num;
    int colour;
    int parent;
    int enter;
    int up;
    int edges[1000];
} Vert;

void getEdge(Vert *verts, int from, int to, int edge_num) {
    if (from != to) {
        verts[from].edges[verts[from].edges_num] = to;
        verts[from].edges_num++;
        verts[to].edges[verts[to].edges_num] = from;
        verts[to].edges_num++;
    }
}

void DFS(Vert *verts, int start, int *cutpoints, int *time) {
    verts[start].colour = 1;
    (*time)++;
    verts[start].enter = verts[start].up = *time;

    int c = 0;

    for (int i = 0; i < verts[start].edges_num; ++i) {
        int next_vert = verts[start].edges[i];
        if (next_vert != verts[start].parent) {
            if (verts[next_vert].colour) {
                verts[start].up = verts[start].up < verts[next_vert].enter ? 
                    verts[start].up : verts[next_vert].enter;
            }
            else {
                verts[next_vert].parent = start;
                DFS(verts, next_vert, cutpoints, time);
                c++;
                verts[start].up = verts[start].up < verts[next_vert].up ? 
                    verts[start].up : verts[next_vert].up;
                if (verts[start].parent && verts[next_vert].up >= verts[start].enter) {
                    cutpoints[start] = 1;
                }
            }
        }
    }
    if (!verts[start].parent && c > 1) {
        cutpoints[start] = 1;
    }


    verts[start].colour = 2;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    scanf("%d %d", &n, &m);

    Vert *verts = (Vert *)calloc(n + 1, sizeof(Vert));
    int *cutpoints = (int *)calloc(n + 1, sizeof(int));
    int time = 0;

    for (int i = 0; i < m; ++i) {
        int from, to;
        scanf("%d %d", &from, &to);
        getEdge(verts, from, to, i + 1);
    }

    for (int i = 1; i <= n; ++i) {
        if (verts[i].colour == 0) {
            DFS(verts, i, cutpoints, &time);
        }
    }

    int c = 0;
    for (int i = 1; i <= n; ++i) {
        if (cutpoints[i]) {
            c++;
        }
    }

    printf("%d\n", c);
    for (int i = 1; i <= n; ++i) {
        if (cutpoints[i]) {
            printf("%d ", i);
        }
    }

    free(verts);
    free(cutpoints);

    fclose(stdin);
    fclose(stdout);
    return 0;
}