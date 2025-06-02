#include <stdlib.h>
#include <stdio.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct Edge {
    int to;
    long long flow;
    long long capacity;
    int is_original;
} Edge;

typedef struct {
    int colour;
    int edges_num;
    Edge edges[200];
} Vert;

void getEdge(Vert *verts, int from, int to, long long weight) {
    verts[from].edges[verts[from].edges_num].to = to;
    verts[from].edges[verts[from].edges_num].capacity = weight;
    verts[from].edges[verts[from].edges_num].flow = 0;
    verts[from].edges[verts[from].edges_num].is_original = 1;
    verts[from].edges_num++;
    
    verts[to].edges[verts[to].edges_num].to = from;
    verts[to].edges[verts[to].edges_num].capacity = weight;
    verts[to].edges[verts[to].edges_num].flow = 0;
    verts[to].edges[verts[to].edges_num].is_original = 1;
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
        for (int i = 1; i <= n; i++) {
            verts[i].colour = 0;
        }
        long long path_flow = dfs(verts, n, start, finish, __LONG_LONG_MAX__);
        if (path_flow == 0) {
            break;
        }
        total_flow += path_flow;
    }
    
    return total_flow;
}

void mark_reachable(Vert *verts, int n, int curr, int *reachable) {
    reachable[curr] = 1;
    
    for (int j = 0; j < verts[curr].edges_num; j++) {
        int v = verts[curr].edges[j].to;
        if (!reachable[v] && verts[curr].edges[j].capacity > verts[curr].edges[j].flow) {
            mark_reachable(verts, n, v, reachable);
        }
    }
}

void collect_edges(Vert *verts, int n, int *reachable, int **final_edges, int *final_k, int *final_capacity) {
    for (int u = 1; u <= n; u++) {
        if (reachable[u]) {
            for (int j = 0; j < verts[u].edges_num; j++) {
                int v = verts[u].edges[j].to;
                if (!reachable[v] && verts[u].edges[j].flow == verts[u].edges[j].capacity && verts[u].edges[j].is_original) {
                    if (*final_k >= *final_capacity) {
                        *final_capacity *= 2;
                        *final_edges = (int *)realloc(*final_edges, *final_capacity * 2 * sizeof(int));
                    }
                    (*final_edges)[(*final_k) * 2] = u;
                    (*final_edges)[(*final_k) * 2 + 1] = v;
                    (*final_k)++;
                }
            }
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m, s, t;
    scanf("%d %d", &n, &m);
    scanf("%d %d", &s, &t);

    Vert *verts = (Vert *)malloc(sizeof(Vert) * (n + 1));
    for (int i = 1; i <= n; i++) {
        verts[i].edges_num = 0;
        verts[i].colour = 0;
    }

    int final_k = 0;
    int final_capacity = n;
    int *final_edges = (int *)malloc(final_capacity * 2 * sizeof(int));

    for (int i = 0; i < m; i++) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        getEdge(verts, u, v, c);
    }

    long long min_cut = max_flow(verts, n, s, t);

    int reachable[101] = {0};
    mark_reachable(verts, n, s, reachable);
    collect_edges(verts, n, reachable, &final_edges, &final_k, &final_capacity);

    printf("%lld %d\n", min_cut, final_k);
    for (int i = 0; i < final_k; i++) {
        printf("%d %d\n", final_edges[i * 2], final_edges[i * 2 + 1]);
    }

    free(final_edges);
    free(verts);

    fclose(stdin);
    fclose(stdout);
    return 0;
}