#include <stdlib.h>
#include <stdio.h>

typedef struct Vertex{
    int edges_num;
    int colour;
    int parent;
    int edges[100];
} Vert;

typedef struct list{
    int index;
    int *list;
} Index_list;

void getEdge(Vert *verts, int from, int to) {
    verts[from].edges[verts[from].edges_num] = to;
    verts[from].edges_num++;
}

int DFS(Vert *verts, int start, Index_list *ind_list) {
    verts[start].colour = 1;
    for (int i = 0; i < verts[start].edges_num; ++i) {
        if (verts[verts[start].edges[i]].colour == 1) {
            return -1;
        }
        else if (verts[verts[start].edges[i]].colour == 0) {
            verts[verts[start].edges[i]].parent = start;

            if (DFS(verts, verts[start].edges[i], ind_list) == -1) {
                return -1;
            }
        }
    }
    ind_list->list[ind_list->index] = start;
    ind_list->index--;
    verts[start].colour = 2;
    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    int from, to;
    scanf("%d %d", &n, &m);

    Vert *verts = (Vert*)calloc(n + 1, sizeof(Vert));

    int *list = (int *)malloc(sizeof(int) * n);
    Index_list ind_list;
    ind_list.index = n - 1;
    ind_list.list = list;

    for (int i = 0; i < m; ++i) {
        scanf ("%d %d", &from, &to);
        getEdge(verts, from, to);
    }
    
    for (int i = 1; i <= n; ++i) {
        if (verts[i].colour == 0) {
            int num = DFS(verts, i, &ind_list);

            if (num == -1) {
                printf("NO");

                free(verts);
                free(list);
                fclose(stdin);
                fclose(stdout);
                return 0;
            }
        }
    }

    int *result = (int *)malloc(sizeof(int) * (n + 1));
    for (int i = 0; i < n; ++i) {
        result[ind_list.list[i]] = i + 1;
    }
    printf("YES\n");
    for (int i = 1; i <= n; ++i) {
        printf("%d ", result[i]);
    }
    free(result);

    free(verts);
    free(list);
    fclose(stdin);
    fclose(stdout);
    return 0;
}