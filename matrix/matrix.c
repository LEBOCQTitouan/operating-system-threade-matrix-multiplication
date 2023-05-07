//
// Created by Titouan LEBOCQ on 27/04/2023.
//

#include "matrix.h"

void *thread_multiplication_routine(void *args) {
    thread_args_t *thread_data_holder = (thread_args_t *) args;
    // extracting data from thread args
    matrix_t *matrix_a = thread_data_holder->matrix_a;
    matrix_t *matrix_b = thread_data_holder->matrix_b;
    matrix_t *result = thread_data_holder->result;

    for (int row_a = thread_data_holder->start_index; row_a < thread_data_holder->end_index + 1; ++row_a) {
        for (int col_b = 0; col_b < matrix_b->cols; ++col_b) {
            for (int col_a = 0; col_a < matrix_a->cols; ++col_a) {
                result->data[row_a][col_b] += matrix_a->data[row_a][col_a] * matrix_b->data[col_a][col_b];
            }
        }
    }

    return NULL;
}

matrix_t multiply_matrix(matrix_t matrix_a, matrix_t matrix_b) {
    matrix_t result = matrix_create_empty(matrix_a.rows, matrix_b.cols);
    for (int row_a = 0; row_a < matrix_a.rows; ++row_a) {
        for (int col_b = 0; col_b < matrix_b.cols; ++col_b) {
            for (int col_a = 0; col_a < matrix_a.cols; ++col_a) {
                result.data[row_a][col_b] += matrix_a.data[row_a][col_a] * matrix_b.data[col_a][col_b];
            }
        }
    }
    return result;
}

matrix_t multiply_matrix_threaded(matrix_t matrix_a, matrix_t matrix_b) {
    matrix_t result = matrix_create_empty(matrix_a.rows, matrix_b.cols);
    int number_proc_used = MIN(get_number_of_procs(), matrix_a.rows);

    pthread_t *threads = calloc(sizeof(pthread_t), number_proc_used);
    thread_args_t *args = calloc(sizeof(thread_args_t), number_proc_used);
    int step_cache = matrix_a.rows / number_proc_used;
    int overfitted_rows = matrix_a.rows % number_proc_used;
    for (int i = 0; i < number_proc_used; ++i) {
        args[i].matrix_a = &matrix_a;
        args[i].matrix_b = &matrix_b;
        args[i].result = &result;

        args[i].start_index = 0;
        if (i != 0)
            args[i].start_index = args[i-1].end_index + 1;

        args[i].end_index = args[i].start_index + step_cache - 1;
        if (overfitted_rows > 0) {
            args[i].end_index++;
            overfitted_rows--;
        }

        // printf("proc n°%d : [%d;%d]\n", i + 1, args[i].start_index, args[i].end_index);
        if (pthread_create(&threads[i], NULL, thread_multiplication_routine, &args[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < number_proc_used; ++i) {
        pthread_join(threads[i], NULL);
    }
    free(threads);
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
    for (int row = 0; row < matrix.rows; ++row) {
        for (int col = 0; col < matrix.cols; ++col) {
            printf("%f\t", matrix.data[row][col]);
        }
        printf("\n");
    }
}

bool are_equal(matrix_t matrix_a, matrix_t matrix_b) {
    if (matrix_a.cols != matrix_b.cols | matrix_a.rows != matrix_b.rows)
        return false;
    for (int i = 0; i < matrix_a.cols; ++i) {
        for (int j = 0; j < matrix_a.rows; ++j) {
            if (matrix_a.data[i][j] != matrix_b.data[i][j])
                return false;
        }
    }
    return true;
}

int get_number_of_procs() {
    int ncpus;
    #if defined(__APPLE__)
        int mib[2];
        size_t len = sizeof(int);
        // Set up the mib array to request the number of CPUs
        mib[0] = CTL_HW;
        mib[1] = HW_NCPU;
        // Call sysctl to retrieve the number of CPUs
        if (sysctl(mib, 2, &ncpus, &len, NULL, 0) == -1) {
            perror("sysctl");
            exit(EXIT_FAILURE);
        }
    #elif defined(__linux__)
        return sysconf(_SC_NPROCESSORS_ONLN); // TODO check
    #elif defined(_WIN32)
        return GetActiveProcessorCount(ALL_PROCESSOR_GROUPS); // TODO check
    #endif

    return ncpus;
}