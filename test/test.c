//
// Created by Titouan LEBOCQ on 27/04/2023.
//

#include "test.h"

test_return_data chronometer(matrix_t (tested_function)(matrix_t, matrix_t), matrix_t matrix_a, matrix_t matrix_b) {
    clock_t start, end;
    test_return_data result = {0};

    start = clock();
    result.result = tested_function(matrix_a, matrix_b);
    end = clock();
    result.execution_time = end - start;

    return result;
}