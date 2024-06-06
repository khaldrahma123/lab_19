#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_NAME_LENGTH 50
// Структура для представления информации о товаре на складе
typedef struct {
 char name[MAX_NAME_LENGTH];
 float unitPrice;
 float totalPrice;
 int quantity;
} Product;
// Структура для представления информации о заказе
typedef struct {
 char name[MAX_NAME_LENGTH];
 int quantity;
} Order;
// Функция для чтения товаров из файла
Product* readProducts(const char* filename, int* count) {
 FILE *file = fopen(filename, "rb");
 if (!file) {
 perror("Failed to open file");
 exit(EXIT_FAILURE);
 }
 fread(count, sizeof(int), 1, file); // Читаем количество товаров из файла
 Product *products = (Product*)malloc(*count * sizeof(Product));
 for (int i = 0; i < *count; ++i) {
 fread(&products[i], sizeof(Product), 1, file); // Читаем информацию о
товаре из файла
 }
 fclose(file);
31
 return products;
}
// Функция для чтения заказов из файла
Order* readOrders(const char* filename, int* count) {
 FILE *file = fopen(filename, "rb");
 if (!file) {
 perror("Failed to open file");
 exit(EXIT_FAILURE);
 }
 fread(count, sizeof(int), 1, file); // Читаем количество заказов из файла
 Order *orders = (Order*)malloc(*count * sizeof(Order));
 for (int i = 0; i < *count; ++i) {
 fread(&orders[i], sizeof(Order), 1, file); // Читаем информацию о
заказе из файла
 }
 fclose(file);
 return orders;
}
// Функция для обновления товаров на складе с учетом заказов
Product* updateProducts(Product* products, int* productCount, Order* orders, 
int orderCount) {
 for (int i = 0; i < orderCount; ++i) {
 for (int j = 0; j < *productCount; ++j) {
 if (strcmp(orders[i].name, products[j].name) == 0) {
    products[j].quantity -= orders[i].quantity;
    products[j].totalPrice = products[j].quantity * 
    roducts[j].unitPrice;
 // Если товар отпущен полностью, удаляем запись о нем
 if (products[j].quantity <= 0) {
 for (int k = j; k < *productCount - 1; ++k) {
 products[k] = products[k + 1];
 }
(*productCount)--;
products = (Product*)realloc(products, (*productCount) * 
sizeof(Product));
 j--; // Не увеличиваем j, чтобы проверить новый продукт
на текущем месте
 }
 break;
 }
 }
 }
 return products;
}
// Функция для записи обновленных товаров обратно в файл
void writeProducts(const char* filename, Product* products, int count) {
 FILE *file = fopen(filename, "wb");
 if (!file) {
 perror("Failed to open file");
 exit(EXIT_FAILURE);
 }
 fwrite(&count, sizeof(int), 1, file); // Записываем количество товаров в
файл
 for (int i = 0; i < count; ++i) {
32
 fwrite(&products[i], sizeof(Product), 1, file); // Записываем
информацию о товаре в файл
 }
 fclose(file);
}
// Функция для создания тестового файла с товарами
void createTestProductFile(const char* filename) {
 FILE *file = fopen(filename, "wb");
 if (!file) {
 perror("Failed to open file");
 exit(EXIT_FAILURE);
 }
 Product products[] = {
 {"Product1", 10.0, 100.0, 10},
 {"Product2", 20.0, 200.0, 10},
 {"Product3", 30.0, 300.0, 10}
 };
 int count = sizeof(products) / sizeof(Product);
 fwrite(&count, sizeof(int), 1, file);
 for (int i = 0; i < count; ++i) {
 fwrite(&products[i], sizeof(Product), 1, file);
 }
 fclose(file);
}
// Функция для создания тестового файла с заказами
void createTestOrderFile(const char* filename) {
 FILE *file = fopen(filename, "wb");
 if (!file) {
 perror("Failed to open file");
 exit(EXIT_FAILURE);
 }
 Order orders[] = {
 {"Product1", 5},
 {"Product2", 10}
 };
 int count = sizeof(orders) / sizeof(Order);
 fwrite(&count, sizeof(int), 1, file);
 for (int i = 0; i < count; ++i) {
 fwrite(&orders[i], sizeof(Order), 1, file);
 }
 fclose(file);
}
// Функция для проверки содержимого файла с товарами
void checkProductFile(const char* filename, Product* expectedProducts, int 
expectedCount) {
 int count;
 Product* products = readProducts(filename, &count);
 assert(count == expectedCount);
 for (int i = 0; i < count; ++i) {
 assert(strcmp(products[i].name, expectedProducts[i].name) == 0);
33
 assert(products[i].unitPrice == expectedProducts[i].unitPrice);
 assert(products[i].totalPrice == expectedProducts[i].totalPrice);
 assert(products[i].quantity == expectedProducts[i].quantity);
 }
 free(products);
}
void runTests() {
 const char* productFile = "test_products.bin";
 const char* orderFile = "test_orders.bin";
 createTestProductFile(productFile);
 createTestOrderFile(orderFile);
 int productCount;
 Product* products = readProducts(productFile, &productCount);
 int orderCount;
 Order* orders = readOrders(orderFile, &orderCount);
 products = updateProducts(products, &productCount, orders, orderCount);
 writeProducts(productFile, products, productCount);
 Product expectedProducts[] = {
 {"Product1", 10.0, 50.0, 5},
 {"Product3", 30.0, 300.0, 10}
 };
 int expectedCount = sizeof(expectedProducts) / sizeof(Product);
 checkProductFile(productFile, expectedProducts, expectedCount);
 free(products);
 free(orders);
 printf("All tests passed successfully.\n");
}
int main() {
 runTests();
 return 0;
}