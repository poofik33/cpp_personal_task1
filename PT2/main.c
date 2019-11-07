/*
 ИЗ2 посвящено приобретению навыков системной разработки на C и работе с внешними библиотеками.
 В качестве результата ИЗ2 ожидается:
* грамотное разбиение проекта на файлы;
* наличие двух реализаций – последовательной и параллельной, оформленных в виде статической и динамической библиотеки,
* а также тестирующей программы, которая будет сравнивать на разных входных данных результаты обеих реализаций
 между собой;
* максимальная утилизация ресурсов процессора при параллельной обработке данных путём использования нескольких
 процессов или потоков;
* продуманные структуры данных в целях экономии оперативной памяти;
* реализация алгоритмов, эффективно взаимодействующих с кэш-памятью.

 В вашем распоряжении — матрица размером 10 000 x 5000 чисел. Составьте наивный алгоритм зеркального отображения матрицы
 относительно побочной диагонали, а затем реализуйте параллельный алгоритм решения этой задачи с использованием
 нескольких процессов с учетом оптимизации работы с кэш-памятью.
 */
#include "matrix.h"
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main(int argc, char *argv[]) {
    int *matrix = NULL;
    size_t width = 0, height = 0;
    bool success = input_matrix(&matrix, &width, &height, stdin);
    if (!success)
        return EXIT_FAILURE;
    int *copy_matrix = (int*)malloc(width * height * sizeof(int));
    memcpy(copy_matrix, matrix, width * height * sizeof(int));

    clock_t begin = clock();
    success = serial_side_matrix_reflection(matrix, width, height);
    if (!success) {
        free(matrix);
        free(copy_matrix);
        return EXIT_FAILURE;
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Single process algorithm working time: %f\n", time_spent);


    free(matrix);

    void *library = dlopen("libparallel_work_with_matrix.so", RTLD_LAZY);
    if (!library) {
        free(copy_matrix);
        return EXIT_FAILURE;
    }

    bool(*parallel_reflection)(int * const m, size_t w, size_t h) = dlsym(library, "parallel_side_matrix_reflection");
    if (!parallel_reflection) {
        free(copy_matrix);
        return EXIT_FAILURE;
    }
    begin = clock();
    success = parallel_reflection(copy_matrix, width, height);
    if (!success) {
        free(copy_matrix);
        return EXIT_FAILURE;
    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Multi process algorithm working time: %f\n", time_spent);

    free(copy_matrix);
    return EXIT_SUCCESS;
}


