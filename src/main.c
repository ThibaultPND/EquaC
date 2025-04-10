#include <stdio.h>
#include <stdlib.h>
#include "equ.h"
#include "parseCSV.h"

int main(int argc, char *argv[])
{
    /*Je Crée une matrice un peu "aléatoire"*/ 
    // TODO Deplacer dans une fonction
    
    double **matrix = NULL;
    int size;
    SetCsvDataToDoubleMatrix(&matrix, &size, "matrix.csv");
    
    printMatrix(matrix, size);
    if(GaussPivot(matrix,size))
        printf("Error !?\n");
    printf("\n");
    printMatrix(matrix, size);
    
    for (int i = 0; i < 3; ++i)
        free(*(matrix + i));
    free(matrix);

    return 0;
}