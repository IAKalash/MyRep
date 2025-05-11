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

int runLab(int height, int width) {
    int start, finish;
    char *lab = (char *)malloc(height * width);

    for (int i = 0; i < height; ++i) {
        scanf("%s", &lab[i * width]);
    }

    Vert *verts = (Vert *)malloc(height * width * sizeof(Vert));

    for (int i = 0; i < height * width; ++i) {
        verts[i].edges_num = 0;
        verts[i].distance = -1;
    }

    for (int i = 0; i < height * width; ++i) {
        if (lab[i] != 'X') {
            if (lab[i] == 'F') finish = i;
            if (lab[i] == 'S') {
                start = i;
                verts[start].distance = 0;
            }

            if (i % width != 0 && lab[i - 1] != 'X') {
                getEdge(verts, i, i - 1);
            }
            if (i % width != width - 1 && lab[i + 1] != 'X') {
                getEdge(verts, i, i + 1);
            }
            if (i >= width && lab[i - width] != 'X') {
                getEdge(verts, i, i - width);
            }
            if (i < width * (height - 1) && lab[i + width] != 'X') {
                getEdge(verts, i, i + width);
            }
        }
    }

    BFS(verts, start);

    int result = verts[finish].distance;

    free(verts);
    free(lab);

    return result;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int height, width;
    scanf("%d %d", &height, &width);

    printf("%d\n", runLab(height, width));

    fclose(stdin);
    fclose(stdout);
    return 0;
}