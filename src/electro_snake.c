#include <stdio.h>
#include <stdlib.h>

void sort_vertical(int n, int m, int ***result_matrix, int *buf_arr);
void sort_horizontal(int n, int m, int ***result_matrix, int *buf_arr);
int input(int ***matrix, int *n, int *m, int ***result);
void output(int **matrix, int n, int m);

int main() {
    int **matrix, **result;
    int *buf_arr;
    int n, m;
    int det = input(&matrix, &n, &m, &result);
    if (det == 1) {
        printf("n/a");
        return 1;
    }
    if (det == 2) {
        printf("n/a");
        for (int i = 0; i < n; i++) free(matrix[i]);
        free(matrix);
        return 1;
    }

    buf_arr = (int *)malloc((n * m) * sizeof(int));
    int c = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            buf_arr[c] = matrix[i][j];
            c += 1;
        }
    }

    sort_vertical(n, m, &result, buf_arr);
    output(result, n, m);

    sort_horizontal(n, m, &result, buf_arr);
    printf("\n");
    printf("\n");
    output(result, n, m);

    for (int i = 0; i < n; i++) free(matrix[i]);
    free(matrix);
    for (int i = 0; i < n; i++) free(result[i]);
    free(result);
    free(buf_arr);
}

int input(int ***matrix, int *n, int *m, int ***result) {
    char ch1, ch2;
    if (scanf("%d%c %d%c", n, &ch1, m, &ch2) != 4 || ch1 != ' ' || ch2 != '\n' || *n <= 0 || *m <= 0) {
        return 1;
    }

    (*matrix) = malloc(*n * sizeof(int *));

    for (int i = 0; i < *n; i++) {
        (*matrix)[i] = malloc(*m * sizeof(int));
    }

    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            int l;
            if (scanf("%d", &l) != 1) {
                return 2;
            }
            (*matrix)[i][j] = l;
        }

        char ch2;
        if (scanf("%c", &ch2) != 1 || ch2 != '\n') {
            return 2;
        }
    }

    (*result) = malloc(*n * sizeof(int *));

    for (int i = 0; i < *n; i++) {
        (*result)[i] = malloc(*m * sizeof(int));
    }

    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            (*result)[i][j] = 0;
        }
    }

    return 0;
}

void output(int **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d", matrix[i][j]);

            if (j + 1 < m) {
                printf(" ");
            }
        }
        if (i + 1 < n) printf("\n");
    }
}

void sort_vertical(int n, int m, int ***result_matrix, int *buf_arr) {
    for (int i = 0; i < n * m; i++) {
        for (int j = i + 1; j < n * m; j++) {
            if (buf_arr[j] < buf_arr[i]) {
                int tmp = buf_arr[i];
                buf_arr[i] = buf_arr[j];
                buf_arr[j] = tmp;
            }
        }
    }
    int c = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < m; j++) {
                (*result_matrix)[j][i] = buf_arr[c];
                c += 1;
            }
        }
        if (i % 2 == 1) {
            for (int j = m - 1; j >= 0; j--) {
                (*result_matrix)[j][i] = buf_arr[c];
                c += 1;
            }
        }
    }
}

void sort_horizontal(int n, int m, int ***result_matrix, int *buf_arr) {
    for (int i = 0; i < n * m; i++) {
        for (int j = i + 1; j < n * m; j++) {
            if (buf_arr[j] < buf_arr[i]) {
                int tmp = buf_arr[i];
                buf_arr[i] = buf_arr[j];
                buf_arr[j] = tmp;
            }
        }
    }
    int c = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < m; j++) {
                (*result_matrix)[i][j] = buf_arr[c];
                c += 1;
            }
        }
        if (i % 2 == 1) {
            for (int j = m - 1; j >= 0; j--) {
                (*result_matrix)[i][j] = buf_arr[c];

                c += 1;
            }
        }
    }
}