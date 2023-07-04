#include "../headers/servicess.h"

MYSQL* CreateConnection(const char* basename) {
    MYSQL* conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "root", "Ak472700", basename, 3306, NULL, 0)) {
        printf("\nERR: CONNECTION FAILED\n");
        conn = mysql_init(NULL);
        if (mysql_real_connect(conn, "localhost", "root", "Ak472700", "mysql", 3306, NULL, 0)) {
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
        printf("\nQuery Success\n");
        int affected_rows = mysql_affected_rows(conn);
        if (affected_rows != -1)
            printf("Affected %d rows\n", affected_rows);
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
    }
    else
        printf("\nERR: RESULT IS EMPTY\n");
}
void FreeResult(MYSQL_RES* result) {
    mysql_free_result(result);
    printf("\nFREED RESULT SUCCESSFULLY\n");
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
    FreeResult(result);
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

void UserPayment(MYSQL* conn) {
    printf("select types");
    scanf("%s");
}