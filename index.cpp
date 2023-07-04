
#include "headers/servicess.h"
#include "headers/geneStr.h"


//MYSQL* conn;           // MySQL 连接对象
//MYSQL_RES* result;     // 结果集对象
//MYSQL_ROW row;         // 结果集中的一行数据


int main() {
	MYSQL* conn = CreateConnection("market_managment");
	const char* str[30] = {
		"order_items.order_id",
		"order_date",
		NULL
	};
	const char* func = "SUM(quantity * item_price) AS sum";
	char *res = DaySelling(str, func);
	SelectPrint(conn, res);
	mysql_close(conn);
	
}



