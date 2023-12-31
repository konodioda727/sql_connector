#include "../headers/router.h"

int SysLogin(MYSQL* conn) {

	PrintfWrap("商品管理系统");

	//定义两个二维字符数组，用于存储name和phone字段
	char customer_name[100][100];
	char customer_phone[20][100];
	char employee_name[100][100];
	char employee_phone[20][100];

	//读取conn所指向的数据库中的employees和customers表，分别读取其中的name，phone字段，按照相同的索引保存在传入的二维数组中
	ReadData(conn, "employees", employee_name, employee_phone);
	ReadData(conn, "customers", customer_name, customer_phone);

	//用一个变量记录最后一个employees数据的索引，以便成功登录时判断登陆上的是管理员账号还是用户账号
	int last_employee_index = -1;
	for (int i = 0; i < 100; i++) {
		if (strlen(employee_name[i]) >= 100) {
			last_employee_index = i - 1;
			break;
		}
	}

	//在控制台一行一行输出每一个name和phone
	//printf("Employees:\n");
	for (int i = 0; i <= last_employee_index; i++) {
		if (strlen(employee_name[i]) >= 100) {
			break;
		}
		//printf("[Emp]\n[NAME]%s\n[PHONE]%s\n", employee_name[i], employee_phone[i]);
	}
	//printf("Customers:\n");
	for (int i = 0; i < 100; i++) {
		if (strlen(customer_name[i]) >= 100) {
			break;
		}
		//printf("[Cst]\n[NAME]%s\n[PHONE]%s\n", customer_name[i], customer_phone[i]);
	}

	//要求用户依次输入name和phone值
	char input_name[100];
	char input_phone[20];
	printf("请输入您的账户名：\n");
	fflush(stdin);
	gets_s(input_name);
	printf("请输入您的手机号：\n");
	fflush(stdin);
	gets_s(input_phone);

	int result = CheckInput(conn, customer_name, customer_phone, last_employee_index, input_name, input_phone);
	if (result == -1)
	{
		result = CheckInput(conn, employee_name, employee_phone, last_employee_index, input_name, input_phone);
	}

	while (result != 0) {
		if (result == -1) {
			PrintfInMiddle("不存在此账户，请重新输入。\n");
		}
		else if (result == -2) {
			PrintfInMiddle("密码错误，请重新输入。\n");
		}
		printf("请输入您的账户名：\n");
		fflush(stdin);
		gets_s(input_name);
		printf("请输入您的手机号：\n");
		fflush(stdin);
		gets_s(input_phone);
		result = CheckInput(conn, customer_name, customer_phone, last_employee_index, input_name, input_phone);
		if (result == -1)
		{
			result = CheckInput(conn, employee_name, employee_phone, last_employee_index, input_name, input_phone);
		}
	}

	if (result == 0) {
		int is_employee = -1;
		for (int i = 0; i <= last_employee_index; i++) {
			if (strcmp(input_name, employee_name[i]) == 0 && strcmp(input_phone, employee_phone[i]) == 0) {
				is_employee = i;
				break;
			}
		}
		if (is_employee != -1) {
			PrintfWrap("欢迎管理员 %s 登录系统。", input_name);
			return 2;
		}
		else {
			PrintfWrap("欢迎用户 %s 登录系统。", input_name);
			return 1;
		}
	}
	return 0;
}

