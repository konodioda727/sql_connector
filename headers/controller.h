#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "geneStr.h"
#include "servicess.h"
#include "utils.h"

void DaySelling(MYSQL* conn);
void Shopping(MYSQL* conn);
void ProductSelling(MYSQL* conn);
void InsertStock(MYSQL* conn,int* num);
void EditingStock(MYSQL* conn);
void DeleteShoppingCart(MYSQL* conn, int id);
void OrderPrintAll(MYSQL* conn);
void OrderPrintOne(MYSQL* conn, char* query);

#endif // !CONTROLLER_H
