/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** main
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include "include/109_titration.h"

static int check_if_file_empty(char *file)
{
    struct stat check;
    int result = 0;

    result = stat(file, &check);
    if (result < 0)
        return (84);
    else {
        if (check.st_size <= 1)
            return (84);
    }
    return (0);
}

int main(int ac, char **av)
{
    struct stat st;
    double **numbers = NULL;

    if (ac != 2)
        return (84);
    if (access(av[1], F_OK) != 0)
        return (84);
    if (check_if_file_empty(av[1]) != 0)
        return (84);
    numbers = start_parsing(av[1]);
    for (int i = 0; i < get_nb(av[1]) / 2; i++) {
        if (numbers[i][1] < 0 || numbers[i][1] > 14)
            return (84);
        if (numbers[i][0] < 0)
            return (84);
    }
    if (get_nb(av[1]) / 2 < 5)
        return (84);
    main_loop(numbers, get_nb(av[1]) / 2);
}