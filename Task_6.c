#include <stdio.h>
#include "working_with_files\file_.h"
void create_example_bin_file(const char* filename) {
 FILE* file = fopen(filename, "wb");
 if (!file) {
 perror("Failed to open file");
 exit(EXIT_FAILURE);
 }
 // Пример многочлена 1: 3x^2 + 2x + 1
 PolynomialTerm poly1[] = {{2, 3.0}, {1, 2.0}, {0, 1.0}};
 int count1 = sizeof(poly1) / sizeof(poly1[0]);
 fwrite(&count1, sizeof(int), 1, file);
 fwrite(poly1, sizeof(PolynomialTerm), count1, file);
 // Пример многочлена 2: x^3 - x
 PolynomialTerm poly2[] = {{3, 1.0}, {1, -1.0}, {0, 0.0}};
 int count2 = sizeof(poly2) / sizeof(poly2[0]);
 fwrite(&count2, sizeof(int), 1, file);
 fwrite(poly2, sizeof(PolynomialTerm), count2, file);
 fclose(file);
}
int main() {
 const char* input_filename = "polynomials.bin";
 const char* output_filename = "filtered_polynomials.bin";
 double x = 2.0;
 create_example_bin_file(input_filename);
 process_file_s(input_filename, output_filename, x);
 printf("Processing completed.\n");
 return 0;
}