#if !defined(__MATRIX_H__)
#define __MATRIX_H__

#include "types.h"

Matrix_t *createMatrix(int rows, int cols, Matrix_t *src);
void killMatrix(Matrix_t *matrix);

Matrix_t *copyMatrix(Matrix_t *src, Matrix_t *dst);

void printMatrix(const Matrix_t *matrix);

#endif // __MATRIX_H__
