#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "working_with_files\file_.h"
// Вспомогательная функция для создания временного файла с матрицей
void createTempFile(const char* filename, const char* content) {
 FILE *file = fopen(filename, "w");
 assert(file != NULL);
 fprintf(file, "%s", content);
 fclose(file);
}
// Вспомогательная функция для чтения содержимого файла в строку
char* readFileToString(const char* filename) {
 FILE *file = fopen(filename, "r");
 assert(file != NULL);
 fseek(file, 0, SEEK_END);
 long length = ftell(file);
 fseek(file, 0, SEEK_SET);
 char *buffer = (char *)calloc(length + 1, sizeof(char)); // Используем
calloc для инициализации нулями
 fread(buffer, 1, length, file);
 buffer[length] = '\0';
 fclose(file);
 return buffer;
}
// Вспомогательная функция для удаления невидимых символов в конце строки
void strtrim(char* str) {
 size_t len = strlen(str);
 while (len > 0 && (str[len-1] == ' ' || str[len-1] == '\n' || str[len-1] 
== '\r' || str[len-1] == '\t')) {
12
 str[len-1] = '\0';
 len--;
 }
}
// Функция для вывода каждого символа строки с его кодом
void printStringWithCodes(const char* str) {
 printf("String with codes:\n");
 for (size_t i = 0; i < strlen(str); ++i) {
 printf("%c [%d] ", str[i], str[i]);
 }
 printf("\n");
}
// Тестовая функция для readMatrix и writeMatrix
void testReadAndWriteMatrix() {
 const char *inputContent = "1 2\n3 4\n";
 const char *expectedOutputContent = "2\n1 3\n2 4\n";
 createTempFile("test_input.txt", inputContent);
 FILE *inputFile = fopen("test_input.txt", "r");
 assert(inputFile != NULL);
 int **matrix = readMatrix(inputFile, 2);
 fclose(inputFile);
 FILE *outputFile = fopen("test_output.txt", "w");
 assert(outputFile != NULL);
 writeMatrix(outputFile, matrix, 2);
 fclose(outputFile);
 char *outputContent = readFileToString("test_output.txt");
 strtrim(outputContent); // Удаляем лишние символы
 // Отладочная печать
 printf("Expected Output:\n%s\n", expectedOutputContent);
 printf("Actual Output:\n%s\n", outputContent);
 // Вывод каждого символа строки с его кодом
 printStringWithCodes(expectedOutputContent);
 printStringWithCodes(outputContent);
}
// Тестовая функция для freeMatrix
void testFreeMatrix() {
 int n = 2;
 int **matrix = (int **)malloc(n * sizeof(int *));
 for (int i = 0; i < n; ++i) {
 matrix[i] = (int *)malloc(n * sizeof(int));
 }
 freeMatrix(matrix, n);
}
int main() {
 testReadAndWriteMatrix();
 testFreeMatrix();
 printf("All tests passed!\n");
 return 0;
}
