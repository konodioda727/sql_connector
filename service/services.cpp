#include "../headers/servicess.h"

MYSQL* CreateConnection(const char* basename) {
    MYSQL* conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "root", "2328", basename, 3306, NULL, 0)) {
        printf("\nERR: CONNECTION FAILED\n");
        conn = mysql_init(NULL);
        if (mysql_real_connect(conn, "localhost", "root", "2328", "market_managment", 3306, NULL, 0)) {
            char query[50] = "CREATE DATABASE";
            char use[50] = "USE";
            AddTab(use, basename);
            AddTab(query, basename);
            Query(conn, query);
            Query(conn, use);
            return conn;
        } 
        return NULL;
    }
    printf("\nCONNECTED\n");
    return conn;
}
int Query(MYSQL* conn, const char query[]) {
    int status = mysql_query(conn, query);
    if (status == 0) {
        return 1;
    }
    printf("\nERR SENTENCE: %s\n", query);
    printf("\nERR: FAILED TO EXCUTE QUERY\n");
    
    return 0;
}
void ReadRow(MYSQL_RES* result) {
    MYSQL_ROW row;
    MYSQL_FIELD* field;
    if (result != NULL) {
        int numFields = mysql_num_fields(result);
        printf("Table:\n");
        while ((field = mysql_fetch_field(result))) {
            printf("%20s\t", field->name);
        }
        printf("\n");
        while ((row = mysql_fetch_row(result))) {
            for (int i = 0; i < numFields; ++i) {
                printf("%20s\t", row[i] ? row[i] : "NULL");
            }
            printf("\n");
        }
        mysql_free_result(result);
    }
    else
        printf("\nERR: RESULT IS EMPTY\n");
}
char* getValueFromTable(MYSQL* conn, const char* query, const char* fieldName) {

    if (mysql_query(conn, query) != 0) {
        printf("MySQL query failed: %s\n", mysql_error(conn));
        return NULL;
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (result == NULL) {
        printf("MySQL result retrieval failed: %s\n", mysql_error(conn));
        return NULL;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL) {
        printf("No data found.\n");
        mysql_free_result(result);
        return NULL;
    }

    char* value = _strdup(row[0]);

    mysql_free_result(result);

    return value;
}
void FreeResult(MYSQL_RES* result) {
    mysql_free_result(result);
    printf("\nFREED RESULT SUCCESSFULLY\n");
}
unsigned long long getLastInsertId(MYSQL* conn) {
    unsigned long long lastInsertId = 0;
    mysql_query(conn, "SELECT LAST_INSERT_ID();");
    MYSQL_RES* result = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row != NULL) {
        lastInsertId = strtoull(row[0], NULL, 10);
    }
    mysql_free_result(result);
    return lastInsertId;
}
int getid(MYSQL* conn, const char* table, const char* field) {
    char str[80];
    sprintf(str, "SELECT MAX(%s) FROM %s", field, table);
    const char* res = getValueFromTable(conn, str, field);
    int ret = atoi(res) + 1;
    return ret;
}
int emptyornot(MYSQL* conn, const char* query) {
    if (mysql_query(conn, query) == 0) {
        MYSQL_RES* result = mysql_store_result(conn);
        if (result != NULL) {
            // 获取查询结果成功

            // 获取结果集中的行数
            unsigned long num_rows = mysql_num_rows(result);

            if (num_rows > 0) {
                return 1;
            }

            // 释放结果集
            mysql_free_result(result);
        }
        
    }
    return 0;
}

MYSQL_RES* Select(MYSQL* conn, const char query[]) {
    MYSQL_RES* result;
    Query(conn, query);
    result = mysql_use_result(conn);
    if (result == NULL) {
        printf("\nERR: SYNTAX ERROR OR NO SUCH DATA\n");
        return NULL;
    }
    return result;
}
void SelectPrint(MYSQL* conn, const char query[]) {
    MYSQL_RES* result = Select(conn, query);
    ReadRow(result);
    //FreeResult(result);
}
void Delete(MYSQL* conn, const char table[], const char query[]) {
    char str[50] = "DELETE FROM";
    AddTab(str, table);
    AddTab(str, "WHERE");
    AddTab(str, query);
    Query(conn, str);
}
void Insert(MYSQL* conn, const char table[], const char* key[], const char* value[]) {
    char str[50] = "INSERT INTO";
    AddTab(str, table);
    Arr2Str(str, key);
    AddTab(str, "VALUES");
    Arr2Str(str, value);
    Query(conn, str);
}
void Update(MYSQL* conn, const char table[], const char value_set[], const char condition[]) {
    char str[50] = "UPDATE";
    AddTab(str, table);
    AddTab(str, "SET", value_set);
    AddTab(str, "WHERE", condition);
    Query(conn, str);
}

