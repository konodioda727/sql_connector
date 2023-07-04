#pragma once
#ifndef ADD_H
#define ADD_H

#include "mysql.h" 
#include <stdio.h>
#include <string.h>

void Arr2Str(char* result, const char* str[]);
void AddTab(char* result, const char* add);
void AddTab(char* result, const char* addname, const char* addbody);
void AddTab(char* result, const char* type,const char* str[]);
char* DaySelling(const char* rows[], const char* function);
//void DaySelling(const char* rows[]);
#endif // !CONNECTION_H
