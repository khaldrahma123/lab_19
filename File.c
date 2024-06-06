#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include "file_.h"
int** readMatrix(FILE *file, int n) {
 int **matrix = (int **)malloc(n * sizeof(int *));
 for (int i = 0; i < n; ++i) {
 matrix[i] = (int *)malloc(n * sizeof(int));
 for (int j = 0; j < n; ++j) {
 fscanf(file, "%d", &(matrix[i][j]));
 }
 }
 return matrix;
}
void writeMatrix(FILE *file, int **matrix, int n) {
 fprintf(file, "%d\n", n);
 for (int j = 0; j < n; ++j) {
 for (int i = 0; i < n; ++i) {
 fprintf(file, "%d", matrix[i][j]);
 if (i < n - 1) {
 fprintf(file, " ");
 }
 }
 fprintf(file, "\n");
 }
}
void freeMatrix(int **matrix, int n) {
 for (int i = 0; i < n; ++i) {
 free(matrix[i]);
 }
 free(matrix);
}
void convertFixedToFloating(const char *inputFilePath, const char 
*outputFilePath) {
 FILE *inputFile = fopen(inputFilePath, "r");
 FILE *outputFile = fopen(outputFilePath, "w");
 if (inputFile == NULL || outputFile == NULL) {
 fprintf(stderr, "Error opening file.\n");
 exit(1);
 }
 double number;
 while (fscanf(inputFile, "%lf", &number) == 1) {
 fprintf(outputFile, "%.2lf\n", number);
 }
4
 fclose(inputFile);
 fclose(outputFile);
}
int evaluateExpression(const char *expression, int *result) {
 int operand1 = 0, operand2 = 0;
 char operator = 0;
 int numOperands = 0;
 while (*expression) {
 if (isdigit(*expression)) {
 if (numOperands == 0) {
 operand1 = *expression - '0';
 numOperands++;
 } else if (numOperands == 1) {
 operand2 = *expression - '0';
 numOperands++;
 } else {
 return -1; // Ошибка: слишком много операндов
 }
 } else if (*expression == '+' || *expression == '-' || *expression == 
'*' || *expression == '/') {
 if (operator == 0) {
 operator = *expression;
 } else {
 return -1; // Ошибка: слишком много операторов
 }
 }
 expression++;
 }
 if (numOperands < 2) {
 return -1; // Ошибка: недостаточно операндов
 }
 switch (operator) {
 case '+': *result = operand1 + operand2; break;
 case '-': *result = operand1 - operand2; break;
 case '*': *result = operand1 * operand2; break;
 case '/': *result = operand1 / operand2; break;
 default: return -1; // Ошибка: неизвестный оператор
 }
 return 0; // Успешно
}
void calculateExpressionAndAppendResult(const char *filePath) {
 FILE *file = fopen(filePath, "r+");
 if (file == NULL) {
 SetConsoleOutputCP(CP_UTF8);
 fprintf(stderr, "Ошибка открытия файла.\n");
 exit(1);
 }
 char expression[100];
 char buffer[10000] = {0}; // buffer to store the entire content of the 
file
 char *buf_ptr = buffer;
 long offset = 0;
 while (fgets(expression, sizeof(expression), file) != NULL) {
 // Remove the newline character at the end of the expression
5
 size_t len = strlen(expression);
 if (len > 0 && expression[len - 1] == '\n') {
 expression[len - 1] = '\0';
 }
 int result;
 if (evaluateExpression(expression, &result) == 0) {
 buf_ptr += sprintf(buf_ptr, "%s\n%d\n", expression, result);
 } else {
 buf_ptr += sprintf(buf_ptr, "%s\n", expression);
 SetConsoleOutputCP(CP_UTF8);
 fprintf(stderr, "Ошибка вычисления выражения: %s\n", expression);
 }
 }
 freopen(filePath, "w", file);
 fputs(buffer, file);
 fclose(file);
}
int containsPattern(const char *word, const char *pattern) {
 return strstr(word, pattern) != NULL;
}
void filterWordsContainingPattern(const char *inputFilePath, const char 
*outputFilePath, const char *pattern) {
 FILE *inputFile = fopen(inputFilePath, "r");
 if (inputFile == NULL) {
 SetConsoleOutputCP(CP_UTF8);
 fprintf(stderr, "Ошибка при открытии входного файла.\n");
 exit(1);
 }
 FILE *outputFile = fopen(outputFilePath, "w");
 if (outputFile == NULL) {
 SetConsoleOutputCP(CP_UTF8);
 fprintf(stderr, "Ошибка при открытии выходного файла.\n");
 fclose(inputFile);
 exit(1);
 }
 char word[256];
 while (fscanf(inputFile, "%255s", word) == 1) {
 if (containsPattern(word, pattern)) {
 fprintf(outputFile, "%s\n", word);
 }
 }
 fclose(inputFile);
 fclose(outputFile);
}
// Функция для проверки, является ли символ буквой
int is_letter(char c) {
 return isalpha(c);
}
// Функция для нахождения самого длинного слова в строке
char* longest_word(char* str) {
 char* longest = NULL;
 char* word = strtok(str, " ");
 int max_length = 0;
6
 while (word != NULL) {
 int len = strlen(word);
 if (len > max_length) {
 max_length = len;
 longest = word;
 }
 word = strtok(NULL, " ");
 }
 return longest;
}
// Функция для обработки файла
void process_file(const char* input_file, const char* output_file) {
 FILE* infile = fopen(input_file, "r");
 if (infile == NULL) {
 printf("Не удается открыть файл %s\n", input_file);
 return;
 }
 FILE* outfile = fopen(output_file, "w");
 if (outfile == NULL) {
 printf("Не удается создать файл %s\n", output_file);
 fclose(infile);
 return;
 }
 char line[1000]; // Предполагаем максимальную длину строки 1000 символов
 while (fgets(line, sizeof(line), infile)) {
 char cleaned_line[1000] = "";
 int i = 0;
 for (int j = 0; line[j] != '\0'; j++) {
 if (is_letter(line[j])) {
 cleaned_line[i++] = line[j];
 } else if (i > 0 && cleaned_line[i - 1] != ' ') {
 cleaned_line[i++] = ' ';
 }
 }
 cleaned_line[i] = '\0';
 char* longest = longest_word(cleaned_line);
 if (longest != NULL) {
 fprintf(outfile, "%s\n", longest);
 }
 }
 fclose(infile);
 fclose(outfile);
}
void read_polynomial(FILE* file, PolynomialTerm** terms, int* count) {
 fread(count, sizeof(int), 1, file);
 *terms = (PolynomialTerm*)malloc((*count) * sizeof(PolynomialTerm));
 fread(*terms, sizeof(PolynomialTerm), *count, file);
}
void write_polynomial(FILE* file, PolynomialTerm* terms, int count) {
 fwrite(&count, sizeof(int), 1, file);
 fwrite(terms, sizeof(PolynomialTerm), count, file);
}
int is_root(PolynomialTerm* terms, int count, double x) {
 double result = 0.0;
 for (int i = 0; i < count; ++i) {
7
 result += terms[i].coefficient * pow(x, terms[i].degree);
 }
 return result == 0.0;
}
void process_file_s(const char* input_filename, const char* output_filename, 
double x) {
 FILE* input_file = fopen(input_filename, "rb");
 if (!input_file) {
 perror("Failed to open input file");
 exit(EXIT_FAILURE);
 }
 FILE* output_file = fopen(output_filename, "wb");
 if (!output_file) {
 perror("Failed to open output file");
 fclose(input_file);
 exit(EXIT_FAILURE);
 }
 PolynomialTerm* terms = NULL;
 int count = 0;
 while (fread(&count, sizeof(int), 1, input_file) == 1) {
 terms = (PolynomialTerm*)malloc(count * sizeof(PolynomialTerm));
 fread(terms, sizeof(PolynomialTerm), count, input_file);
 if (!is_root(terms, count, x)) {
 write_polynomial(output_file, terms, count);
 }
 free(terms);
 }
 fclose(input_file);
 fclose(output_file);
}
void read_integers(const char* filename, int** positive, int* pos_count, 
int** negative, int* neg_count);
void write_integers(const char* filename, int* integers, int count);
void rearrange_integers(const char* filename) {
 FILE* file = fopen(filename, "rb");
 if (!file) {
 perror("Failed to open file");
 exit(EXIT_FAILURE);
 }
 FILE* new_file = fopen("rearranged_integers.bin", "wb");
 if (!new_file) {
 perror("Failed to create new file");
 exit(EXIT_FAILURE);
 }
 int num;
 while (fread(&num, sizeof(int), 1, file) == 1) {
 if (num >= 0) {
 fwrite(&num, sizeof(int), 1, new_file);
 }
 }
 fseek(file, 0, SEEK_SET); // Вернем указатель файла в начало
 while (fread(&num, sizeof(int), 1, file) == 1) {
8
 if (num < 0) {
 fwrite(&num, sizeof(int), 1, new_file);
 }
 }
 fclose(file);
 fclose(new_file);
 remove(filename); // Удаляем исходный файл
 rename("rearranged_integers.bin", filename); // Переименовываем новый
файл
}
size_t read_file_to_buff(const char *filePath, char *buff, size_t buffSize) {
 FILE *f = fopen(filePath, "r");
 if (f == NULL) {
 return 0;
 }
 size_t size = fread(buff, sizeof(char), buffSize, f);
 fclose(f);
 return size;
}
long get_file_size(FILE *fp) {
 fseek(fp, 0, SEEK_END);
 long size = ftell(fp);
 fseek(fp, 0, SEEK_SET);
 return size;
}