#if !defined(__ALGEBRA_H__)
#define __ALGEBRA_H__

#include "types.h"

int gaussJordanAlgorithm(Matrix_t *matrix);
int exchangeRows(Matrix_t *matrix, int row1, int row2);
int transposeMatrix(Matrix_t *matrix);

Matrix_t *generateAugmentedMatrix(int nrows, short complexity);
Matrix_t *extractMatrixPart(Matrix_t *matrix);
Matrix_t *extractResultPart(Matrix_t *matrix);

#endif // __ALGEBRA_H__
