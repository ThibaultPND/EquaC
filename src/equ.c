#include "equ.h"
#include <stdio.h>

int printMatrix(double **matrix, int size)
{
    int i, j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            printf("%f   ", matrix[i][j]);
        }
        printf("|  %f\n", matrix[i][j]);
    }
    return 0;
}
int exchangeLines(double **matrix, int size, int lineA, int lineB)
{
    if (lineA > size || lineB > size && lineA <= 0 && lineB <= 0)
    {
        return 1; // ! ERROR
    }

    double *temp = *(matrix + lineA);
    *(matrix + lineA) = *(matrix + lineB);
    *(matrix + lineB) = temp;
    return 0;
}

int FindColumnPivot(double **matrix, int size, int column)
{
    if (column > size)
        return -1;
    int i = column;
    while (matrix[i][column] == 0)
        i++;
    return i;
}

void DivideLineByInteger(double *line, int size, int k)
{
    for (int i = 0; i < size + 1; i++)
    {
        line[i] /= (double)k;
    }
}

int SubstractLineByLineSpecial(double *line_to_substract, double *line, int size, int pivot)
{
    double k = line_to_substract[pivot] / line[pivot];
    for (int col = pivot; col < size + 1; col++)
    {
        line_to_substract[col] -= line[col] * k;
    }
    return 0;
}

int RemoveOtherColumnCoefiscent(double **matrix, int size, int column)
{
    int pivot = column;
    for (int line = 0; line < size; line++)
    {
        if (line == pivot)
            continue;
        SubstractLineByLineSpecial(matrix[line], matrix[pivot], size, pivot);
    }
}

int GaussPivot(double **matrix, int size)
{
    for (int column = 0; column < size; column++)
    {
        int pivot = FindColumnPivot(matrix, size, column);
        if (pivot == -1) // Pivot introuvable
            return -1;
        else if (pivot > column)
        {
            exchangeLines(matrix, size, pivot, column);
            pivot = column;
        }
        printf("Integer = %f\n", matrix[pivot][column]);
        DivideLineByInteger(matrix[pivot], size, matrix[pivot][column]);
        RemoveOtherColumnCoefiscent(matrix, size, column);
    }
    return 0;
}