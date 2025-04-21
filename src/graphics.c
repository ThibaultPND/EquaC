#include <stdio.h>
#include <time.h>

#include "graphics.h"

void updateProgressBar(int current, int total) {
    static clock_t last_call = 0;
    clock_t now = clock();

    if (now - last_call < 500) {
        return;
    }

    last_call = now;
    int width = 50;
    float ratio = (float) current / total;
    int filled = (int) (ratio * width);

    printf("\r[");
    for (int i = 0; i < width; i++) {
        if (i <= filled)
            printf("=");
        else
            printf(" ");
    }
    printf("] %3d%%", (int) (ratio * 100));
    fflush(stdout);
}