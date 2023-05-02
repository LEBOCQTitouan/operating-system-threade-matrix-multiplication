//
// Created by Titouan LEBOCQ on 27/04/2023.
//

#ifndef OPERATING_SYSTEM_THREADED_MATRIX_MULTIPLICATION_TEST_H
#define OPERATING_SYSTEM_THREADED_MATRIX_MULTIPLICATION_TEST_H

#include "../matrix/matrix.h"
#include <stdio.h>
#include <time.h>

void test_non_threaded(matrix_t matrix_a, matrix_t matrix_b);
void test_threaded(matrix_t matrix_a, matrix_t matrix_b);

#endif //OPERATING_SYSTEM_THREADED_MATRIX_MULTIPLICATION_TEST_H
