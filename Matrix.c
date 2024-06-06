#include "matrix.h"
#include <stdlib.h>
matrix get_mem_matrix(int n) {
 matrix m;
 m.n = n;
 m.values = (int **)malloc(n * sizeof(int *));
 for (int i = 0; i < n; i++) {
 m.values[i] = (int *)malloc(n * sizeof(int));
 }
 return m;
}
void free_matrix(matrix *m) {
 for (int i = 0; i < m->n; i++) {
 free(m->values[i]);
 }
 free(m->values);
}
matrix read_matrix_from_binary(FILE *file, int n, int *res) {
 matrix m = get_mem_matrix(n);
 *res = 1;
 for (int i = 0; i < n; i++) {
 for (int j = 0; j < n; j++) {
 if (fread(&m.values[i][j], sizeof(int), 1, file) != 1) {
 *res = 0;
 free_matrix(&m);
return m;
 }
 }
 }
 return m;
}
void write_matrix_to_binary(FILE *file, matrix *m, int n) {
 for (int i = 0; i < n; i++) {
 for (int j = 0; j < n; j++) {
 fwrite(&m->values[i][j], sizeof(int), 1, file);
 }
 }
}
10
int is_symmetric(matrix *m) {
 for (int i = 0; i < m->n; i++) {
 for (int j = 0; j < m->n; j++) {
 if (m->values[i][j] != m->values[j][i]) {
 return 0;
 }
 }
 }
 return 1;
}
void transpose_matrix(matrix *m) {
 for (int i = 0; i < m->n; i++) {
 for (int j = i + 1; j < m->n; j++) {
 int temp = m->values[i][j];
 m->values[i][j] = m->values[j][i];
 m->values[j][i] = temp;
 }
 }
}
