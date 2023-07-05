#include "../headers/window.h"
#include "../headers/servicess.h"

void Shop(MYSQL* conn,char* product_id, int* product_num,int* num) {
    SelectPrint(conn, "SELECT product_id,name,price FROM products");
    printf("\nselect id: ");
    scanf("%s", product_id);getchar();
    printf("\nselect numbers: ");
    scanf("%d", product_num);getchar();
    printf("\nenter a numebr (-1 to quit): ");
    scanf("%d", num);
}
void Stock_Insert(char* name, float* income_price, float* outcome_price, int* stock,int* num) {
    int tmp = 0;
    printf("purchase or refund (1/-1)");
    scanf("%d",&tmp);
    if (tmp != 1 && tmp != -1) {
        printf("WRONG NUMBER");
        return;
    }
    printf("\nname of product: ");
    scanf("%s",name);
    if (tmp > 0) {
        printf("\nincome_price: ");
        scanf("%f", income_price);
        printf("\noutcome_price: ");
        scanf("%f", outcome_price);
    }
    printf("\nstock: ");
    scanf("%d", stock);
    if (tmp == -1) {
        *stock = -(*stock);
    }
    printf("\nenter a numebr (-1 to quit): ");
    scanf("%d", num);
}
void Shopping_Cart(int *order_item_id) {
    printf("enter the order_item_id you want to delete:");
    scanf("%d",order_item_id);
}
int DeleteShopping_Cart() {
    int tmp = 0;
    printf("want to delete from shopping cart? (press 1 to delete)");
    scanf("%d", &tmp);
    if (tmp != 1 ) {
        return 0;
    }
    return 1;
}