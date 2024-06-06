#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "working_with_files\file_.h"
void createFile(const char *filename, const char *content) {
 FILE *file = fopen(filename, "w");
 if (file != NULL) {
 fprintf(file, "%s", content);
 fclose(file);
 } else {
 SetConsoleOutputCP(CP_UTF8);
 fprintf(stderr, "Ошибка создания файла: %s\n", filename);
 exit(1);
 }
}
char* readFile(const char *filename) {
 FILE *file = fopen(filename, "r");
15
 if (file == NULL) {
 SetConsoleOutputCP(CP_UTF8);
 fprintf(stderr, "Ошибка чтения файла: %s\n", filename);
 exit(1);
 }
 fseek(file, 0, SEEK_END);
 long length = ftell(file);
 fseek(file, 0, SEEK_SET);
 char *buffer = malloc(length + 1);
 fread(buffer, 1, length, file);
 buffer[length] = '\0';
 fclose(file);
 return buffer;
}
void deleteFile(const char *filename) {
 if (remove(filename) != 0) {
 SetConsoleOutputCP(CP_UTF8);
 fprintf(stderr, "Ошибка удаления файла: %s\n", filename);
 }
}
void testCalculateExpressionAndAppendResult(const char *inputContent, const 
char *expectedOutputContent) {
 const char *filename = "test_expression.txt";
 createFile(filename, inputContent);
 calculateExpressionAndAppendResult(filename);
 char *outputContent = readFile(filename);
 if (strcmp(outputContent, expectedOutputContent) == 0) {
 SetConsoleOutputCP(CP_UTF8);
 printf("Тест пройден: результат совпадает с ожидаемым.\n");
 } else {
 SetConsoleOutputCP(CP_UTF8);
 printf("Тест не пройден: результат не совпадает с ожидаемым.\n");
 printf("Ожидаемый результат:\n%s\n", expectedOutputContent);
 printf("Фактический результат:\n%s\n", outputContent);
 }
 free(outputContent);
 deleteFile(filename);
}
int main() {
 testCalculateExpressionAndAppendResult("3+5\n9-4\n6*7\n8/2\n", 
"3+5\n8\n9-4\n5\n6*7\n42\n8/2\n4\n");
 return 0;
}