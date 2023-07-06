#pragma once
#ifndef ROUTER_H
#define ROUTER_H

#include "servicess.h"
#include "window.h"

//������¼���棬��������ֵ�����½ʧ�ܣ�����Ա��¼��˿͵�¼
int SysLogin(MYSQL* conn);
// ����һ�����������ڻ�ȡ����̨�Ŀ��
int get_console_width();
// ����һ�����������ڼ����ʽ���ַ����ĳ���
int get_format_length(const char* format, ...);
// ����һ�����������ھ��в��á�+�����������ʽ���ַ���
void PrintfWrap(const char* format, ...);
// ����һ�����������ھ��������ʽ���ַ���
void PrintfInMiddle(const char* format, ...);
// �����ݿ��ж�ȡname��phone�ֶεĺ���
void ReadData(MYSQL* conn, const char* table, char(*name)[100], char(*phone)[100]);
// �ж��û������name��phone�Ƿ���ȷ�ĺ���
int CheckInput(MYSQL* conn, char(*name)[100], char(*phone)[100], int index, char* input_name, char* input_phone);
// �˿ͽ���
void customerPage(MYSQL* conn);
// ���ø�ʽ����ʾ�û������Ŀ¼��ѡ�������ʹ��ÿ��ѡ��Ҫ�����intֵ
// E.G. NewSwitch("Please enter a number:\n 1.ali\n 2.bite\n 3.code\n 4.docker", 4, 1, 2, 3, 4);
int NewSwitch(const char* str, int count, ...);

#endif // !CONTROLLER_H