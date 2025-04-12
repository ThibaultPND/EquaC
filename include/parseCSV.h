#if !defined(__PARSECSV_H__)
#define __PARSECSV_H__

#include "equ.h"

// Approximatly 170 line
#define LINE_MAX 1024
#define COL_MAX 1025

int GetMatrixFromCSV(Matrix *matrix, char *src_file);
int SetDataToCSV(Matrix matrix, char *dst_file);


#endif // __PARSECSV_H__
