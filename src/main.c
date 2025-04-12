#include <stdio.h>
#include <stdlib.h>
#include "equ.h"
#include "parseCSV.h"

int main(int argc, char *argv[])
{
    // Exemple de code
    Matrix matrix;
    if (GetMatrixFromCSV(&matrix, "matrix.csv")){
        printf("Csv error !\n");
        return 1;
    }
    printMatrix(matrix);
    GaussPivot(matrix);
    printf("\n");
    printMatrix(matrix);
    
    
    // Memory free (very important ofc)
    FreeMatrix(&matrix);

    return 0;
}