#include "parseCSV.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX 1024

int CountColumn(const char *line)
{
    int count = 1;
    for (const char *p = line; *p != '\0'; p++)
    {
        if (*p == ',')
            count++;
    }
    return count;
}
int GetMatrixFromCSV(Matrix *matrix, char *file_path)
{
    FILE *file = fopen(file_path, "r");
    if (!file)
    {
        perror("Erreur d'ouverture du fichier");
        return 1;
    }

    char *buffer = malloc(LINE_MAX * sizeof(char));
    if (!buffer)
    {
        perror("Erreur d'allocation de mémoire");
        fclose(file);
        return 1;
    }

    size_t buffer_size = LINE_MAX;
    int line = 0, column = 0;

    while (fgets(buffer, buffer_size, file))
    {
        if (strlen(buffer) == buffer_size - 1 && buffer[buffer_size - 2] != '\n')
        {
            buffer_size *= 2;
            buffer = realloc(buffer, buffer_size);
            if (!buffer)
            {
                perror("Erreur de réallocation de mémoire");
                fclose(file);
                return 1;
            }
            fseek(file, -strlen(buffer), SEEK_CUR);
            continue;
        }

        if (line == 0)
        {
            column = CountColumn(buffer);
        }
        line++;
    }

    if (column == 0)
    {
        fprintf(stderr, "Erreur : le fichier CSV est vide ou mal formé.\n");
        free(buffer);
        fclose(file);
        return 1;
    }
    rewind(file);

    matrix->matrix = (double**)malloc(line * sizeof(double *));
    for (int i = 0; i < line; i++)
    {
        matrix->matrix[i] = malloc(column * sizeof(double));
    }
    matrix->height = line;
    matrix->lenght = column;

    line = 0;
    while (fgets(buffer, buffer_size, file))
    {
        char *token = strtok(buffer, ",");
        for (int col = 0; col < column && token != NULL; col++)
        {
            (matrix->matrix)[line][col] = atof(token);
            token = strtok(NULL, ",");
        }
        line++;
    }

    free(buffer);
    fclose(file);

    return 0;
}

int SetDataToCSV(Matrix matrix, char *dst_file)
{
    FILE *file = fopen(dst_file, "w");
    if (!file)
    {
        return 1;
    }

    for (int i = 0; i < matrix.height; i++)
    {
        for (int j = 0; j < matrix.lenght; j++)
        {
            fprintf(file, "%f", matrix.matrix[i][j]);
            if (j < matrix.lenght - 1)
            {
                fprintf(file, ",");
            }
        }
        fprintf(file, "\n");
    }
    fclose(file);
    return 0;
}
