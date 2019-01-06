#include "data.h"

/* Get a textual representation of an order */
void getOrderStr(tOrder order, int maxSize, char *str);

/* Get an order object from its textual representation */
void getOrderObject(const char *str, tOrder *order);

/* Copy the order data in src to dst*/
void order_cpy(tOrder *dst, tOrder src);

/* Compares the order data of p1 and p2*/
int order_cmp(tOrder p1, tOrder p2);

/* Initializes the given orders table */
void ordersTable_init(tOrderTable *ordersTable);

/* Add a new order to the table of orders */
void ordersTable_add(tOrderTable *tabOrders, tOrder order, tError *retVal);

/* Find an order in the table */
int ordersTable_find(tOrderTable tabOrders, tOrderId order);

/* Cleans the given orders table */
void ordersTable_clean(tOrderTable *ordersTable);

/* Load the table of orders from a file */
void ordersTable_load(tOrderTable *tabOrders, const char* filename, tError *retVal);

/* Save a table of orders to a file */
void ordersTable_save(tOrderTable tabOrders, const char* filename, tError *retVal);
