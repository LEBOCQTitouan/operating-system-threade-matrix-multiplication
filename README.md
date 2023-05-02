# Operating system : threaded matrix multiplication

This project provide a simple implementation of a matrix multiplication using thread in C.

## Instalation

### Building the project

#### Using Cmake

```bash
mkdir build
cmake --build build
```

#### Using make

```bash
make
```

## Project description

In this simple project we will implement a matrix multiplication using thread in C. The threaded multiplication will be
compared to a sequential multiplication and will be timed to see the performance gain.

The matrix multiplication will be done by separating the martrix in 4 parts and each part will be calculated by a
thread.