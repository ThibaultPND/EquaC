#if !defined(__EQU_H__)
#define __EQU_H__

typedef struct
{
    double **matrix;
    int height; // Number of lines
    int lenght; // Number of rows
} Matrix;

// Math things
int exchangeLines(Matrix matrix, int lineA, int lineB);
int GaussPivot(Matrix matrix);
int transposeMatrix(Matrix dst_matrix, Matrix src_matrix);

// Utils
Matrix CreateMatrix(Matrix *src, int nrows, int ncols);
int printMatrix(const Matrix matrix);
int MatrixCopy(Matrix *dst_matrix, Matrix *src_matrix);
Matrix GetMatrixFromAugmentedMatrix(const Matrix *m);
Matrix GetResultFromAugmentedMatrix(const Matrix *m);

// Free
int FreeMatrix(Matrix *matrix);

#endif // __EQU_H__
