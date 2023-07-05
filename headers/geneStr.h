#pragma once
#ifndef GENESTR_H
#define GENESTR_H

#include "geneStr.h"

char* DaySelling(const char* rows[], const char* functions[]);
void Product(const char* product_id, const char* product_row, char* string);
void ProductTotal(const char* rows[], const char* functions[], char* string);
void PrintOne(char* query);
#endif // !GENESTR_H
