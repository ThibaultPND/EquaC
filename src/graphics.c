#include <stdio.h>
#include <time.h>

#include "graphics.h"

#define BAR_WIDTH 50

void updateProgressBar(int current, int total) {
    static clock_t last_call = 0;
    clock_t now = clock();

    static int filled = 0;
    float ratio = (float) current / total;
    filled = (int) (ratio * BAR_WIDTH);

    if (now - last_call < 500)
        if (filled < (BAR_WIDTH - 1))
            return;

    last_call = now;

    printf("\r[");
    for (int i = 0; i < BAR_WIDTH; i++) {
        if (i <= filled)
            printf("=");
        else
            printf(" ");
    }
    printf("] %3d%%", (int) (ratio * 100));
    fflush(stdout);
    if ((int) ratio)
        printf("\n");
}