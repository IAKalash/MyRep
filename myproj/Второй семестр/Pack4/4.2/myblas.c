void cblas_dgemm (const int Layout, const int transa, const int transb, const int m, const int n, const int k, const double alpha, const double *a, const int lda, const double *b, const int ldb, const double beta, double *c, const int ldc) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                c[i * n + j] += a[i * n + k] * a[k * n + j];
            }
        }
    }
}