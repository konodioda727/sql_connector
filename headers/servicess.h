#pragma once
#ifndef SERVICESS_H
#define SERVICESS_H

#include "utils.h"
#include "mysql.h" 


MYSQL* CreateConnection(const char* basename);
int Query(MYSQL* conn, const char query[]);
void ReadRow(MYSQL_RES* result);
void FreeResult(MYSQL_RES* result);
unsigned long long getLastInsertId(MYSQL* conn);
char* getValueFromTable(MYSQL* conn, const char* query, const char* fieldName);
int getid(MYSQL* conn, const char* table, const char* field);
int emptyornot(MYSQL* conn, const char* query);

MYSQL_RES* Select(MYSQL* conn, const char query[]);
void SelectPrint(MYSQL* conn, const char query[]);
void Delete(MYSQL* conn, const char table[], const char query[]);
void Insert(MYSQL* conn, const char table[], const char* key[], const char* value[]);
void Update(MYSQL* conn, const char table[], const char value_set[], const char condition[]);


#endif // !METHOD_H
