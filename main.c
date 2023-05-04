#include <assert.h>

#include "test/test.h"
#include "matrix/matrix.h"

int main() {
    int size = 3000;
    matrix_t matrix_a = matrix_create_random(size, size);
    matrix_t matrix_b = matrix_create_random(size, size);

    test_return_data threaded = chronometer(multiply_matrix_threaded, matrix_a, matrix_b);
    printf("Execution time not threaded:\t%f\tms\n", threaded.execution_time);
    if (size <= 10000) {
        test_return_data not_threaded = chronometer(multiply_matrix, matrix_a, matrix_b);
        printf("Execution time threaded:\t%f\tms\n", not_threaded.execution_time);
        assert(are_equal(not_threaded.result, threaded.result));
    }

    return 0;
}
