#include "data.h"

/* Get a textual representation of a warehouse */
void getWareHouseStr(tWareHouse wh, int maxSize, char *str);

/* Get a warehouse object from its textual representation */
void getWareHouseObject(const char *str, tWareHouse *wh);

/* Load the distribution center from a file */
void distributionCenter_load(tDistributionCenter *centers, const char* filename, tError *retVal);

/* Save the distribution center to a file */
void distributionCenter_save(tDistributionCenter centers, const char* filename, tError *retVal);

/* Inits a distribution center */
void distributionCenter_init(tDistributionCenter *centers, char id);

/* Finds a good in the warehouse. Returns NO_GOOD if not found. Returns the index if found */
int warehouse_find( tGoodId id, tWareHouse wh );

/* Adds a good in the warehouse with the specified stock */
void warehouse_addStock( tGoodId id, tWareHouse *wh, int qtt );

/* Updates a good in the warehouse with the given increment or decrement of stock (+/- qtt) */
void warehouse_updateStock( tGoodId id, tWareHouse *wh, int qtt );

/* Sets a good in the warehouse with the given stock (absolute value for qtt) */
void warehouse_setStock( tGoodId id, tWareHouse *wh, int qtt );

/* Gets the stock qtt of a good in the warehouse */
int warehouse_getStock( tGoodId id, tWareHouse wh );

/* Gets the number of goods in the warehouse */
int warehouse_getNumberOfGoods( tWareHouse wh );

/* Cleans all stocks of the warehouse */
void warehouse_cleanAllStocks( tWareHouse *wh );

