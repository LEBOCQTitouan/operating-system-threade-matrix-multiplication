//
// Created by Titouan LEBOCQ on 27/04/2023.
//

#ifndef OPERATING_SYSTEM_THREADED_MATRIX_MULTIPLICATION_MATRIX_H
#define OPERATING_SYSTEM_THREADED_MATRIX_MULTIPLICATION_MATRIX_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <math.h>
#include <pthread.h>

#if defined(__APPLE__)
#include <sys/sysctl.h>
#elif defined(__linux__)
#include <unistd.h>
#elif defined(_WIN32)
#include <Windows.h>
#endif

/**
 * Matrix structure
 */
typedef struct {
    double **data;  // 2D array of doubles
    int rows;       // number of rows
    int cols;       // number of columns
} matrix_t;

/**
 * Matrix multiplication arguments structure for threads
 */
typedef struct {
    int start_index;
    int end_index;
    matrix_t *matrix_a;          //
    matrix_t *matrix_b;          //
    matrix_t *result;           // the result matrix
} thread_args_t;

enum processing_position_main {
    TOP,
    BOTTOM
};

enum processing_position_sub {
    LEFT,
    RIGHT
};

/**
 * Function used by a thread to multiply a part of two matrices
 * @param args the processing arguments for the thread @see pos_args_t
 */
void *thread_multiplication_routine(void *args);

/**
 * Function creating an empty matrix
 * @param rows the number of rows
 * @param cols the number of columns
 * @return the created matrix
 */
matrix_t matrix_create_empty(int rows, int cols);

/**
 * Function creating a random matrix
 * @param rows the number of rows
 * @param cols the number of columns
 * @return the created matrix
 */
matrix_t matrix_create_random(int rows, int cols);

/**
 * Function used to multiply two matrices
 * @param matrix_a
 * @param matrix_b
 * @return the result of the multiplication
 */
matrix_t multiply_matrix(matrix_t matrix_a, matrix_t matrix_b);

/**
 * Function used to multiply two matrices using threads
 * @param matrix_a
 * @param matrix_b
 * @return the result of the multiplication
 */
matrix_t multiply_matrix_threaded(matrix_t matrix_a, matrix_t matrix_b);

/**
 * Function used to print a matrix
 * @param matrix the matrix to print
 */
void print_matrix(matrix_t matrix);

bool are_equal(matrix_t matrix_a, matrix_t matrix_b);

int get_number_of_procs();

#endif //OPERATING_SYSTEM_THREADED_MATRIX_MULTIPLICATION_MATRIX_H