//从数据库中读取name和phone字段的函数
void ReadData(MYSQL* conn, const char* table, char(*name)[100], char(*phone)[100]) {
	//定义一个语句句柄
	MYSQL_STMT* stmt = mysql_stmt_init(conn);
	//定义一个SQL语句，用于查询指定表的name和phone字段
	char sql[100];
	sprintf(sql, "SELECT name, phone FROM %s", table);
	//准备SQL语句
	mysql_stmt_prepare(stmt, sql, strlen(sql));
	//执行SQL语句
	mysql_stmt_execute(stmt);
	//绑定结果集的列到变量
	MYSQL_BIND bind[2];
	memset(bind, 0, sizeof(bind));
	bind[0].buffer_type = MYSQL_TYPE_STRING;
	bind[0].buffer = (char*)malloc(100);
	bind[0].buffer_length = 100;
	bind[1].buffer_type = MYSQL_TYPE_STRING;
	bind[1].buffer = (char*)malloc(20);
	bind[1].buffer_length = 20;
	mysql_stmt_bind_result(stmt, bind);
	//遍历结果集，将数据存储到二维字符数组中
	int i = 0;
	while (mysql_stmt_fetch(stmt) == 0) {
		strcpy(name[i], (char*)bind[0].buffer);
		strcpy(phone[i], (char*)bind[1].buffer);
		i++;
	}
	//释放结果集和语句句柄
	mysql_stmt_free_result(stmt);
	mysql_stmt_close(stmt);
}

//判断用户输入的name和phone是否正确的函数
int CheckInput(MYSQL* conn, char(*name)[100], char(*phone)[100], int index, char* input_name, char* input_phone) {
	//定义一个标志变量，用于返回结果
	int flag = -1; //-1表示不存在此账户，-2表示密码错误，0表示正确
	//遍历二维字符数组，查找是否有匹配的name和phone
	for (int i = 0; i < index + 100; i++) {
		if (strcmp(input_name, name[i]) == 0) { //找到匹配的name
			flag = -2; //假设密码错误
			if (strcmp(input_phone, phone[i]) == 0) { //找到匹配的phone
				flag = 0; //正确
				break;
			}
		}
	}
	return flag;
}

int get_console_width() {
	CONSOLE_SCREEN_BUFFER_INFO csbi; // 定义一个结构体，用于存储控制台的信息
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi); // 调用Windows API函数，获取控制台的信息，并存储到结构体中
	return csbi.srWindow.Right - csbi.srWindow.Left + 1; // 返回控制台的宽度
}

// 定义一个函数，用于计算格式化字符串的长度
int get_format_length(const char* format, ...) {
	va_list args; // 定义一个可变参数列表
	va_start(args, format); // 初始化可变参数列表
	char buffer[1024]; // 定义一个缓冲区，用于存储格式化后的字符串
	int length = vsnprintf(buffer, sizeof(buffer), format, args); // 使用vsnprintf函数将可变参数格式化为字符串，并返回其长度
	va_end(args); // 结束可变参数列表
	return length; // 返回格式化字符串的长度
}

// 定义一个函数，用于居中并用“+”包裹输出格式化字符串
void PrintfWrap(const char* format, ...) {
	va_list args; // 定义一个可变参数列表
	va_start(args, format); // 初始化可变参数列表
	char buffer[1024]; // 定义一个缓冲区，用于存储格式化后的字符串
	vsnprintf(buffer, sizeof(buffer), format, args); // 使用vsnprintf函数将可变参数格式化为字符串，并存储到缓冲区中
	va_end(args); // 结束可变参数列表

	int length = strlen(buffer); // 获取格式化字符串的长度
	int screen_width = get_console_width(); // 获取控制台的宽度
	int left = (screen_width - length - 2) / 2; // 计算左边需要输出的空格数
	int right = screen_width - length - 2 - left; // 计算右边需要输出的空格数

	for (int i = 0; i < screen_width; i++) { // 输出上边的“+”
		printf("+");
	}
	printf("\n"); // 输出换行符

	printf("+"); // 输出左上角的“+”
	for (int i = 0; i < left; i++) { // 输出左边的空格
		printf(" ");
	}
	printf("%s", buffer); // 输出格式化字符串
	for (int i = 0; i < right; i++) { // 输出右边的空格
		printf(" ");
	}
	printf("+\n"); // 输出右上角的“+”和换行符

	for (int i = 0; i < screen_width; i++) { // 输出下边的“+”
		printf("+");
	}
	printf("\n"); // 输出换行符
}

