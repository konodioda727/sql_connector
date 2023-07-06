#include "../headers/router.h"
void customerPage(MYSQL* conn) {
    // �ȴ�һ��
    Sleep(2000);
    // ��տ���̨
    system("cls");
    PrintfWrap("Costomer Mode");
}

//���Ժ���
int SysLogin(MYSQL* conn) {

    PrintfWrap("��Ʒ����ϵͳ");

    //����������ά�ַ����飬���ڴ洢name��phone�ֶ�
    char customer_name[100][100];
    char customer_phone[20][100];
    char employee_name[100][100];
    char employee_phone[20][100];

    //��ȡconn��ָ������ݿ��е�employees��customers���ֱ��ȡ���е�name��phone�ֶΣ�������ͬ�����������ڴ���Ķ�ά������
    ReadData(conn, "employees", employee_name, employee_phone);
    ReadData(conn, "customers", customer_name, customer_phone);

    //��һ��������¼���һ��employees���ݵ��������Ա�ɹ���¼ʱ�жϵ�½�ϵ��ǹ���Ա�˺Ż����û��˺�
    int last_employee_index = -1;
    for (int i = 0; i < 100; i++) {
        if (strlen(employee_name[i]) >= 100) {
            last_employee_index = i - 1;
            break;
        }
    }

    //�ڿ���̨һ��һ�����ÿһ��name��phone
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

    //Ҫ���û���������name��phoneֵ
    char input_name[100];
    char input_phone[20];
    printf("�����������˻�����\n");
    fflush(stdin);
    gets_s(input_name);
    printf("�����������ֻ��ţ�\n");
    fflush(stdin);
    gets_s(input_phone);

    int result = CheckInput(conn, customer_name, customer_phone, last_employee_index, input_name, input_phone);
    if (result == -1)
    {
        result = CheckInput(conn, employee_name, employee_phone, last_employee_index, input_name, input_phone);
    }

    while (result != 0) {
        if (result == -1) {
            PrintfInMiddle("�����ڴ��˻������������롣\n");
        }
        else if (result == -2) {
            PrintfInMiddle("����������������롣\n");
        }
        printf("�����������˻�����\n");
        fflush(stdin);
        gets_s(input_name);
        printf("�����������ֻ��ţ�\n");
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
            PrintfWrap("��ӭ����Ա %s ��¼ϵͳ��", input_name);
            return 2;
        }
        else {
            PrintfWrap("��ӭ�û� %s ��¼ϵͳ��", input_name);
            return 1;
        }
    }
    return 0;
}

//�����ݿ��ж�ȡname��phone�ֶεĺ���
void ReadData(MYSQL* conn, const char* table, char(*name)[100], char(*phone)[100]) {
    //����һ�������
    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    //����һ��SQL��䣬���ڲ�ѯָ�����name��phone�ֶ�
    char sql[100];
    sprintf(sql, "SELECT name, phone FROM %s", table);
    //׼��SQL���
    mysql_stmt_prepare(stmt, sql, strlen(sql));
    //ִ��SQL���
    mysql_stmt_execute(stmt);
    //�󶨽�������е�����
    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char*)malloc(100);
    bind[0].buffer_length = 100;
    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char*)malloc(20);
    bind[1].buffer_length = 20;
    mysql_stmt_bind_result(stmt, bind);
    //����������������ݴ洢����ά�ַ�������
    int i = 0;
    while (mysql_stmt_fetch(stmt) == 0) {
        strcpy(name[i], (char*)bind[0].buffer);
        strcpy(phone[i], (char*)bind[1].buffer);
        i++;
    }
    //�ͷŽ�����������
    mysql_stmt_free_result(stmt);
    mysql_stmt_close(stmt);
}

