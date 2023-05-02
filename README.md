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

![Threaded_schema](https://user-images.githubusercontent.com/75916953/235661801-cc16f359-9018-46da-87d0-aa9f25e596c7.png)
