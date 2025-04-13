#include <stdio.h>
#include <stdlib.h>

#include "algebra.h"
#include "io.h"
#include "matrix.h"
#include "types.h"

int main(int argc, char *argv[]) {
    // Exemple de code
    Matrix_t matrix;
    if (loadMatrixFromCSV(&matrix, "matrix.csv")) {
        printf("Csv error !\n");
        return 1;
    }
    printMatrix(&matrix);
    gaussJordanAlgorithm(&matrix);
    printf("\n");

    Matrix_t rslt = extractResultPart(&matrix);
    printMatrix(&rslt);

    // Memory free (very important ofc)
    freeMatrix(&rslt);
    freeMatrix(&matrix);

    return 0;
}