
#include "headers/servicess.h"
#include "headers/geneStr.h"
#include "headers/controller.h"
#include "headers/router.h"


//MYSQL* conn;           // MySQL 连接对象
//MYSQL_RES* result;     // 结果集对象
//MYSQL_ROW row;         // 结果集中的一行数据


int main() {
	MYSQL* conn = CreateConnection("market_managment");

	// 登录数据库获取以及输入字段匹配
	int userType = SysLogin(conn);
	//在副作用中完成登录IO，返回值为2代表管理员登录，返回值为1代表用户登录
	switch (userType) {
	case 1:
		customerPage(conn);
		break;
	case 2:
		break;
	default:
		PrintfInMiddle("ERROR");
		break;
	}

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



