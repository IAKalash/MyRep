#include <stdlib.h>
#include <stdio.h>

typedef struct Vertex {
    int edges_num;
    int colour;
    int component;
    int edges[100000];
} Vert;

typedef struct list {
    int index;
    int *list;
} Index_list;

void getEdge(Vert *verts, int from, int to) {
    verts[from].edges[verts[from].edges_num] = to;
    verts[from].edges_num++;
}

void DFS(Vert *verts, int start, Index_list *ind_list) {
    verts[start].colour = 1;
    for (int i = 0; i < verts[start].edges_num; ++i) {
        int next = verts[start].edges[i];
        if (verts[next].colour == 0) {
            DFS(verts, next, ind_list);
        }
    }
    ind_list->list[ind_list->index] = start;
    ind_list->index++;
    verts[start].colour = 2;
}

void DFS2(Vert *verts, int start, int component) {
    verts[start].colour = 1;
    verts[start].component = component;
    for (int i = 0; i < verts[start].edges_num; ++i) {
        int next = verts[start].edges[i];
        if (verts[next].colour == 0) {
            DFS2(verts, next, component);
        }
    }
    verts[start].colour = 2;
}

void Kosaraju(int n, int m) {
    int from, to;

    Vert *verts = (Vert*)calloc(n + 1, sizeof(Vert));
    int *list = (int *)malloc(sizeof(int) * n);
    Index_list ind_list = {0, list};

    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &from, &to);
        getEdge(verts, from, to);
    }

    for (int i = 1; i <= n; ++i) {
        if (verts[i].colour == 0) {
            DFS(verts, i, &ind_list);
        }
    }

    Vert *transp_verts = (Vert*)calloc(n + 1, sizeof(Vert));
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < verts[i].edges_num; ++j) {
            getEdge(transp_verts, verts[i].edges[j], i);
        }
    }

    int SCC = 0;
    for (int i = ind_list.index - 1; i >= 0; --i) {
        int ind = ind_list.list[i];
        if (transp_verts[ind].colour == 0) {
            SCC++;
            DFS2(transp_verts, ind, SCC);
        }
    }

    printf("%d\n", SCC);
    for (int i = 1; i <= n; ++i) {
        printf("%d ", transp_verts[i].component);
    }

    free(verts);
    free(list);
    free(transp_verts);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    scanf("%d %d", &n, &m);
    Kosaraju(n, m);

    fclose(stdin);
    fclose(stdout);
    return 0;
}