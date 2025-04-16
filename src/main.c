#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "algebra.h"
#include "io.h"
#include "matrix.h"
#include "types.h"
#include "sort.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));
    // Exemple de code
    Matrix_t matrix;
    if (loadMatrixFromCSV(&matrix, "matrix.csv")) {
        printf("Csv error !\n");
        return 1;
    }
    shuffleSort(matrix.data, matrix.nrows);

    gaussJordanAlgorithm(&matrix);

    Matrix_t rslt = extractResultPart(&matrix);
    saveMatrixToCSV(&rslt, "exit.csv");

    // Memory free (very important ofc)
    freeMatrix(&rslt);
    freeMatrix(&matrix);

    return 0;
}