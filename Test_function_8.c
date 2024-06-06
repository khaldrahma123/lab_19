#include <stdio.h>
#include <stdlib.h>
#include "work_matrix/matrix.h"
#include "working_with_files/file_.h"
void process_matrices(const char* filename) {
 FILE *file = fopen(filename, "r+b");
 if (!file) {
 perror("Failed to open file");
 exit(EXIT_FAILURE);
 }
 int n;
 fread(&n, sizeof(int), 1, file);
 matrix m;
 long pos;
 int res;
 while ((pos = ftell(file)) != -1 && pos < get_file_size(file)) {
 m = read_matrix_from_binary(file, n, &res);
 if (!res) {
 break;
23
 }
 if (!is_symmetric(&m)) {
 transpose_matrix(&m);
 fseek(file, pos, SEEK_SET);
 write_matrix_to_binary(file, &m, n);
 fflush(file);
 }
 free_matrix(&m);
 }
 fclose(file);
}
void create_test_file(const char* filename) {
 FILE *file = fopen(filename, "wb");
 if (!file) {
 perror("Failed to open file");
 exit(EXIT_FAILURE);
 }
 int n = 3;
 fwrite(&n, sizeof(int), 1, file);
 int matrices[2][3][3] = {
 { {1, 2, 3}, {2, 1, 4}, {3, 4, 1} },
 { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} }
 };
 for (int k = 0; k < 2; k++) {
 for (int i = 0; i < n; i++) {
 for (int j = 0; j < n; j++) {
 fwrite(&matrices[k][i][j], sizeof(int), 1, file);
 }
 }
 }
 fclose(file);
}
int main() {
 const char* filename = "matrices.bin";
 create_test_file(filename);
 process_matrices(filename);
 printf("Processing completed.\n");
 return 0;
}