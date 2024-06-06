#include <stdio.h>
#include "working_with_files\file_.h"
int main() {
 FILE *inputFile = fopen("input.txt", "r");
 FILE *outputFile = fopen("output.txt", "w");
 if (inputFile == NULL || outputFile == NULL) {
 fprintf(stderr, "Error opening file.\n");
 return 1;
 }
 int **matrix;
 int n;
 while (fscanf(inputFile, "%d", &n) == 1) {
 matrix = readMatrix(inputFile, n);
 writeMatrix(outputFile, matrix, n);
 freeMatrix(matrix, n);
 }
 fclose(inputFile);
 fclose(outputFile);
 return 0;
}