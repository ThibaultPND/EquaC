#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "matrix.h"
#include "graphics.h"

#define LINE_MAX 1024

// Prototypes
int countColumn(FILE *file);
int countFileLines(FILE *file);
int my_getline(char **lineptr, size_t *n, FILE *file); // getline() est dispo que sur UNIX : (

// Functions

int loadMatrixFromCSV(Matrix_t *matrix, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier csv\n");
        return 1;
    }

    matrix->nrows = countFileLines(file);
    printf(" rows  = %d\n\n", matrix->nrows);
    rewind(file);
    matrix->ncols = countColumn(file);
    rewind(file);

    matrix->data = (double **) malloc(matrix->nrows * sizeof(double *));
    if (!matrix->data) {
        fclose(file);
        return 1;
    }

    // Remplir la matrice en lisant les lignes du fichiers.
    char *buffer = NULL;
    int line = 0;
    size_t size;
    printf("Chargement de la matrice depuis le fichier CSV :\n");
    while (my_getline(&buffer, &size, file) != -1) {
        updateProgressBar(line, matrix->nrows);
        matrix->data[line] = (double *) malloc(matrix->ncols * sizeof(double));
        char *token = strtok(buffer, ",");
        for (int col = 0; col < matrix->ncols && token != NULL; col++) {
            (matrix->data)[line][col] = atof(token);
            token = strtok(NULL, ",");
        }
        line++;
    }
    free(buffer);
    fclose(file);
    return 0;
}
int saveMatrixToCSV(const Matrix_t *matrix, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        return 1;
    }

    for (int i = 0; i < matrix->nrows; i++) {
        for (int j = 0; j < matrix->ncols; j++) {
            fprintf(file, "%.3f", matrix->data[i][j]);
            if (j < matrix->ncols - 1) {
                fprintf(file, ",");
            }
        }
        fprintf(file, "\n");
    }
    fclose(file);
    return 0;
}

int countColumn(FILE *file) {
    char *buffer = NULL;
    size_t buf_size;
    my_getline(&buffer, &buf_size, file);

    int count = 0;
    for (const char *p = buffer; *p != '\0'; p++) {
        if (*p == ',')
            count++;
    }
    free(buffer);
    return count;
}

int my_getline(char **lineptr, size_t *n, FILE *stream) {
    if (lineptr == NULL || n == NULL || stream == NULL)
        return -1;

    size_t pos = 0;
    int c;

    if (*lineptr == NULL || *n == 0) {
        *n = 128;
        *lineptr = malloc(*n);
        if (*lineptr == NULL)
            return -1;
    }

    while ((c = fgetc(stream)) != EOF) {
        if (pos + 1 >= *n) {
            *n *= 2;
            char *new_ptr = realloc(*lineptr, *n);
            if (!new_ptr)
                return -1;
            *lineptr = new_ptr;
        }

        (*lineptr)[pos++] = c;
        if (c == '\n')
            break;
    }

    if (pos == 0 && c == EOF)
        return -1;

    (*lineptr)[pos] = '\0';
    // if ((*lineptr)[pos - 1] == '\n') {
    //     (*lineptr)[pos - 1] = '\0';
    // }

    return pos;
}

int countFileLines(FILE *file) {

    int i;
    int clu;
    int nrow = 0;
    char buffer[LINE_MAX];
    if (file) {
        rewind(file);
        while ((clu = fread(buffer, sizeof(char), LINE_MAX, file))) {
            for (i = 0; i < clu; i++)
                if (buffer[i] == '\n')
                    nrow++;
        }
    }
    return nrow;
}