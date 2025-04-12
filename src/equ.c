#include "equ.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int printMatrix(Matrix matrix)
{
    int i, j;
    for (i = 0; i < matrix.height; i++)
    {
        for (j = 0; j < matrix.lenght - 1; j++)
        {
            printf("%f   ", matrix.matrix[i][j]);
        }
        printf("|  %f\n", matrix.matrix[i][j]);
    }
    return 0;
}
int exchangeLines(Matrix m, int lineA, int lineB)
{
    if (lineA > m.height || lineB > m.height || lineA <= 0 || lineB <= 0)
    {
        return 1; // ! ERROR
    }

    double *temp = m.matrix[lineA];
    m.matrix[lineA] = m.matrix[lineB];
    m.matrix[lineB] = temp;
    return 0;
}
int FindColumnPivot(Matrix matrix, int column)
{
    if (column > matrix.lenght - 1)
        return -1;
    int i = column;
    while (matrix.matrix[i][column] == 0)
        i++;
    return i;
}
void DivideLineByDouble(double *line, int lenght, double k)
{
    for (int i = 0; i < lenght; i++)
    {
        line[i] /= k;
    }
}
int SubstractLineByLineSpecial(double *line_to_substract, double *line, int lenght, int pivot)
{
    double k = line_to_substract[pivot] / line[pivot];
    for (int col = pivot; col < lenght; col++)
    {
        line_to_substract[col] -= line[col] * k;
    }
    return 0;
}
Matrix CreateMatrix(Matrix *src, int nrows, int ncols)
{
    Matrix matrix = {NULL, nrows, ncols};
    matrix.matrix = (double **)malloc(nrows * sizeof(double *));
    for (int i = 0; i < nrows; i++)
    {
        matrix.matrix[i] = (double *)malloc(ncols * sizeof(double));
    }

    if (src)
    {
        MatrixCopy(&matrix, src);
    }

    return matrix;
}
int RemoveOtherColumnCoefiscent(Matrix m, int column)
{
    int pivot = column;
    for (int line = 0; line < m.height; line++)
    {
        if (line == pivot)
            continue;
        SubstractLineByLineSpecial(m.matrix[line], m.matrix[pivot], m.lenght, pivot);
    }
    return 0;
}
Matrix VoidMatrix()
{
    Matrix matrix = {NULL, 0, 0};
    return matrix;
}
int GaussPivot(Matrix m)
{
    for (int column = 0; column < m.lenght - 1; column++)
    {
        int pivot = FindColumnPivot(m, column);
        if (pivot == -1) // Pivot introuvable
            return 1;
        else if (pivot > column)
        {
            ;
            exchangeLines(m, pivot, column);
            pivot = column;
        }
        DivideLineByDouble(m.matrix[pivot], m.lenght, m.matrix[pivot][column]);
        RemoveOtherColumnCoefiscent(m, column);
    }
    return 0;
}
int MatrixCopy(Matrix *dst_matrix, Matrix *src_matrix)
{
    if (dst_matrix->height != src_matrix->height || dst_matrix->lenght != src_matrix->lenght)
        return 1;

    for (int i = 0; i < src_matrix->height; ++i)
    {
        memcpy(*(dst_matrix->matrix + i), *(src_matrix->matrix + i), (src_matrix->lenght) * sizeof(double));
    }
    return 0;
}
Matrix GetMatrixFromAugmentedMatrix(const Matrix *m)
{
    Matrix matrix = CreateMatrix(NULL, m->height, m->lenght - 1);
    for (int i = 0; i < matrix.height; i++)
    {
        memcpy(matrix.matrix[i], m->matrix[i], matrix.lenght * sizeof(double));
    }
    return matrix;
}
Matrix GetResultFromAugmentedMatrix(const Matrix *m)
{
    Matrix returned_matrix = CreateMatrix(NULL, m->height, 1);
    for (int i = 0; i < m->height; i++)
    {
        returned_matrix.matrix[i][0] = m->matrix[i][m->lenght - 1];
    }

    return returned_matrix;
}
int FreeMatrix(Matrix *matrix)
{
    if (matrix == NULL || matrix->matrix == NULL)
        return -1;

    for (int i = 0; i < matrix->height; i++)
    {
        free(matrix->matrix[i]);
        matrix->matrix[i] = NULL;
    }
    free(matrix->matrix);
    matrix->matrix = NULL;

    return 0;
}
int transposeMatrix(Matrix dst_matrix, Matrix src_matrix)
{
    if (dst_matrix.matrix == NULL)
        return 1;
    for (int i = 0; i < src_matrix.height; i++)
        for (int j = 0; j < src_matrix.lenght; j++)
            dst_matrix.matrix[j][i] = src_matrix.matrix[i][j];
    return 0;
}