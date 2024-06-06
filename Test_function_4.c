#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "working_with_files\file_.h"
void createFile(const char *filename, const char *content) {
 FILE *file = fopen(filename, "w");
 if (file != NULL) {
 fprintf(file, "%s", content);
 fclose(file);
 } else {
 fprintf(stderr, "Error creating file: %s\n", filename);
 exit(1);
 }
}
char* readFile(const char *filename) {
 FILE *file = fopen(filename, "r");
 if (file == NULL) {
 fprintf(stderr, "Error reading file: %s\n", filename);
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
 fprintf(stderr, "Error deleting file: %s\n", filename);
 }
}
void testFilterWordsContainingPattern(const char *inputContent, const char 
*pattern, const char *expectedOutputContent) {
 const char *inputFilename = "test_input_4.txt";
 const char *outputFilename = "test_output.txt";
 createFile(inputFilename, inputContent);
17
 filterWordsContainingPattern(inputFilename, outputFilename, pattern);
 char *outputContent = readFile(outputFilename);
 if (strcmp(outputContent, expectedOutputContent) == 0) {
 printf("Test passed: output matches expected result.\n");
 } else {
 printf("Test failed: output does not match expected result.\n");
 printf("Expected result:\n%s\n", expectedOutputContent);
 printf("Actual result:\n%s\n", outputContent);
 }
 free(outputContent);
 deleteFile(inputFilename);
 deleteFile(outputFilename);
}
int main() {
 testFilterWordsContainingPattern("hello world\nthis is a test\npattern 
matching\n", "is", "this\nis\n");
 testFilterWordsContainingPattern("filter the words\ncontaining certain 
pattern\nin this file\n", "in", "containing\nin\n");
 return 0;
}