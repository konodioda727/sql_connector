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

#endif // !CONTROLLER_H