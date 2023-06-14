/*
** EPITECH PROJECT, 2023
** derivative.c
** File description:
** derivative
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

double *get_derivative(double *a, double *b, double *c)
{
    double *final = malloc(sizeof(double) * 2);
    double back_rate = 0;
    double forw_rate = 0;
    double weighted_rate = 0;

    final[0] = b[0];
    if (((b[0] - a[0]) < 0.01 && (b[0] - a[0]) > -0.01) || ((c[0] - b[0]) < 0.01 && (c[0] - b[0]) > -0.01) || ((c[0] - a[0]) < 0.01 && (c[0] - a[0]) > -0.01))
        exit(84);
    back_rate = ((b[1] - a[1]) / (b[0] - a[0]));
    forw_rate = ((c[1] - b[1]) / (c[0] - b[0]));
    weighted_rate = (c[0] - b[0]) * back_rate + (b[0] - a[0]) * forw_rate;
    weighted_rate = weighted_rate / (c[0] - a[0]);
    final[1] = weighted_rate;
    return (final);
}

double *get_a_and_b(double Xa,double Xb, double Ya, double Yb)
{
    double a = 0;
    double b = 0;
    double *a_b = malloc(sizeof(double) * 2);

    if ((Xa - Xb) < 0.01 && (Xa - Xb) > -0.01)
        exit(84);
    a = ((Ya - Yb) / (Xa - Xb));
    b = Yb - (a * Xb);
    a_b[0] = a;
    a_b[1] = b;
    return (a_b);
}

double get_y(double *array, double x)
{
    double y = 0;

    y = (array[0] * x) + array[1];
    printf("%.1f ml -> %.2f\n", x, y);
    return (y);
}
