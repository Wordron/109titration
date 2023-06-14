/*
** EPITECH PROJECT, 2023
** 109_titration
** File description:
** parsing
*/
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "include/109_titration.h"

static int get_nb_numbers(char *buffer)
{
    int nb_number = 0;

    for (int i = 0; buffer[i] != 0; i++) {
        if (buffer[i] == ';')
            nb_number = nb_number + 2;
    }
    return (nb_number);
}

int get_nb(char *filepath)
{
    struct stat stock;
    int error = stat(filepath, &stock);
    char *buffer = malloc(sizeof(char) * (stock.st_size + 1));
    int fd = open(filepath, O_RDONLY);

    if (fd == -1)
        exit(84);
    read(fd, buffer, stock.st_size);
    close(fd);
    return (get_nb_numbers(buffer));
}

static double **get_numbers(char *buffer)
{
    int nb_numbers = get_nb_numbers(buffer);
    double **base_numbers = malloc(sizeof(double *) * nb_numbers);
    char **arr = separate_str(buffer, ";\n");
    int j = 0;

    for (int i = 0; i < nb_numbers; i++)
        base_numbers[i] = malloc(sizeof(double) * 2);
    for (int i = 0; arr[i] != NULL; i = i + 2, j++) {
        base_numbers[j][0] = atof(arr[i]);
        base_numbers[j][1] = atof(arr[i + 1]);
    }
    return (base_numbers);
}

static int check_validity(char *buffer)
{
    int nb_separators = 0;

    for (int i = 0; buffer[i] != 0; i++) {
        if ((buffer[i] < '0' || buffer[i] > '9') && buffer[i] != '.' && buffer[i] != ';'&& buffer[i] != '\n')
            return (84);
    }
    for (int i = 0; buffer[i] != 0; i++, nb_separators = 0) {
        while (buffer[i] != '\n' && buffer[i] != '\0') {
            if (buffer[i] == ';') {
                nb_separators++;
                if (buffer[i + 1] < '0' || buffer[i + 1] > '9')
                    return (84);
            }
            i++;
        }
        if (nb_separators != 1)
            return (84);
    }
    return (0);
}

double **start_parsing(char *filepath)
{
    struct stat stock;
    int error = stat(filepath, &stock);
    char *buffer = malloc(sizeof(char) * (stock.st_size + 1));
    int fd = open(filepath, O_RDONLY);

    if (fd == -1)
        exit(84);
    read(fd, buffer, stock.st_size);
    close(fd);
    if (check_validity(buffer) != 0)
        exit(84);
    return (get_numbers(buffer));
}
