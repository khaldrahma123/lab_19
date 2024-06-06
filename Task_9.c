#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_NAME_LENGTH 50
// Структура для представления информации о спортсмене
typedef struct {
 char name[MAX_NAME_LENGTH];
 int bestResult;
} Athlete;
24
// Функция для создания бинарного файла с данными о спортсменах
void createAthletesFile(const char* filename) {
 FILE *file = fopen(filename, "wb");
 if (!file) {
 perror("Failed to open file");
 exit(EXIT_FAILURE);
 }
 // Примерные данные о спортсменах
 Athlete athletes[] = {
 {"John Doe", 95},
 {"Jane Smith", 92},
 {"Emily Davis", 87},
 {"Michael Brown", 88},
 {"Jessica Wilson", 90}
 };
 int count = sizeof(athletes) / sizeof(Athlete);
 fwrite(&count, sizeof(int), 1, file); // Записываем количество
спортсменов в файл
 for (int i = 0; i < count; ++i) {
 fwrite(&athletes[i], sizeof(Athlete), 1, file); // Записываем
информацию о спортсмене в файл
 }
 fclose(file);
 printf("File '%s' created successfully with %d athletes.\n", filename, 
count);
}
// Функция для чтения данных о спортсменах из бинарного файла
Athlete* readAthletes(const char* filename, int* count) {
 FILE *file = fopen(filename, "rb");
 if (!file) {
 perror("Failed to open file");
 exit(EXIT_FAILURE);
 }
 fread(count, sizeof(int), 1, file); // Читаем количество спортсменов из
файла
 Athlete *athletes = (Athlete*)malloc(*count * sizeof(Athlete));
 for (int i = 0; i < *count; ++i) {
 fread(&athletes[i], sizeof(Athlete), 1, file); // Читаем информацию о
спортсмене из файла
 }
 fclose(file);
 return athletes;
}
// Функция для сортировки спортсменов по наилучшему результату (по убыванию)
void sortAthletes(Athlete* athletes, int count) {
 for (int i = 0; i < count - 1; ++i) {
 for (int j = 0; j < count - i - 1; ++j) {
 if (athletes[j].bestResult < athletes[j + 1].bestResult) {
 // Меняем местами спортсменов, если их результаты не в том
порядке
 Athlete temp = athletes[j];
athletes[j] = athletes[j + 1];
athletes[j + 1] = temp;
25
 }
 }
 }
}
// Функция для формирования команды из первых n лучших спортсменов
Athlete* createTeam(Athlete* athletes, int count, int n) {
 if (n > count) {
 fprintf(stderr, "Error: Not enough athletes in the file.\n");
 exit(EXIT_FAILURE);
 }
 // Выделяем память под массив команды и копируем первых n спортсменов
 Athlete *team = (Athlete*)malloc(n * sizeof(Athlete));
 memcpy(team, athletes, n * sizeof(Athlete));
 return team;
}
// Функция для записи информации о спортсменах команды в бинарный файл
void writeTeamToFile(Athlete* team, int count, const char* filename) {
 FILE *file = fopen(filename, "wb");
 if (!file) {
 perror("Failed to open file");
 exit(EXIT_FAILURE);
 }
 fwrite(&count, sizeof(int), 1, file); // Записываем количество
спортсменов в файл
 for (int i = 0; i < count; ++i) {
 fwrite(&team[i], sizeof(Athlete), 1, file); // Записываем информацию
о спортсмене в файл
 }
 fclose(file);
}
// Функция для проверки содержимого файла
void checkFileContent(const char* filename, Athlete* expectedAthletes, int 
expectedCount) {
 int count;
 Athlete* athletes = readAthletes(filename, &count);
 assert(count == expectedCount);
 for (int i = 0; i < count; ++i) {
 assert(strcmp(athletes[i].name, expectedAthletes[i].name) == 0);
 assert(athletes[i].bestResult == expectedAthletes[i].bestResult);
 }
 free(athletes);
}
void test_createAthletesFile() {
 const char* filename = "test_athletes.bin";
 createAthletesFile(filename);
 Athlete expectedAthletes[] = {
 {"John Doe", 95},
 {"Jane Smith", 92},
 {"Emily Davis", 87},
 {"Michael Brown", 88},
 {"Jessica Wilson", 90}
 };
 int expectedCount = sizeof(expectedAthletes) / sizeof(Athlete);
26
 checkFileContent(filename, expectedAthletes, expectedCount);
}
void test_sortAthletes() {
 Athlete athletes[] = {
 {"John Doe", 95},
 {"Jane Smith", 92},
 {"Emily Davis", 87},
 {"Michael Brown", 88},
 {"Jessica Wilson", 90}
 };
 int count = sizeof(athletes) / sizeof(Athlete);
 sortAthletes(athletes, count);
 Athlete expectedAthletes[] = {
 {"John Doe", 95},
 {"Jane Smith", 92},
 {"Jessica Wilson", 90},
 {"Michael Brown", 88},
 {"Emily Davis", 87}
 };
 for (int i = 0; i < count; ++i) {
 assert(strcmp(athletes[i].name, expectedAthletes[i].name) == 0);
 assert(athletes[i].bestResult == expectedAthletes[i].bestResult);
 }
}
void test_createTeam() {
 Athlete athletes[] = {
 {"John Doe", 95},
 {"Jane Smith", 92},
 {"Jessica Wilson", 90},
 {"Michael Brown", 88},
 {"Emily Davis", 87}
 };
 int count = sizeof(athletes) / sizeof(Athlete);
 int n = 3;
 Athlete* team = createTeam(athletes, count, n);
 Athlete expectedTeam[] = {
 {"John Doe", 95},
 {"Jane Smith", 92},
 {"Jessica Wilson", 90}
 };
 for (int i = 0; i < n; ++i) {
 assert(strcmp(team[i].name, expectedTeam[i].name) == 0);
 assert(team[i].bestResult == expectedTeam[i].bestResult);
 }
 free(team);
}
void test_writeTeamToFile() {
 const char* filename = "test_team.bin";
 Athlete team[] = {
 {"John Doe", 95},
 {"Jane Smith", 92},
 {"Jessica Wilson", 90}
 };
27
 int count = sizeof(team) / sizeof(Athlete);
 writeTeamToFile(team, count, filename);
 checkFileContent(filename, team, count);
}
int main() {
    test_createAthletesFile();
    test_sortAthletes();
    test_createTeam();
    test_writeTeamToFile();
    printf("All tests passed successfully.\n");
 return 0;
}