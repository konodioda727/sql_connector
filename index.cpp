
#include "headers/servicess.h"
#include "headers/geneStr.h"
#include "headers/controller.h"


//MYSQL* conn;           // MySQL 连接对象
//MYSQL_RES* result;     // 结果集对象
//MYSQL_ROW row;         // 结果集中的一行数据


int main() {
	MYSQL* conn = CreateConnection("market_managment");
	//Customer(conn);
	DaySelling(conn);
	mysql_close(conn);
}



