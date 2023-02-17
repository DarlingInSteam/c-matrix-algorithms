#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int input(double ***matrix, int *n, int *m);
void output(double **res, int n, int m);
void getMatrixWithoutRowAndCol(double **matrix, int size, int row, int col, double ***newMatrix);
double matrixDet(double **matrix, int size);
void search(double **a, int n, double **res);
void mul(double **a, int n, int m, double d);
void transp(double **a, int n, int m, double ***mat);

int main() {
    double **matrix, **res;
    int size_arr_first, size_arr_second;
    int f = input(&matrix, &size_arr_first, &size_arr_second);
    if (f == 1) {
        printf("n/a");
        return 1;
    }
    if (f == 2) {
        printf("n/a");
        for (int i = 0; i < size_arr_first; i++) free(matrix[i]);
        free(matrix);
        return 1;
    }

    res = malloc((size_arr_first) * sizeof(double));
    for (int i = 0; i < size_arr_first; i++) {
        res[i] = malloc((size_arr_first) * sizeof(double));
    }

    double q = matrixDet(matrix, size_arr_first);
    if (q != 0) {
        search(matrix, size_arr_first, res);
        mul(res, size_arr_first, size_arr_first, 1 / q);
        transp(res, size_arr_first, size_arr_first, &matrix);
        output(matrix, size_arr_first, size_arr_first);

    } else {
        printf("n/a");
    }
    for (int i = 0; i < size_arr_first; i++) free(matrix[i]);
    free(matrix);
    for (int i = 0; i < size_arr_first; i++) free(res[i]);
    free(res);
}

void getMatrixWithoutRowAndCol(double **matrix, int size, int row, int col, double ***newMatrix) {
    int offsetRow = 0;
    int offsetCol = 0;
    for (int i = 0; i < size - 1; i++) {
        if (i == row) {
            offsetRow = 1;
        }

        offsetCol = 0;
        for (int j = 0; j < size - 1; j++) {
            if (j == col) {
                offsetCol = 1;
            }

            (*newMatrix)[i][j] = matrix[i + offsetRow][j + offsetCol];
        }
    }
}

double matrixDet(double **matrix, int size) {
    int det = 0;
    int degree = 1;

    if (size == 1) {
        return matrix[0][0];
    }

    else if (size == 2) {
        return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
    } else {
        double **newMatrix;
        newMatrix = malloc((size - 1) * sizeof(double));
        for (int i = 0; i < size - 1; i++) {
            newMatrix[i] = malloc((size - 1) * sizeof(double));
        }

        for (int j = 0; j < size; j++) {
            getMatrixWithoutRowAndCol(matrix, size, 0, j, &newMatrix);

            det = det + (degree * matrix[0][j] * matrixDet(newMatrix, size - 1));

            degree *= -1;
        }

        for (int i = 0; i < size - 1; i++) {
            free(newMatrix[i]);
        }
        free(newMatrix);
    }

    return det;
}

int input(double ***matrix, int *n, int *m) {
    if (scanf("%d %d", n, m) != 2 || *n <= 0 || *m <= 0) {
        return 1;
    }

    (*matrix) = malloc(*n * sizeof(double *));

    for (int i = 0; i < *n; i++) {
        (*matrix)[i] = malloc(*m * sizeof(double));
    }

    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            double l;
            if (scanf("%lf", &l) != 1) {
                return 2;
            }
            (*matrix)[i][j] = l;
        }
    }

    return 0;
}

void transp(double **a, int n, int m, double ***mat) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            (*mat)[j][i] = a[i][j];
        }
    }
}

void mul(double **a, int n, int m, double d) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i][j] *= d;
        }
    }
}

void search(double **a, int n, double **res) {
    double **newMatrix;

    newMatrix = malloc((n - 1) * sizeof(double *));

    for (int i = 0; i < n - 1; i++) {
        newMatrix[i] = malloc((n - 1) * sizeof(double));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            getMatrixWithoutRowAndCol(a, n, i, j, &newMatrix);
            res[i][j] = pow(-1, i + 2 + j) * matrixDet(newMatrix, n - 1);
        }
    }

    for (int i = 0; i < n - 1; i++) free(newMatrix[i]);
    free(newMatrix);
}

void output(double **res, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%.6lf", res[i][j]);

            if (j + 1 < m) printf(" ");
        }

        if (i + 1 < n) printf("\n");
    }
}