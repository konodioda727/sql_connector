#include "../headers/geneStr.h"
#include "../headers/utils.h"

char* DaySelling(const char* rows[], const char* functions[]) {
    char str[300] = "";
    AddTab(str, "SELECT", rows);
    AddTab(str,",", functions);
    AddTab(str, "FROM", "orders");
    AddTab(str, "GROUP BY", rows);
    return str;
}
char* Product(const char* product_id, const char* product_row, char* string) {
    char* str = string;
    sprintf(str, "SELECT %s FROM products WHERE product_id=%s;", product_row, product_id);
    return str;
}