// 定义一个函数，用于居中输出格式化字符串
void PrintfInMiddle(const char* format, ...) {
	va_list args; // 定义一个可变参数列表
	va_start(args, format); // 初始化可变参数列表
	char buffer[1024]; // 定义一个缓冲区，用于存储格式化后的字符串
	vsnprintf(buffer, sizeof(buffer), format, args); // 使用vsnprintf函数将可变参数格式化为字符串，并存储到缓冲区中
	va_end(args); // 结束可变参数列表

	int length = strlen(buffer); // 获取格式化字符串的长度
	int screen_width = get_console_width(); // 获取控制台的宽度
	int left = (screen_width - length) / 2; // 计算左边需要输出的空格数

	for (int i = 0; i < left; i++) { // 输出左边的空格
		printf(" ");
	}
	printf("%s\n", buffer); // 输出格式化字符串和换行符
}

// 定义一个函数，用于判断一个字符串是否是整数
int isInteger(const char* str) {
	char* endptr; // 定义一个指针，用于存储转换后的字符串的结束位置
	strtol(str, &endptr, 10); // 使用strtol函数尝试将字符串转换为整数，并传入10表示十进制
	return *endptr == '\0'; // 如果转换后的字符串的结束位置是空字符，说明字符串是整数，返回1；否则返回0
}

// 定义一个函数，用于判断一个整数是否在可变参数列表中
int isInList(int num, int count, va_list args) {
	for (int i = 0; i < count; i++) { // 遍历可变参数列表中的每个整数
		int arg = va_arg(args, int); // 使用va_arg宏获取可变参数列表中的下一个整数
		if (num == arg) { // 如果输入的整数和可变参数列表中的某个整数相等
			return 1; // 返回1
		}
	}
	return 0; // 如果输入的整数和可变参数列表中的所有整数都不相等，返回0
}

// 定义一个函数，该函数接受一个字符串，可变参数个数和一个可变参数列表，该函数将先输出接受的字符串，
// 然后等待用户输入整形数字，
// 若用户输入的值不是整形数字或者不是传入整形数字的其中一个，则打印“输入格式错误”，并要求用户再次输入（不要使用递归），
// 若成功则返回用户输入的整形数，依次类推
int NewSwitch(const char* str, int count, ...) {
	printf("%s", str); // 输出接受的字符串

	char buffer[1024]; // 定义一个缓冲区，用于存储用户输入的字符串
	fgets(buffer, sizeof(buffer), stdin); // 使用fgets函数读取用户输入的字符串，并存储到缓冲区中
	buffer[strcspn(buffer, "\n")] = '\0'; // 去掉buffer中的'\n'字符

	va_list args; // 定义一个可变参数列表
	va_start(args, count); // 初始化可变参数列表

	while (!isInteger(buffer) || !isInList(atoi(buffer), count, args)) { // 如果用户输入的值不是整数或者不是传入整形数字的其中一个
		printf("输入格式错误\n"); // 打印“输入格式错误”
		printf("%s", str); // 输出接受的字符串
		fgets(buffer, sizeof(buffer), stdin); // 使用fgets函数读取用户输入的字符串，并存储到缓冲区中
		buffer[strcspn(buffer, "\n")] = '\0'; // 去掉buffer中的'\n'字符

		va_list args_copy; // 定义一个新的可变参数列表
		va_copy(args_copy, args); // 使用va_copy宏复制原来的可变参数列表
		va_end(args); // 结束原来的可变参数列表

		args = args_copy; // 将新的可变参数列表赋值给args
	}

	int num = atoi(buffer); // 将用户输入的字符串转换为整数

	va_end(args); // 结束可变参数列表

	return num; // 返回用户输入的整数
}


void customerPage(MYSQL* conn) {
	// 等待一秒
	Sleep(1000);
	// 清空控制台
	system("cls");
	PrintfWrap("Costomer Mode");
	int CB = NewSwitch("请选择要进行的操作:\n 1.选择商品\n 2.结算\n 3.购物车\n", 3, 1, 2, 3);
	printf("%d", CB);
}