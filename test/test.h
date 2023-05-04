//
// Created by Titouan LEBOCQ on 27/04/2023.
//

#ifndef OPERATING_SYSTEM_THREADED_MATRIX_MULTIPLICATION_TEST_H
#define OPERATING_SYSTEM_THREADED_MATRIX_MULTIPLICATION_TEST_H

#include "../matrix/matrix.h"
#include <stdio.h>
#include <time.h>

typedef struct {
    double execution_time;
    matrix_t result;
} test_return_data;

test_return_data chronometer(matrix_t (tested_function)(matrix_t, matrix_t), matrix_t matrix_a, matrix_t matrix_b);

#endif //OPERATING_SYSTEM_THREADED_MATRIX_MULTIPLICATION_TEST_H
