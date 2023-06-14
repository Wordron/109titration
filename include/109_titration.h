/*
** EPITECH PROJECT, 2023
** 109_titration
** File description:
** 109_titration
*/

#ifndef _TITRATION_H_
    #define _TITRATION_H_

    char **separate_str(char *argv, char *delim);
    double **start_parsing(char *filepath);
    double **start_parsing(char *filepath);
    int get_nb(char *filepath);

    double *get_derivative(double *a, double *b, double *c);
    double **main_loop(double **point_x_y, int size);
    double get_y(double *array, double x);
    double *get_a_and_b(double Xa,double Xb, double Ya, double Yb);

#endif /* !_TITRATION_H_ */
