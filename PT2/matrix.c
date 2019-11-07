#include "matrix.h"

#include "input.h"

bool input_matrix(int **matrix_p, size_t *width, size_t *heigth, FILE *stream) {
    if (!matrix_p || !width || !heigth)
        return false;

    if (stream == stdin)
        printf("Введите ширину матрицы\n");
    *width = input_number(stream);
    if (stream == stdin)
        printf("Введите высоту матрицы\n");
    *heigth = input_number(stream);

    int *new_matrix = (int*)malloc(*heigth * *width * sizeof(int));
    if (!new_matrix)
        return false;
    *matrix_p = new_matrix;

    for (size_t i = 0; i < *heigth; i++) {
        for (size_t j = 0; j < *width; j++) {
            new_matrix[*width * i + j] = input_number(stream);
        }
    }

    return true;
}

bool serial_side_matrix_reflection(int * const matrix, size_t width, size_t heigth) {
    if (!matrix || width <= 1 || heigth <= 1)
        return false;

    size_t quadro_size = (heigth > width) ? width : heigth;

    for (int i = heigth - 1, diagonal_num = 0; i >= heigth - quadro_size / 2; i--, diagonal_num++) {
        for (int j = 0; j < quadro_size; j++) {
            if (j != diagonal_num) {
                int swap_number = (2 * heigth - quadro_size - i -1) * width + quadro_size - j - 1;
                swap(&matrix[i * width + j], &matrix[swap_number]);
            }
        }
    }

    if (quadro_size % 2 == 1)
        for (int j = 0; j < quadro_size / 2; j++) {
            int swap_number = (heigth - quadro_size / 2 - 1) * width + quadro_size - j - 1;
            swap(&matrix[(heigth - quadro_size / 2 - 1) * width + j], &matrix[swap_number]);
        }

    return true;
}

void swap(int * const a, int * const b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
