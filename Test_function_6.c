#include <assert.h>
#include "working_with_files/file_.h"
void create_test_file(const char* filename, PolynomialTerm* polynomials[], 
int counts[], int num_polynomials) {
 FILE* file = fopen(filename, "wb");
 if (!file) {
 perror("Failed to open file");
 exit(EXIT_FAILURE);
 }
20
 for (int i = 0; i < num_polynomials; i++) {
 fwrite(&counts[i], sizeof(int), 1, file);
 fwrite(polynomials[i], sizeof(PolynomialTerm), counts[i], file);
 }
 fclose(file);
}
void read_polynomials(const char* filename, PolynomialTerm** polynomials, 
int* counts, int* num_polynomials) {
 FILE* file = fopen(filename, "rb");
 if (!file) {
 perror("Failed to open file");
 exit(EXIT_FAILURE);
 }
 *num_polynomials = 0;
 while (fread(&counts[*num_polynomials], sizeof(int), 1, file) == 1) {
 polynomials[*num_polynomials] = 
(PolynomialTerm*)malloc(counts[*num_polynomials] * sizeof(PolynomialTerm));
 fread(polynomials[*num_polynomials], sizeof(PolynomialTerm), 
counts[*num_polynomials], file);
 (*num_polynomials)++;
 }
 fclose(file);
}
void test_process_file_s() {
 const char* input_filename = "test_polynomials.bin";
 const char* output_filename = "test_filtered_polynomials.bin";
 // Создание тестовых многочленов
 PolynomialTerm poly1[] = {{2, 3.0}, {1, -2.0}, {0, 1.0}}; // 3x^2 - 2x + 
1 (не корень для x=1)
 PolynomialTerm poly2[] = {{2, 1.0}, {0, -1.0}}; // x^2 - 1 
(корень для x=1)
 PolynomialTerm poly3[] = {{1, 1.0}, {0, -1.0}}; // x - 1 
(корень для x=1)
 PolynomialTerm* polynomials[] = {poly1, poly2, poly3};
 int counts[] = {3, 2, 2};
 int num_polynomials = 3;
 // Создание входного файла
 create_test_file(input_filename, polynomials, counts, num_polynomials);
 // Запуск функции обработки
 process_file_s(input_filename, output_filename, 1.0);
 // Чтение выходного файла
 PolynomialTerm* out_polynomials[3];
 int out_counts[3];
 int out_num_polynomials = 0;
 read_polynomials(output_filename, out_polynomials, out_counts, 
&out_num_polynomials);
 // Проверка результатов
 assert(out_num_polynomials == 1);
 assert(out_counts[0] == 3);
 assert(out_polynomials[0][0].degree == 2);
 assert(out_polynomials[0][0].coefficient == 3.0);
 assert(out_polynomials[0][1].degree == 1);
 assert(out_polynomials[0][1].coefficient == -2.0);
21
 assert(out_polynomials[0][2].degree == 0);
 assert(out_polynomials[0][2].coefficient == 1.0);
 // Освобождение памяти
 for (int i = 0; i < out_num_polynomials; i++) {
 free(out_polynomials[i]);
 }
 printf("test_process_file_s passed.\n");
}
int main() {
 test_process_file_s();
 return 0;
}