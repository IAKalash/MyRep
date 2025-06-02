#include <stdlib.h>
#include <stdio.h>

typedef struct Vertex{
    int edges_num;
    int colour;
    int edges[100];
} Vert;

void getEdge(Vert *verts, int from, int to) {
    verts[from].edges[verts[from].edges_num] = to;
    verts[from].edges_num++;
}

int DFS(Vert *verts, int start, int *res) {
    verts[start].colour = 1;
    for (int i = 0; i < verts[start].edges_num; ++i) {
        if (verts[(verts[start].edges[i])].colour == 1) {
            res[0] = (verts[start].edges[i]);
            res[1] = start;
            return 1;
        }
        else if (verts[(verts[start].edges[i])].colour == 0){
            int num = DFS(verts, verts[start].edges[i], res);
            if (num != 0) {
                if (res[0] == res[num]) return num;
                else {
                    ++num;
                    res[num] = start;
                    return num;
                }
            }
        }
    }
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

    for (int i = 0; i < m; ++i) {
        scanf ("%d %d", &from, &to);
        getEdge(verts, from, to);
    }

    int *res = (int *)malloc(sizeof(int) * (n + 1));
    
    for (int i = 1; i <= n; ++i) {
        if (verts[i].colour == 0) {
            int num = DFS(verts, i, res);

            if (num != 0) {
                printf("%d\n", num);
                for (int i = num - 1; i >= 0; --i) {
                    printf("%d ", res[i]);
                }
                free(verts);
                free(res);
                fclose(stdin);
                fclose(stdout);
                return 0;
            }
        }
    }

    printf("-1");

    free(verts);
    free(res);

    fclose(stdin);
    fclose(stdout);
    return 0;
}