#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <time.h>

void getTime(char* timeString);
float strToFloat(const char* str);

void Arr2Str(char* result, const char* str[]);
void AddTab(char* result, const char* add);
void AddTab(char* result, const char* addname, const char* addbody);
void AddTab(char* result, const char* type, const char* str[]);

