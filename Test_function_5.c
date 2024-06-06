#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "working_with_files/file_.h"
// Вспомогательная функция для сравнения содержимого файлов
int compare_files(const char* file1, const char* file2) {
 FILE *f1 = fopen(file1, "r");
 FILE *f2 = fopen(file2, "r");
 if (f1 == NULL || f2 == NULL) {
 if (f1) fclose(f1);
 if (f2) fclose(f2);
 return 0;
 }
 char ch1 = getc(f1);
 char ch2 = getc(f2);
 while (ch1 != EOF && ch2 != EOF) {
 if (ch1 != ch2) {
 fclose(f1);
 fclose(f2);
18
 return 0;
 }
 ch1 = getc(f1);
 ch2 = getc(f2);
 }
 int result = ch1 == ch2;
 fclose(f1);
 fclose(f2);
 return result;
}
// Тестовая функция для проверки корректности работы process_file
void test_process_file() {
 // Test case 1
 const char* input_file1 = "test_input1.txt";
 const char* expected_output_file1 = "expected_output1.txt";
 const char* actual_output_file1 = "actual_output1.txt";
 // Запись тестовых данных в файл
 FILE* input1 = fopen(input_file1, "w");
 fprintf(input1, "The quicks brown fox jumps over the lazy dog.\n");
 fprintf(input1, "This is a test file for the longest word 
extraction.\n");
 fprintf(input1, "Programming is fun and challenging.\n");
 fprintf(input1, "I love OpenAI's language models.\n");
 fclose(input1);
 // Запись ожидаемого результата в файл
 FILE* expected1 = fopen(expected_output_file1, "w");
 fprintf(expected1, "quick\n");
 fprintf(expected1, "extraction\n");
 fprintf(expected1, "challenging\n");
 fprintf(expected1, "language");
 fclose(expected1);
 // Выполнение тестируемой функции
 process_file(input_file1, actual_output_file1);
 // Проверка результата
 assert(compare_files(actual_output_file1, expected_output_file1) && "Test 
case 1 failed");
 // Test case 2 (добавьте больше тестовых случаев по необходимости)
 const char* input_file2 = "test_input2.txt";
 const char* expected_output_file2 = "expected_output2.txt";
 const char* actual_output_file2 = "actual_output2.txt";
 FILE* input2 = fopen(input_file2, "w");
 fprintf(input2, "Hello world.\n");
 fprintf(input2, "C programming language.\n");
 fprintf(input2, "Unit testing is essential.\n");
 fprintf(input2, "File processing example.\n");
 fclose(input2);
 FILE* expected2 = fopen(expected_output_file2, "w");
 fprintf(expected2, "Hello\n");
 fprintf(expected2, "programming\n");
 fprintf(expected2, "essential\n");
 fprintf(expected2, "processing\n");
 fclose(expected2);
19
 process_file(input_file2, actual_output_file2);
 assert(compare_files(actual_output_file2, expected_output_file2) && "Test 
case 2 failed");
 printf("All test cases passed!\n");
}
int main() {
 test_process_file();
 return 0;
}