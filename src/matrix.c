#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "matrix.h"

Matrix_t createMatrix(int rows, int cols, Matrix_t *src) {
    Matrix_t matrix = {NULL, rows, cols};
    matrix.data = (double **) malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
        matrix.data[i] = (double *) malloc(cols * sizeof(double));
    }

    if (src) {
        copyMatrix(&matrix, src);
    }

    return matrix;
}
void killMatrix(Matrix_t *matrix) {
    for (int i = 0; i < matrix->nrows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    matrix->ncols = 0;
    matrix->nrows = 0;
}

Matrix_t *copyMatrix(Matrix_t *src, Matrix_t *dst) {
    if (src->ncols != dst->ncols || src->nrows != dst->nrows)
        return NULL;

    for (int i = 0; i < src->nrows; i++) {
        memcpy(dst->data[i], src->data[i], src->nrows * sizeof(double));
    }
    return dst;
}

void printMatrix(const Matrix_t *matrix) {
    int i, j;
    for (i = 0; i < matrix->nrows; i++) {
        for (j = 0; j < matrix->ncols; j++) {
            printf("%f   ", matrix->data[i][j]);
        }
        printf("\n");
    }
}
