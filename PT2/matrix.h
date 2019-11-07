#ifndef PERSTASK2_MATRIX_H
#define PERSTASK2_MATRIX_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool input_matrix(int **matrix, size_t *width, size_t *heigth, FILE *stream);

bool serial_side_matrix_reflection(int * const matrix, size_t width, size_t heigth);

void swap(int * const a, int * const b);

#endif //PERSTASK2_MATRIX_H
