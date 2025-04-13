#if !defined(__TYPES_H__)
#define __TYPES_H__

// #define Matrix Matrix_t

typedef struct {
    double **data;
    int nrows;
    int ncols;
} Matrix_t;

#endif // __TYPES_H__
