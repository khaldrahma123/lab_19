#ifndef UNTITLED27_FILE__H
#define UNTITLED27_FILE__H
#include <stdio.h>
#include <stdlib.h>
typedef struct {
 int degree;
 double coefficient;
} PolynomialTerm;
// Функция для чтения матрицы из файла
int** readMatrix(FILE *file, int n);
// Функция для записи матрицы в файл
void writeMatrix(FILE *file, int **matrix, int n);
// Функция для освобождения памяти, выделенной под матрицу
void freeMatrix(int **matrix, int n);
void convertFixedToFloating(const char *inputFilePath, const char 
*outputFilePath);
void calculateExpressionAndAppendResult(const char *filePath);
//Функция для проверки того, содержит ли слово шаблон
int containsPattern(const char *word, const char *pattern);
// Функция для фильтрации слов, содержащих определенный шаблон, из входного
файла в выходной
void filterWordsContainingPattern(const char *inputFilePath, const char 
*outputFilePath, const char *pattern);
9
void process_file(const char* input_file, const char* output_file);
void read_polynomial(FILE* file, PolynomialTerm** terms, int* count);
void write_polynomial(FILE* file, PolynomialTerm* terms, int count);
int is_root(PolynomialTerm* terms, int count, double x);
void process_file_s(const char* input_filename, const char* output_filename, 
double x);
void rearrange_integers(const char* filename);
size_t read_file_to_buff(const char *filePath, char *buff, size_t buffSize);
long get_file_size(FILE *fp);
#endif //UNTITLED27_FILE__H
