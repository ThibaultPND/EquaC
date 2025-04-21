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
    Matrix_t matrix = {NULL, 0, 0};
    if (loadMatrixFromCSV(&matrix, "matrix.csv")) {
        printf("Csv error !\n");
        return 1;
    }
    // shuffleSort(matrix.data, matrix.nrows);

    // clock_t start = clock();
    // gaussJordanAlgorithm(&matrix);
    // printf("Time spent : %ld\n", (clock() - start) / CLOCKS_PER_SEC);

    // Matrix_t rslt = extractResultPart(&matrix);
    // saveMatrixToCSV(&rslt, "exit.csv");

    // // Memory free (very important ofc)
    // killMatrix(&rslt)
    killMatrix(&matrix);

    return 0;
}