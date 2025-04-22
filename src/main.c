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
    clock_t start = clock();
    if (loadMatrixFromCSV(&matrix, "equations_hard.csv")) {
        printf("Csv error !\n");
        return 1;
    }
    printf("Time spent : %ld clock units\n", (clock() - start));
    // shuffleSort(matrix.data, matrix.nrows);

    start = clock();
    gaussJordanAlgorithm(&matrix);
    printf("Time spent : %ld clock units\n", (clock() - start));

    // Matrix_t rslt = extractResultPart(&matrix);
    // saveMatrixToCSV(&rslt, "exit.csv");

    // // Memory free (very important ofc)
    // killMatrix(&rslt)
    killMatrix(&matrix);

    return 0;
}