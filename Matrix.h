#ifndef UNTITLED27_MATRIX_H
#define UNTITLED27_MATRIX_H
#include <stdio.h>
typedef struct {
 int **values;
 int n;
} matrix;
matrix get_mem_matrix(int n);
void free_matrix(matrix *m);
matrix read_matrix_from_binary(FILE *file, int n, int *res);
void write_matrix_to_binary(FILE *file, matrix *m, int n);
int is_symmetric(matrix *m);
void transpose_matrix(matrix *m);
#endif //UNTITLED27_MATRIX_H
