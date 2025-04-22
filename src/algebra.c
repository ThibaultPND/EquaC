#include "algebra.h"
#include "matrix.h"
#include "graphics.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

// Prototypes
int getPivotPartiel(Matrix_t *matrix, int column);
void DivideLineByDouble(double *line, int lenght, double k);
void RemoveOtherColumnCoefiscent(Matrix_t *matrix, int column);
void SubstractLineByLineSpecial(double *line_to_substract, double *line, int lenght, int pivot);

// Functions
int gaussJordanAlgorithm(Matrix_t *matrix) {
    printf("Lancement de l'algorithme Gauss Jordan sur la matrice :\n");
    for (int column = 0; column < matrix->ncols - 1; column++) {
        int pivot = getPivotPartiel(matrix, column);
        if (pivot == -1) // Pivot introuvable
            return 1;
        else if (pivot > column) {
            exchangeRows(matrix, pivot, column);
            pivot = column;
        }
        DivideLineByDouble(matrix->data[pivot], matrix->ncols, matrix->data[pivot][column]);
        RemoveOtherColumnCoefiscent(matrix, column);
        updateProgressBar(column+1, matrix->ncols);
    }
    return 0;
}

int getPivotPartiel(Matrix_t *matrix, int column) {
    // TODO Essayer avec data[0][column], voir si ça marche aussi
    int maxi = column;
    for (int i = column; i < matrix->nrows; i++) {
        if (fabs(matrix->data[i][column]) > fabs(matrix->data[maxi][column])) {
            maxi = i;
        }
    }
    return maxi;
}

int exchangeRows(Matrix_t *matrix, int row1, int row2) {
    if (row1 > matrix->nrows || row2 > matrix->nrows) {
        return 1;
    }

    double *temp = matrix->data[row1];
    matrix->data[row1] = matrix->data[row2];
    matrix->data[row2] = temp;

    return 0;
}
void DivideLineByDouble(double *line, int lenght, double k) {
    for (int i = 0; i < lenght; i++) {
        line[i] /= k;
    }
}

void RemoveOtherColumnCoefiscent(Matrix_t *matrix, int column) {
    int pivot = column;
    for (int line = 0; line < matrix->nrows; line++) {
        if (line == pivot)
            continue;
        SubstractLineByLineSpecial(matrix->data[line], matrix->data[pivot], matrix->ncols, pivot);
    }
}
void SubstractLineByLineSpecial(double *line_to_substract, double *line, int lenght, int pivot) {
    double k = line_to_substract[pivot] / line[pivot];
    for (int col = pivot; col < lenght; col++) {
        line_to_substract[col] -= line[col] * k;
    }
}
int transposeMatrix(Matrix_t *matrix) {
    if (matrix->data == NULL)
        return 1;
    for (int i = 0; i < matrix->nrows; i++)
        for (int j = 0; j < matrix->ncols; j++)
            matrix->data[j][i] = matrix->data[i][j];
    return 0;
}

Matrix_t extractMatrixPart(Matrix_t *src) {
    Matrix_t matrix = createMatrix(src->nrows, src->ncols - 1, NULL);
    for (int i = 0; i < matrix.ncols; i++) {
        memcpy(matrix.data[i], src->data[i], matrix.ncols * sizeof(double));
    }
    return matrix;
}
Matrix_t extractResultPart(Matrix_t *matrix) {
    Matrix_t returned_matrix = createMatrix(matrix->nrows, 1, NULL);
    for (int i = 0; i < matrix->nrows; i++) {
        returned_matrix.data[i][0] = matrix->data[i][matrix->ncols - 1];
    }

    return returned_matrix;
}