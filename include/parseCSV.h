#if !defined(__PARSECSV_H__)
#define __PARSECSV_H__

// Approximatly 170 line
#define LINE_MAX 1024
#define COL_MAX 1025

int GetDataFromCSV(double ***matrix, int *size, char *src_file);
int SetDataToCSV(double **matrix,int rows, int cols, char *dst_file);


#endif // __PARSECSV_H__
