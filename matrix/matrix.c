//
// Created by Titouan LEBOCQ on 27/04/2023.
//

#include "matrix.h"

void *thread_multiplication_routine(void *args) {
    thread_args_t *thread_data_holder = (thread_args_t *) args;
    for (int i = thread_data_holder->positional_args.start_row; i < thread_data_holder->positional_args.end_row; ++i) {
        for (int j = thread_data_holder->positional_args.start_col; j < thread_data_holder->positional_args.end_col; ++j) {
            for (int k = 0; k < thread_data_holder->matrix_a.cols; ++k) {
                thread_data_holder->result->data[i][j] += thread_data_holder->matrix_a.data[i][k] * thread_data_holder->matrix_b.data[k][j];
            }
        }
    }
    return NULL;
}

matrix_t multiply_matrix(matrix_t matrix_a, matrix_t matrix_b) {
    matrix_t result = matrix_create_empty(matrix_a.rows, matrix_b.cols);
    for (int i = 0; i < matrix_a.rows; ++i) {
        for (int j = 0; j < matrix_b.cols; ++j) {
            for (int k = 0; k < matrix_a.cols; ++k) {
                result.data[i][j] += matrix_a.data[i][k] * matrix_b.data[k][j];
            }
        }
    }
    return result;
}

matrix_t multiply_matrix_threaded(matrix_t matrix_a, matrix_t matrix_b) {
    matrix_t result = matrix_create_empty(matrix_a.rows, matrix_b.cols);
    pthread_t threads[4];

    // Create the positional arguments for the threads
    pos_args_t top_left_args = {0, matrix_a.rows / 2, 0, matrix_b.cols / 2};
    pos_args_t top_right_args = {0, matrix_a.rows / 2, matrix_b.cols / 2, matrix_b.cols};
    pos_args_t bottom_left_args = {matrix_a.rows / 2, matrix_a.rows, 0, matrix_b.cols / 2};
    pos_args_t bottom_right_args = {matrix_a.rows / 2, matrix_a.rows, matrix_b.cols / 2, matrix_b.cols};

    // Create the processing arguments for the threads
    thread_args_t top_left_thread_args = {top_left_args, matrix_a, matrix_b, &result};
    thread_args_t top_right_thread_args = {top_right_args, matrix_a, matrix_b, &result};
    thread_args_t bottom_left_thread_args = {bottom_left_args, matrix_a, matrix_b, &result};
    thread_args_t bottom_right_thread_args = {bottom_right_args, matrix_a, matrix_b, &result};

    // Create the threads
    pthread_create(&threads[0], NULL, thread_multiplication_routine, &top_left_thread_args);
    pthread_create(&threads[1], NULL, thread_multiplication_routine, &top_right_thread_args);
    pthread_create(&threads[2], NULL, thread_multiplication_routine, &bottom_left_thread_args);
    pthread_create(&threads[3], NULL, thread_multiplication_routine, &bottom_right_thread_args);

    // Wait for the threads to finish
    for (int i = 0; i < 4; ++i) {
        pthread_join(threads[i], NULL);
    }

    return result;
}

matrix_t matrix_create_empty(int rows, int cols) {
    matrix_t matrix = {0};
    matrix.rows = rows;
    matrix.cols = cols;
    matrix.data = calloc(rows, sizeof(double*));
    for (int i = 0; i < rows; ++i) {
        matrix.data[i] = calloc(cols, sizeof(double));
    }
    return matrix;
}

matrix_t matrix_create_random(int rows, int cols) {
    matrix_t matrix = matrix_create_empty(rows, cols);
    for (int i = 0; i < matrix.rows; ++i) {
        for (int j = 0; j < matrix.cols; ++j) {
            matrix.data[i][j] = (double)(rand() % 10);
        }
    }
    return matrix;
}

void print_matrix(matrix_t matrix) {
    for (int i = 0; i < matrix.rows; ++i) {
        for (int j = 0; j < matrix.cols; ++j) {
            printf("%f\t", matrix.data[i][j]);
        }
        printf("\n");
    }
}
