#include <stdlib.h>
#include <stdio.h>

int solve(int curr, int *switches, int *bulbs, int *res, int n, int k, int m, int l, int *order) {
    if (curr == n) {
        for (int f = 0; f < m; f++) {
            if (bulbs[f] != l) {
                return 0;
            }
        }
        return 1;
    }
    
    for (int p = 0; p < k; p++) {
        int j = order[curr * k + p];
        int valid = 1;
        for (int f = 0; f < m; f++) {
            if (bulbs[f] == l && switches[curr * k * m + j * m + f]) {
                valid = 0;
                break;
            }
        }
        if (!valid) continue;
        
        for (int f = 0; f < m; f++) {
            bulbs[f] += switches[curr * k * m + j * m + f];
            if (bulbs[f] > l || bulbs[f] + (n - curr - 1) < l) {
                for (int g = 0; g <= f; g++) {
                    bulbs[g] -= switches[curr * k * m + j * m + g];
                }
                valid = 0;
                break;
            }
        }
        if (!valid) continue;
        
        res[curr] = j + 1;
        if (solve(curr + 1, switches, bulbs, res, n, k, m, l, order)) {
            return 1;
        }
        for (int f = 0; f < m; f++) {
            bulbs[f] -= switches[curr * k * m + j * m + f];
        }
    }
    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, k, m, l;
    scanf("%d %d %d %d", &n, &k, &m, &l);

    int *switches = (int *)malloc(sizeof(int) * m * k * n);
    int *order = (int *)malloc(sizeof(int) * n * k);
    char sym;
    scanf("%c", &sym);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            for (int f = 0; f < m; ++f) {
                scanf("%c", &sym);
                if (sym == 'X')
                    switches[i * k * m + j * m + f] = 1;
                else 
                    switches[i * k * m + j * m + f] = 0;
            }
            scanf("%c", &sym);
        }
    }

    int *x_count = (int *)calloc(n * k, sizeof(int));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            int count = 0;
            for (int f = 0; f < m; f++) {
                count += switches[i * k * m + j * m + f];
            }
            x_count[i * k + j] = count;
            order[i * k + j] = j;
        }
        for (int p = 0; p < k - 1; p++) {
            for (int q = 0; q < k - p - 1; q++) {
                int a = i * k + q, b = i * k + q + 1;
                if (x_count[a] < x_count[b]) {
                    int tmp = x_count[a];
                    x_count[a] = x_count[b];
                    x_count[b] = tmp;
                    tmp = order[a];
                    order[a] = order[b];
                    order[b] = tmp;
                }
            }
        }
    }

    int *lamp_x = (int *)calloc(m, sizeof(int));
    for (int f = 0; f < m; f++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < k; j++) {
                lamp_x[f] += switches[i * k * m + j * m + f];
            }
        }
        if (lamp_x[f] < l || (l == 0 && lamp_x[f] > 0)) {
            printf("NO\n");
            free(switches);
            free(order);
            free(x_count);
            free(lamp_x);
            fclose(stdin);
            fclose(stdout);
            return 0;
        }
    }

    int *bulbs = (int *)calloc(m, sizeof(int));
    int *res = (int *)calloc(n, sizeof(int));

    if (solve(0, switches, bulbs, res, n, k, m, l, order)) {
        printf("YES\n");
        for (int i = 0; i < n; i++) {
            printf("%d\n", res[i]);
        }
    } else {
        printf("NO\n");
    }

    free(switches);
    free(bulbs);
    free(res);
    free(order);
    free(x_count);
    free(lamp_x);

    fclose(stdin);
    fclose(stdout);
    return 0;
}