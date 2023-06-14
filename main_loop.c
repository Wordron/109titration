/*
** EPITECH PROJECT, 2023
** 109_titration
** File description:
** main_loop
*/
#include <stdlib.h>
#include <stdio.h>
#include "include/109_titration.h"

int get_bigger_value(double **first_deriv, int size)
{
    double bigger = 0;
    int index = 0;
    int i = 0;

    for (i = 1; i != size - 3; i++) {
        if (first_deriv[i][1] > bigger) {
            bigger = first_deriv[i][1];
            index = i;
        }
    }
    printf("\nEquivalence point at %.1f ml\n\n", first_deriv[index][0]);
    return (index);
}

void get_smaller_value(double **first_deriv, int size)
{
    double smaller = first_deriv[0][1] * 100;
    double temp_2 = 0;
    double temp = 0;
    int index = 0;
    int i = 0;

    if (smaller < 0)
        smaller = smaller * (-1);
    for (i = 1; i != size - 1; i++) {
        if (first_deriv[i][1] < 0)
            temp_2 = first_deriv[i][1] * (-1);
        else
            temp_2 = first_deriv[i][1];
        temp = temp_2 * 100;
        if (temp < smaller) {
            smaller = temp;
            index = i;
        }
    }
    printf("\nEquivalence point at %.1f ml\n", first_deriv[index][0]);
}

double **main_loop(double **point_x_y, int size)
{
    double **first_derivative = malloc(sizeof(double *) * (size - 2));
    double **second_derivative = malloc(sizeof(double *) * (size - 4));
    double **second_derivative_estimated = NULL;
    double *a_b = NULL;
    int size_estimated = 0;
    int i_estimated = 0;
    int equivalence = 0;

    printf("Derivative:\n");
    for (int i = 1; i < size - 1; i++) {
        first_derivative[i] = get_derivative(point_x_y[i - 1], point_x_y[i], point_x_y[i + 1]);
        printf("%.1f ml -> %.2f\n", first_derivative[i][0], first_derivative[i][1]);
    }
    equivalence = get_bigger_value(first_derivative, size);
    if (equivalence < 1 || equivalence > size - 1)
        exit(0);
    printf("Second derivative:\n");
    for (int i = 2; i < size - 2; i++) {
        second_derivative[i] = get_derivative(first_derivative[i - 1], first_derivative[i], first_derivative[i + 1]);
        printf("%.1f ml -> %.2f\n", second_derivative[i][0], second_derivative[i][1]);
    }

    if (equivalence < 2 || equivalence > size - 2)
        exit(0);
    for (double i = first_derivative[equivalence - 1][0]; i < first_derivative[equivalence][0]; i = i + 0.1)
        size_estimated++;
    for (double i = first_derivative[equivalence][0]; i < first_derivative[equivalence + 1][0]; i = i + 0.1)
        size_estimated++;
    second_derivative_estimated = malloc(sizeof(double *) * size_estimated);
    for (int i = 0; i < size_estimated; i++)
        second_derivative_estimated[i] = malloc(sizeof(double) * 2);
    printf("\nSecond derivative estimated:\n");
    a_b = get_a_and_b(second_derivative[equivalence - 1][0], second_derivative[equivalence][0], second_derivative[equivalence - 1][1], second_derivative[equivalence][1]);
    for (double i = first_derivative[equivalence - 1][0]; i + 0.1 < first_derivative[equivalence][0]; i = i + 0.1) {
        second_derivative_estimated[i_estimated][0] = i;
        second_derivative_estimated[i_estimated][1] = get_y(a_b, i);
        i_estimated++;
    }
    a_b = get_a_and_b(second_derivative[equivalence][0], second_derivative[equivalence + 1][0], second_derivative[equivalence][1], second_derivative[equivalence + 1][1]);
    for (double i = first_derivative[equivalence][0]; i < first_derivative[equivalence + 1][0]; i = i + 0.1) {
        second_derivative_estimated[i_estimated][0] = i;
        second_derivative_estimated[i_estimated][1] = get_y(a_b, i);
        i_estimated++;
    }
    get_smaller_value(second_derivative_estimated, size_estimated);
    return (first_derivative);
}
