#include <stdio.h>
#include "working_with_files\file_.h"
int main() {
 const char *inputFilePath = "input1.txt";
 const char *outputFilePath = "output1.txt";
 convertFixedToFloating(inputFilePath, outputFilePath);
 printf("Conversion completed successfully.\n");
 return 0;
}