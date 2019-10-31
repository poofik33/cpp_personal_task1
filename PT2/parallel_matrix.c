#include "matrix.h"

#include "input.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <wait.h>

bool input_matrix(int **matrix_p, size_t *width, size_t *heigth, FILE *stream) {
    if (!matrix_p)
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

bool side_matrix_reflection(int * const matrix, size_t width, size_t heigth) {
    if (!matrix || width <= 1 || heigth <= 1)
        return false;

    size_t size = width * heigth;
    FILE *fd = fopen("matrix.b", "w+b");

    if (fwrite(matrix, sizeof(int), size, fd) == 0) {
        fclose(fd);
        return false;
    }
    fclose(fd);

    int num_fd = open("matrix.b", O_RDWR, 0);
    if(num_fd < 0)
        return false;
    int* map_matrix = (int*)mmap(NULL, size * sizeof(int),
            PROT_WRITE|PROT_READ, MAP_SHARED|MAP_POPULATE ,num_fd, 0);
    if (map_matrix == MAP_FAILED) {
        close(num_fd);
        return false;
    }

    int num_proc = sysconf(_SC_NPROCESSORS_ONLN);
    size_t quadro_size = (heigth > width) ? width : heigth;
    num_proc = (num_proc > quadro_size / 2) ? quadro_size / 2 : num_proc;
    size_t chunk = quadro_size / num_proc / 2;
    for(int i = 0; i < num_proc; i++) {
        int bottom = heigth - chunk * i - 1;
        int top = heigth - chunk * (i + 1);
        if (i == num_proc - 1)
            top += (quadro_size / 2) % num_proc;
        pid_t pid = fork();
        if (!pid) {
            for (int j = bottom, diagonal_num = chunk * i; j >= top; j--, diagonal_num++) {
                for (int k = 0; k < quadro_size; k++) {
                    if (k != diagonal_num) {
                        int swap_bot_number = (2 * heigth - quadro_size - j - 1) * width + quadro_size - k - 1;
                        int swap_top_number = j * width + k;
                        swap(&map_matrix[swap_bot_number], &map_matrix[swap_top_number]);
                    }
                }
            }
            exit(EXIT_SUCCESS);
        } else if (pid == -1)
            exit(EXIT_FAILURE);
    }

    if (quadro_size % 2 == 1) {
        for (int j = 0; j < quadro_size / 2; j++) {
            int swap_number = (heigth - quadro_size / 2 - 1) * width + quadro_size - j - 1;
            swap(&map_matrix[(heigth - quadro_size / 2 - 1) * width + j], &map_matrix[swap_number]);
        }
    }

    for(int i = 0; i < num_proc; i++) {
        int status;
        if (wait(&status) < 0) {
            close(num_fd);
            return false;
        }
    }

    for(size_t i = 0; i < size; i++) {
        matrix[i] = map_matrix[i];
    }

    munmap(map_matrix, size * sizeof(int));
    close(num_fd);
    remove("matrix.b");
    return true;
}

void swap(int * const a, int * const b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
