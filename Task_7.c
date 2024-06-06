#include <stdio.h>
#include "working_with_files/file_.h"
int main() {
 const char* filename = "integers.bin";
 // Создаем файл с целыми числами
 FILE* file = fopen(filename, "wb");
 if (!file) {
 perror("Failed to open file");
 return 1;
 }
 int numbers[] = {5, -3, 10, -8, 2};
 fwrite(numbers, sizeof(int), sizeof(numbers) / sizeof(numbers[0]), file);
 fclose(file);
 // Преобразование файла
 rearrange_integers(filename);
 printf("File rearranged successfully.\n");
 return 0;
}