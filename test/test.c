//
// Created by Titouan LEBOCQ on 27/04/2023.
//

#include "test.h"

void test_non_threaded(matrix_t matrix_a, matrix_t matrix_b) {
    clock_t start, end;
    matrix_t result;

    printf("Multipling matrixes (non threaded) \n");
    printf("\n");

    start = clock();
    result = multiply_matrix(matrix_a, matrix_b);
    end = clock();

    if (matrix_a.rows < 10) {
        printf("Matrix C:\n");
        print_matrix(result);
    }

    printf("ended in %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    printf("\n");
}

void test_threaded(matrix_t matrix_a, matrix_t matrix_b) {
    clock_t start, end;
    matrix_t result;

    printf("Multipling matrixes (threaded) \n");
    printf("\n");

    start = clock();
    result = multiply_matrix_threaded(matrix_a, matrix_b);
    end = clock();

    if (matrix_a.rows < 10) {
        printf("Matrix D:\n");
        print_matrix(result);
    }

    printf("ended in %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}