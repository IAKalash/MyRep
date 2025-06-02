#include <stdlib.h>
#include <stdio.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct Edge {
    int to;
    long long flow;
    long long capacity;
} Edge;

typedef struct {
    int colour;
    int edges_num;
    Edge edges[100];
} Vert;

void getEdge(Vert *verts, int from, int to, long long weight) {
    verts[from].edges[verts[from].edges_num].to = to;
    verts[from].edges[verts[from].edges_num].capacity = weight;
    verts[from].edges[verts[from].edges_num].flow = 0;
    verts[from].edges_num++;
    
    verts[to].edges[verts[to].edges_num].to = from;
    verts[to].edges[verts[to].edges_num].capacity = weight;
    verts[to].edges[verts[to].edges_num].flow = 0;
    verts[to].edges_num++;
}

long long dfs(Vert *verts, int n, int curr, int finish, long long bottleneck) {
    if (curr == finish) {
        return bottleneck;
    }
    
    verts[curr].colour = 1;
    
    for (int j = 0; j < verts[curr].edges_num; j++) {
        int i = verts[curr].edges[j].to;
        long long residual = verts[curr].edges[j].capacity - verts[curr].edges[j].flow;
        if (verts[i].colour == 0 && residual > 0) {
            long long path_flow = dfs(verts, n, i, finish, MIN(bottleneck, residual));
            if (path_flow > 0) {
                verts[curr].edges[j].flow += path_flow;
                for (int k = 0; k < verts[i].edges_num; k++) {
                    if (verts[i].edges[k].to == curr) {
                        verts[i].edges[k].flow -= path_flow;
                        break;
                    }
                }
                verts[curr].colour = 0;
                return path_flow;
            }
        }
    }
    
    verts[curr].colour = 0;
    return 0;
}

long long max_flow(Vert *verts, int n, int start, int finish) {
    long long total_flow = 0;
    
    while (1) {
        long long path_flow = dfs(verts, n, start, finish, __LONG_LONG_MAX__);
        if (path_flow == 0) {
            break;
        }
        total_flow += path_flow;
    }
    
    return total_flow;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, k;
    scanf("%d %d", &n, &k);

    Vert *verts = (Vert *)malloc(sizeof(Vert) * (n + 1));
    for (int i = 1; i <= n; i++) {
        verts[i].edges_num = 0;
        verts[i].colour = 0;
    }

    for (int i = 0; i < k; i++) {
        int from, to, weight;
        scanf("%d %d %d", &from, &to, &weight);
        getEdge(verts, from, to, weight);
    }

    printf("%lld", max_flow(verts, n, 1, n));

    free(verts);

    fclose(stdin);
    fclose(stdout);
    return 0;
}