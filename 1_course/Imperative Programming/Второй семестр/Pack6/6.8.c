#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int weight, cost;
} item;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, w;
    scanf("%d %d", &n, &w);

    item *items = (item *)malloc(sizeof(item) * n);
    int *best = (int *)calloc(n, sizeof(int));
    int *w_costs = (int *)calloc(w + 1, sizeof(int));
    int **take = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        take[i] = (int *)calloc(w + 1, sizeof(int));
    }

    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &items[i].weight, &items[i].cost);
    }

    for (int i = 0; i < n; i++) {
        for (int j = w; j >= items[i].weight; j--) {
            if (w_costs[j - items[i].weight] + items[i].cost > w_costs[j]) {
                w_costs[j] = w_costs[j - items[i].weight] + items[i].cost;
                take[i][j] = 1;
            }
        }
    }

    int k = 0, max_c = 0, min_w = w;
    for (int j = 0; j <= w; j++) {
        if (w_costs[j] > max_c) {
            max_c = w_costs[j];
            min_w = j;
        } else if (w_costs[j] == max_c && j < min_w) {
            min_w = j;
        }
    }

    for (int i = n - 1, j = min_w; i >= 0; i--) {
        if (take[i][j]) {
            best[k++] = i + 1;
            j -= items[i].weight;
        }
    }

    printf("%d %d %d\n", k, min_w, max_c);
    for (int i = k - 1; i >= 0; i--) {
        printf("%d ", best[i]);
    }

    free(items);
    free(best);
    free(w_costs);
    for (int i = 0; i < n; i++) {
        free(take[i]);
    }
    free(take);

    fclose(stdin);
    fclose(stdout);
    return 0;
}