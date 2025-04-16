#include <stdlib.h>

#include "sort.h"

void shuffleSort(double **list, int lenght) {
    for (int i = lenght - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        double *temp = list[i];
        list[i] = list[j];
        list[j] = temp;
    }
}