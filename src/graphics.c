#include <stdio.h>
#include <math.h>

#include "graphics.h"

#define BAR_WIDTH 50
#define WEIGHT_EXPONENT 1.5 // Ajuste entre 1.3 et 1.7 selon les tests

double estimateRemainingTimeWeighted(clock_t startTime, int currentColumn, int totalColumns);

void updateProgressBar(int current, int total, clock_t start) {
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
    printf(" %.0lf secondes", estimateRemainingTimeWeighted(start, current, total));
    fflush(stdout);
    if ((int) ratio)
        printf("\n");
}

double estimateRemainingTimeWeighted(clock_t startTime, int currentColumn, int totalColumns) {
    double timeSpent = (double) (clock() - startTime) / CLOCKS_PER_SEC;

    double totalWork = 0, workDone = 0;
    for (int i = 0; i < totalColumns; i++)
        totalWork += pow((double) (totalColumns - i), WEIGHT_EXPONENT);
    for (int i = 0; i < currentColumn; i++)
        workDone += pow((double) (totalColumns - i), WEIGHT_EXPONENT);

    if (workDone == 0)
        return -1.0;

    double proportionRemaining = (totalWork - workDone) / workDone;
    return timeSpent * proportionRemaining;
}
