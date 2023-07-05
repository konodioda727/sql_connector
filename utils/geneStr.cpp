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
void Product(const char* product_id, const char* product_row, char* string) {
    char* str = string;
    sprintf(str, "SELECT %s FROM products WHERE product_id=%s;", product_row, product_id);
}
void ProductTotal(const char* rows[], const char* functions[], char* string) {
    char* str = string;
    AddTab(str, "SELECT", rows);
    AddTab(str, ",", functions);
    AddTab(str, "FROM", "order_items JOIN products ON products.product_id=order_items.product_id");
    AddTab(str, "GROUP BY", rows);
    AddTab(str, "ORDER BY total_amount DESC");
}
void PrintOne(char* query) {
    char* str = query;
    sprintf(query, "SELECT customer_id,order_date,total_amount,name,price,stock FROM orders JOIN products ON orders.product_id = products.product_id WHERE %s",query);
}