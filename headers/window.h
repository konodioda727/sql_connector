#pragma once
#include "servicess.h"

void Shop(MYSQL* conn, char* product_id, int* product_num, int* num);
void Stock_Insert(char* name, float* income_price, float* outcome_price, int* stock, int* num);
void Shopping_Cart(int* order_item_id);
int DeleteShopping_Cart();
void OrderPrintAll(MYSQL* conn);
void OrderPrintOne(MYSQL* conn, char* query);