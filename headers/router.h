#pragma once
#ifndef ROUTER_H
#define ROUTER_H

#include "servicess.h"
#include "window.h"

//新增登录界面，返回整形值代表登陆失败，管理员登录或顾客登录
int SysLogin(MYSQL* conn);
// 定义一个函数，用于获取控制台的宽度
int get_console_width();
// 定义一个函数，用于计算格式化字符串的长度
int get_format_length(const char* format, ...);
// 定义一个函数，用于居中并用“+”包裹输出格式化字符串
void PrintfWrap(const char* format, ...);
// 定义一个函数，用于居中输出格式化字符串
void PrintfInMiddle(const char* format, ...);
// 从数据库中读取name和phone字段的函数
void ReadData(MYSQL* conn, const char* table, char(*name)[100], char(*phone)[100]);
// 判断用户输入的name和phone是否正确的函数
int CheckInput(MYSQL* conn, char(*name)[100], char(*phone)[100], int index, char* input_name, char* input_phone);
// 顾客界面
void customerPage(MYSQL* conn);
// 调用格式：提示用户输入的目录，选项个数，使用每个选项要输入的int值
// E.G. NewSwitch("Please enter a number:\n 1.ali\n 2.bite\n 3.code\n 4.docker", 4, 1, 2, 3, 4);
int NewSwitch(const char* str, int count, ...);

#endif // !CONTROLLER_H