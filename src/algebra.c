#include "algebra.h"
#include "matrix.h"
#include "graphics.h"

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

// Prototypes
int getPivotPartiel(Matrix_t *matrix, int column);
void DivideLineByDouble(double *line, int lenght, double k);
void RemoveOtherColumnCoefiscent(Matrix_t *matrix, int column);
void SubstractLineByLineSpecial(double *line_to_substract, double *line, int lenght, int pivot);

// Functions
int gaussJordanAlgorithm(Matrix_t *matrix) {
    for (int column = 0; column < matrix->ncols - 1; column++) {

        int pivot = getPivotPartiel(matrix, column);
        if (pivot == -1)
            return 1;
        else if (pivot > column)
            exchangeRows(matrix, pivot, column);

        DivideLineByDouble(matrix->data[column], matrix->ncols, matrix->data[column][column]);
        RemoveOtherColumnCoefiscent(matrix, column);
    }
    return 0;
}

int getPivotPartiel(Matrix_t *matrix, int column) {
    int maxi = column;
    double max_value = fabs(matrix->data[maxi][column]);
    for (int i = column + 1; i < matrix->nrows; i++) {
        if (max_value != 0) {
            return maxi;
        }

        double value = fabs(matrix->data[i][column]);
        if (value > max_value) {
            max_value = value;
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
#pragma omp parallel for
    for (int i = 0; i < lenght; i++) {
        line[i] /= k;
    }
}

void RemoveOtherColumnCoefiscent(Matrix_t *matrix, int column) {
    int pivot = column;
#pragma omp parallel for
    for (int line = 0; line < matrix->nrows; line++) {
        if (line != pivot)
            SubstractLineByLineSpecial(matrix->data[line], matrix->data[pivot], matrix->ncols,
                                       pivot);
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
/*
Complexity : 0-3
*/
Matrix_t *generateAugmentedMatrix(int nrows, short complexity) {
    clock_t start = clock();
    Matrix_t *matrix = createMatrix(nrows, nrows + 1, NULL);
    if (!matrix)
        return NULL;

    // Solution connue
    int *solution = (int *) malloc(nrows * sizeof(int));
    if (!solution)
        return NULL;

    for (int i = 0; i < nrows; i++) {
        solution[i] = (i + 1) * (complexity + 1); // Solution croissante ou contrôlée
    }

    printf("Génération de la matrice augmentée %d (complexité %d)\n", nrows, complexity);

    srand(time(NULL));

    for (int i = 0; i < nrows; i++) {
        double sum = 0.0;

        for (int j = 0; j < nrows; j++) {
            double coef = 0.0;

            switch (complexity) {
            case 0: // Simple coefficients
                coef = (i == j) ? 1.0 : 0.0;
                break;
            case 1: // Linéaire
                coef = j + 1;
                break;
            case 2: // Random entre 0 et 9
                coef = (rand() % 10) + 1;
                break;
            case 3: // Random flottant entre -5 et +5
                coef = ((double) (rand() % 1001) / 100.0) - 5.0;
                break;
            default:
                coef = (double) (rand() % 10);
                break;
            }

            matrix->data[i][j] = coef;
            sum += coef * solution[j];
        }

        // Dernière colonne = résultat
        matrix->data[i][nrows] = sum;

        if (complexity >= 2)
            updateProgressBar(i + 1, nrows, start);
    }

    free(solution);
    return matrix;
}

Matrix_t *extractMatrixPart(Matrix_t *src) {
    Matrix_t *matrix = createMatrix(src->nrows, src->ncols - 1, NULL);
    for (int i = 0; i < matrix->ncols; i++) {
        memcpy(matrix->data[i], src->data[i], matrix->ncols * sizeof(double));
    }
    return matrix;
}
Matrix_t *extractResultPart(Matrix_t *matrix) {
    Matrix_t *returned_matrix = createMatrix(matrix->nrows, 1, NULL);
    for (int i = 0; i < matrix->nrows; i++) {
        returned_matrix->data[i][0] = matrix->data[i][matrix->ncols - 1];
    }

    return returned_matrix;
}