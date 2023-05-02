#include <stdio.h>

#include "test/test.h"
#include "matrix/matrix.h"

int main() {
    int size = 3;
    matrix_t matrix_a = matrix_create_random(size, size);
    matrix_t matrix_b = matrix_create_random(size, size);

    if (size < 10) {
        printf("Matrix A:\n");
        print_matrix(matrix_a);
        printf("Matrix B:\n");
        print_matrix(matrix_b);
    }

    test_non_threaded(matrix_a, matrix_b);
    test_threaded(matrix_a, matrix_b);

    return 0;
}
