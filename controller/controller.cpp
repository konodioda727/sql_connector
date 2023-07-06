#include "../headers/controller.h"
#include "../headers/geneStr.h"
#include "../headers/utils.h"
#include "../headers/window.h"

void Shopping(MYSQL* conn) {
    MYSQL* row;
    char product_id[20] = "1", query[200] = "", query2[200] = "";
    float sum = 0;int num = 0, count = 0;
    char tabs[280];
    int id = 0, product_num;
    char time[50];
    while (1) {
        Shop(conn,product_id, &product_num, &num);
        if (num == -1) {
            return;
        }
        Product(product_id, "price", query);
        Product(product_id, "stock", query2);
        const char* prc = getValueFromTable(conn, query, "price");
        const char* sto = getValueFromTable(conn, query2, "stock");
        float price = strToFloat(prc);
        int stock = atoi(sto);
        sum += price * product_num;
        if (!count) {
            getTime(time);
            sprintf(tabs, "INSERT INTO orders (customer_id,order_date,total_amount) VALUES('%d', '%s', '%.2f')", 1, time, sum);
            Query(conn, tabs);
            id = getLastInsertId(conn);
        }
        else {
            sprintf(tabs, "UPDATE orders SET total_amount = '%.2f' WHERE order_id = %d", sum, id);
            Query(conn, tabs);
        }
        sprintf(tabs,"INSERT INTO order_items (order_id,product_id,quantity) VALUES(%d, %s, %d)",id,product_id,product_num);
        Query(conn, tabs);
        sprintf(tabs, "UPDATE products SET stock=%d WHERE product_id=%s", stock-product_num,product_id);
        Query(conn, tabs);
        int dele = DeleteShopping_Cart();
        if (dele)
            DeleteShoppingCart(conn, id);
        count++;
    }
}
void DeleteShoppingCart(MYSQL* conn,int order_id) {
    char query[300];
    sprintf(query, "SELECT order_items.order_item_id, quantity, name, price FROM order_items JOIN products ON order_items.product_id = products.product_id JOIN orders ON order_items.order_id = orders.order_id WHERE orders.order_id =%d",order_id);
    SelectPrint(conn, query);
    int order_item_id = 0;
    Shopping_Cart(&order_item_id);
    sprintf(query, "SELECT quantity * price AS sum FROM order_items JOIN products on products.product_id = order_items.product_id WHERE order_item_id=%d",order_item_id);
    const char* sum = getValueFromTable(conn,query,"sum");
    sprintf(query, "SELECT total_amount FROM orders WHERE order_id=%d", order_id);
    const char* amount = getValueFromTable(conn, query, "total_amount");
    float desc = atof(sum);
    float tot = atof(amount);
    sprintf(query, "DELETE FROM order_items WHERE order_item_id=%d",order_item_id);
    Query(conn,query);
    sprintf(query, "UPDATE orders SET total_amount = %.2f WHERE order_id = %d",tot-desc,order_id);
    Query(conn, query);
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
void ProductSelling(MYSQL* conn) {
    const char* query[80] = {
        "order_items.product_id",
        "products.name",
        NULL
    };
    const char* funcs[80] = {
        "SUM(order_items.quantity * products.price) AS total_amount",
        "SUM(quantity) AS amount",
        NULL
    };
    char str[500] = "";
    ProductTotal(query, funcs, str);
    SelectPrint(conn, str);
}
void EditingStock(MYSQL* conn) {
    int num;
    char name[20] = "1", query[200] = "", query2[200] = "";
    while (1) {
        InsertStock(conn,&num);
        if (num == -1) {
            return;
        }
        
    }
}
void InsertStock(MYSQL* conn,int* num) {
    float income_price = 2.3, outcome_price = 2.4;
    int stock = 20;
    char name[30] = "banana", tabs[300];
    Stock_Insert(name,&income_price,&outcome_price,&stock,num);
    if (stock < 0) {
        sprintf(tabs, "SELECT income_price FROM stock WHERE name='%s';", name);
        int flag = emptyornot(conn, tabs);
        if (flag) {
            const char* prev = getValueFromTable(conn, tabs, "income_price");
            sprintf(tabs, "INSERT INTO Stock (name,income_price,stock) VALUES('%s',%s,%d);", name, prev, stock);
        }
        else {
            return;
        }
    }
    else
        sprintf(tabs, "INSERT INTO Stock (name,income_price,outcome_price,stock) VALUES('%s',%.2f,%.2f,%d);", name, income_price, outcome_price, stock);
    Query(conn, tabs);
    char str[300];
    sprintf(str, "SELECT stock FROM products WHERE name='%s';", name);
    int flag = emptyornot(conn, str);
    if (flag) {
        const char* res = getValueFromTable(conn, str, "stock");
        int res_int = atoi(res),re;
        if (stock + res_int > 0) re = stock + res_int;
        else re = 0;
        if (stock > 0) {
            sprintf(str, "UPDATE products SET stock=%d WHERE name='%s'", re, name);
        }
        else {
            sprintf(str, "UPDATE products SET price=%f,stock=%d WHERE name='%s'",outcome_price ,re, name);
        }
        Query(conn, str);
    }
    else {
        sprintf(str, "INSERT INTO products(name,price,stock) VALUES('%s', %.2f, %d)", name, outcome_price, stock);
        Query(conn, str);
    }
}
void OrderPrintAll(MYSQL* conn) {
    SelectPrint(conn,"SELECT * FROM products ");
}
void OrderPrintOne(MYSQL* conn, char* query) {
    PrintOne(query);
    SelectPrint(conn, query);
}