//�ж��û������name��phone�Ƿ���ȷ�ĺ���
int CheckInput(MYSQL* conn, char(*name)[100], char(*phone)[100], int index, char* input_name, char* input_phone) {
    //����һ����־���������ڷ��ؽ��
    int flag = -1; //-1��ʾ�����ڴ��˻���-2��ʾ�������0��ʾ��ȷ
    //������ά�ַ����飬�����Ƿ���ƥ���name��phone
    for (int i = 0; i < index + 100; i++) {
        if (strcmp(input_name, name[i]) == 0) { //�ҵ�ƥ���name
            flag = -2; //�����������
            if (strcmp(input_phone, phone[i]) == 0) { //�ҵ�ƥ���phone
                flag = 0; //��ȷ
                break;
            }
        }
    }
    return flag;
}

int get_console_width() {
    CONSOLE_SCREEN_BUFFER_INFO csbi; // ����һ���ṹ�壬���ڴ洢����̨����Ϣ
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi); // ����Windows API��������ȡ����̨����Ϣ�����洢���ṹ����
    return csbi.srWindow.Right - csbi.srWindow.Left + 1; // ���ؿ���̨�Ŀ��
}

// ����һ�����������ڼ����ʽ���ַ����ĳ���
int get_format_length(const char* format, ...) {
    va_list args; // ����һ���ɱ�����б�
    va_start(args, format); // ��ʼ���ɱ�����б�
    char buffer[1024]; // ����һ�������������ڴ洢��ʽ������ַ���
    int length = vsnprintf(buffer, sizeof(buffer), format, args); // ʹ��vsnprintf�������ɱ������ʽ��Ϊ�ַ������������䳤��
    va_end(args); // �����ɱ�����б�
    return length; // ���ظ�ʽ���ַ����ĳ���
}

// ����һ�����������ھ��в��á�+�����������ʽ���ַ���
void PrintfWrap(const char* format, ...) {
    va_list args; // ����һ���ɱ�����б�
    va_start(args, format); // ��ʼ���ɱ�����б�
    char buffer[1024]; // ����һ�������������ڴ洢��ʽ������ַ���
    vsnprintf(buffer, sizeof(buffer), format, args); // ʹ��vsnprintf�������ɱ������ʽ��Ϊ�ַ��������洢����������
    va_end(args); // �����ɱ�����б�

    int length = strlen(buffer); // ��ȡ��ʽ���ַ����ĳ���
    int screen_width = get_console_width(); // ��ȡ����̨�Ŀ��
    int left = (screen_width - length - 2) / 2; // ���������Ҫ����Ŀո���
    int right = screen_width - length - 2 - left; // �����ұ���Ҫ����Ŀո���

    for (int i = 0; i < screen_width; i++) { // ����ϱߵġ�+��
        printf("+");
    }
    printf("\n"); // ������з�

    printf("+"); // ������Ͻǵġ�+��
    for (int i = 0; i < left; i++) { // �����ߵĿո�
        printf(" ");
    }
    printf("%s", buffer); // �����ʽ���ַ���
    for (int i = 0; i < right; i++) { // ����ұߵĿո�
        printf(" ");
    }
    printf("+\n"); // ������Ͻǵġ�+���ͻ��з�

    for (int i = 0; i < screen_width; i++) { // ����±ߵġ�+��
        printf("+");
    }
    printf("\n"); // ������з�
}

// ����һ�����������ھ��������ʽ���ַ���
void PrintfInMiddle(const char* format, ...) {
    va_list args; // ����һ���ɱ�����б�
    va_start(args, format); // ��ʼ���ɱ�����б�
    char buffer[1024]; // ����һ�������������ڴ洢��ʽ������ַ���
    vsnprintf(buffer, sizeof(buffer), format, args); // ʹ��vsnprintf�������ɱ������ʽ��Ϊ�ַ��������洢����������
    va_end(args); // �����ɱ�����б�

    int length = strlen(buffer); // ��ȡ��ʽ���ַ����ĳ���
    int screen_width = get_console_width(); // ��ȡ����̨�Ŀ��
    int left = (screen_width - length) / 2; // ���������Ҫ����Ŀո���

    for (int i = 0; i < left; i++) { // �����ߵĿո�
        printf(" ");
    }
    printf("%s\n", buffer); // �����ʽ���ַ����ͻ��з�
}
