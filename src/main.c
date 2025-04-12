#include <stdio.h>
#include <stdlib.h>
#include "equ.h"
#include "parseCSV.h"

int main(int argc, char *argv[])
{
    // Exemple de code
    double **matrix = NULL;
    int size = 0;
    if (GetDataFromCSV(&matrix, &size, "matrix.csv"))
    {
        printf("Csv error !\n");
        return 1;
    }
    if (GaussPivot(matrix, size))
    {
        printf("GaussPivot Error !\n");
        for (int i = 0; i < 3; ++i)
            free(*(matrix + i));
        free(matrix);
        return 1;
    }

    double **result = GetResultFromAugmentedMatrix(matrix, size);
    SetDataToCSV(result, size, 1, "exit.csv");

    // Memory free (very important ofc)
    FreeMatrix(matrix, size);
    FreeMatrix(result, size);

    return 0;
}