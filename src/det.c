#include <stdio.h>
#include <stdlib.h>

double det(double **matrix, int n, int m);
int input(double ***matrix, int *n, int *m);
void output(double det);
void getMatrixWithoutRowAndCol(double **matrix, int size, int row, int col, double **newMatrix);
double matrixDet(double **matrix, int size);
int main() {
    double **matrix;
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

    double q = matrixDet(matrix, size_arr_first);

    for (int i = 0; i < size_arr_first; i++) free(matrix[i]);
    free(matrix);
    printf("%.6lf", q);
}

void getMatrixWithoutRowAndCol(double **matrix, int size, int row, int col, double **newMatrix) {
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

            newMatrix[i][j] = matrix[i + offsetRow][j + offsetCol];
        }
    }
}

double matrixDet(double **matrix, int size) {
    double det = 0;
    int degree = 1;

    if (size == 1) {
        return matrix[0][0];
    }

    else if (size == 2) {
        return (double)(matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
    } else {
        double **newMatrix;
        newMatrix = malloc((size - 1) * sizeof(double));
        for (int i = 0; i < size - 1; i++) {
            newMatrix[i] = malloc((size - 1) * sizeof(double));
        }

        for (int j = 0; j < size; j++) {
            getMatrixWithoutRowAndCol(matrix, size, 0, j, newMatrix);

            det = det + (double)(degree * matrix[0][j] * matrixDet(newMatrix, size - 1));

            degree = -degree;
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
