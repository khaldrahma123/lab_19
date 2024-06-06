#include <stdio.h>
#include <windows.h>
#include "working_with_files\file_.h"
int main() {
 const char* input_file = "input_5.txt";
 const char* output_file = "output_5.txt";
 process_file(input_file, output_file);
 SetConsoleOutputCP(CP_UTF8);
 printf("Преобразование завершено.\n");
 return 0;
}