#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int edges_num;
    int distance;
    int edges[4];
} Vert;

void getEdge(Vert *verts, int from, int to) {
    verts[from].edges[verts[from].edges_num] = to;
    verts[from].edges_num++;
}

void BFS(Vert *vertices, int curr) {
    for (int i = 0; i < vertices[curr].edges_num; ++i) {
        int next = vertices[curr].edges[i];
        if (vertices[next].distance == -1 || vertices[next].distance > vertices[curr].distance + 1) {
            vertices[next].distance = vertices[curr].distance + 1;
            BFS(vertices, next);
        }
    }
}

int runLab(int n) {
    int count = 0;
    char **lab = (char **)malloc(n * sizeof(char*));

    for (int i = 0; i < n; ++i) {
        getchar();
        char *line = (char *)malloc(n);
        fgets(line, n + 1, stdin);
        lab[i] = line;
    }

    count = 0;
    Vert *verts = (Vert *)malloc(n * n * sizeof(Vert));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            verts[i * n + j].distance = -1;
            verts[i * n + j].edges_num = 0;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (lab[i][j] != '*') {
                int idx = i * n + j;
                if (i != 0 && lab[i - 1][j] != '*') {
                    getEdge(verts, idx, idx - n);
                }
                if (i != n - 1 && lab[i + 1][j] != '*') {
                    getEdge(verts, idx, idx + n);
                }
                if (j != 0 && lab[i][j - 1] != '*') {
                    getEdge(verts, idx, idx - 1);
                }
                if (j < (n - 1) && lab[i][j + 1] != '*') {
                    getEdge(verts, idx, idx + 1);
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (lab[i][j] == ' ' && verts[i * n + j].distance == -1) {
                BFS(verts, i * n + j);
                ++count;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        free(lab[i]);
    }

    free(verts);
    free(lab);

    return count;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    scanf("%d", &n);

    printf("%d", runLab(n) - 1);

    fclose(stdin);
    fclose(stdout);
    return 0;
}