#include "../headers/controller.h"
#include "../headers/geneStr.h"
#include "../headers/utils.h"


void Customer(MYSQL* conn) {
    MYSQL* row;
    char product_id[20] = "1", query[200] = "", query2[200] = "";
    float sum = 0;int num = 0, count = 0;
    char tabs[280];
    int id = 0, product_num;
    char time[50];
    while (1) {
        printf("\nenter a numebr (-1 to quit): ");
        scanf("%d", &num);

        if (num == -1) {
            return;
        }
        SelectPrint(conn, "SELECT product_id,name,price FROM products");
        printf("\nselect id: ");
        scanf("%s", product_id);getchar();
        printf("\nselect numbers: ");
        scanf("%d", &product_num);getchar();
        Product(product_id, "price", query);
        Product(product_id, "stock", query2);
        const char* prc = getValueFromTable(conn, query, "price");
        const char* sto = getValueFromTable(conn, query2, "stock");
        float price = strToFloat(prc);
        
        int stock = atoi(sto);
        sum += price * product_num;
        printf("\ntotal:%f", sum);
        if (!count) {
            getTime(time);
            printf("time:%s\n",time);
            sprintf(tabs, "INSERT INTO orders (customer_id,order_date,total_amount) VALUES('%d', '%s', '%.2f')", 1, time, sum);
            Query(conn, tabs);
            id = getLastInsertId(conn);
        }
        else {
            sprintf(tabs, "UPDATE orders SET total_amount = '%.2f' WHERE order_id = %d",sum,id);
            Query(conn, tabs);
        }
        sprintf(tabs,"INSERT INTO order_items (order_id,product_id,quantity) VALUES(%d, %s, %d)",id,product_id,product_num);
        Query(conn, tabs);
        sprintf(tabs, "UPDATE products SET stock=%d WHERE id=%s", stock-product_num,product_id);
        Query(conn, tabs);
        count++;
    }
}
void DaySelling(MYSQL* conn) {
    const char* str[30] = {
        "order_date",
        NULL
    };
    const char* func[50] = { 
        "SUM(total_amount) AS total",
        "COUNT(*) AS order_amount"
    };
    char* res = DaySelling(str, func);
    SelectPrint(conn, res);
}
void ProductSelling() {

}