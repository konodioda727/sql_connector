#include "../headers/geneStr.h"

char* DaySelling(const char* rows[], const char* function) {
    char str[300] = "";
    AddTab(str, "SELECT", rows);
    strcat(str, ",");
    AddTab(str, function);
    AddTab(str, "FROM", "order_items");
    AddTab(str, "JOIN orders ON order_items.order_id = orders.order_id");
    AddTab(str, "GROUP BY", rows);
    return str;
}