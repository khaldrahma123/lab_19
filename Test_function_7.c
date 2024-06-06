#include <stdio.h>
#include <assert.h>
#include "working_with_files/file_.h"
void create_test_file(const char* filename, int* numbers, int count) {
 FILE* file = fopen(filename, "wb");
 if (!file) {
 perror("Failed to open file");
 exit(EXIT_FAILURE);
 }
 fwrite(numbers, sizeof(int), count, file);
 fclose(file);
}
void test_rearrange_integers() {
 const char* filename = "test_integers.bin";
 int numbers[] = {5, -3, 10, -8, 2};
 int expected[] = {5, 10, 2, -3, -8};
 int count = sizeof(numbers) / sizeof(numbers[0]);
 // Создание тестового файла
22
 create_test_file(filename, numbers, count);
 // Преобразование файла
 rearrange_integers(filename);
 // Проверка результата
 FILE* file = fopen(filename, "rb");
 if (!file) {
 perror("Failed to open file");
 exit(EXIT_FAILURE);
 }
 int result[count];
 fread(result, sizeof(int), count, file);
 fclose(file);
 printf("Expected order: ");
 for (int i = 0; i < count; i++) {
 printf("%d ", expected[i]);
 }
 printf("\n");
 printf("Actual order: ");
 for (int i = 0; i < count; i++) {
 printf("%d ", result[i]);
 }
 printf("\n");
 for (int i = 0; i < count; i++) {
 assert(result[i] == expected[i]);
 }
 printf("Test passed.\n");
}
int main() {
 test_rearrange_integers();
 return 0;
}