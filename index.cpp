
#include "headers/servicess.h"
#include "headers/geneStr.h"
#include "headers/controller.h"
#include "headers/router.h"


//MYSQL* conn;           // MySQL 连接对象
//MYSQL_RES* result;     // 结果集对象
//MYSQL_ROW row;         // 结果集中的一行数据


int main() {
	MYSQL* conn = CreateConnection("market_managment");

	//测试登录数据库获取以及输入字段匹配
	SysLogin(conn);

	//商品总销售额
	//ProductSelling(conn);
	// 每日销售额
	//DaySelling(conn);
	// 从购物车删除
	//DeleteShoppingCart(conn, 1);
	// 购物
	//Shopping(conn);
	// 修改库存
	//EditingStock(conn);
	OrderPrintAll(conn);
	mysql_close(conn);
}



