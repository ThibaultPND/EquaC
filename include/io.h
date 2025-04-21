#if !defined(__IO_H__)
#define __IO_H__

#include "types.h"

int loadMatrixFromCSV(Matrix_t *matrix, const char *filename);
int saveMatrixToCSV(const Matrix_t *matrix, const char *filename);
int readTest(Matrix_t *matrix, const char *filename);
#endif // __IO_H__
