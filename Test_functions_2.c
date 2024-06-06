#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "working_with_files/file_.h"
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
void testConvertFixedToFloating() {
 const char *inputContent = "123.456\n78.90\n12.34\n0.56789\n100.0\n0.0\n23.456\n-0.12345\n";
 const char *expectedOutputContent = 
"123.46\n78.90\n12.34\n0.57\n100.00\n0.00\n-23.46\n-0.12\n";
 const char *inputFilename = "test_input.txt";
14
 const char *outputFilename = "test_output.txt";
 createFile(inputFilename, inputContent);
 convertFixedToFloating(inputFilename, outputFilename);
 char *outputContent = readFile(outputFilename);
 if (strcmp(outputContent, expectedOutputContent) == 0) {
 printf("Test passed: Successfully converted fixed point to floating 
point.\n");
 } else {
 printf("Test failed: Incorrect output.\n");
 printf("Expected:\n%s\n", expectedOutputContent);
 printf("Got:\n%s\n", outputContent);
 }
 free(outputContent);
 deleteFile(inputFilename);
 deleteFile(outputFilename);
}
int main() {
 testConvertFixedToFloating();
 return 0;
}