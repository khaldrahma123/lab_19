#include <stdio.h>
#include <windows.h>
#include "working_with_files\file_.h"
int main(int argc, char *argv[]) {
 if (argc != 4) {
 SetConsoleOutputCP(CP_UTF8);
 fprintf(stderr, "Использование: %s <input_file> <output_file> 
16
<pattern>\n", argv[0]);
 return 1;
 }
 const char *inputFilePath = argv[1];
 const char *outputFilePath = argv[2];
 const char *pattern = argv[3];
 filterWordsContainingPattern(inputFilePath, outputFilePath, pattern);
 SetConsoleOutputCP(CP_UTF8);
 printf("Отфильтрованные слова, содержащие шаблон\"%s\" были сохранены для
%s.\n", pattern, outputFilePath);
 return 0;
}