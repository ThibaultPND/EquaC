#if !defined(__EQU_H__)
#define __EQU_H__

// Math things
int exchangeLines(double **matrix, int size, int lineA, int lineB);
int GaussPivot(double **matrix, int size);
int transposeMatrix(double **dst_matrix, double **src_matrix, int rows, int cols);

// Utils
int printMatrix(double **matrix, int size);
int AugmentedMatrixCopy(double **matrix_dst, double **matrix_src, int size);
double **GetMatrixFromAugmentedMatrix(double **matrix, int size);
double **GetResultFromAugmentedMatrix(double **matrix, int size);

// Free
int FreeMatrix(double **augmented_matrix, int size);

#endif // __EQU_H__
