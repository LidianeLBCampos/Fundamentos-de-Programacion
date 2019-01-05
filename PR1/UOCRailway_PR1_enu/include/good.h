#include "data.h"

/* Get a textual representation of a good */
void getGoodStr(tGood good, int maxSize, char *str);
	
/* Get a good object from its textual representation */
void getGoodObject(const char *str, tGood *good);

/* Compare two goods */
int good_cmp(tGood good1, tGood good2);

/* Copy the good data in src to dst*/
void good_cpy(tGood *dst, tGood src);

/* Initialize the table of goods */
void goodTable_init(tGoodTable *table);

/* Add a new good to the table of goods */
void goodTable_add(tGoodTable *table, tGood good, tError *retVal);

/* Find a good in the table and returns its position */
int goodTable_find(tGoodTable table, tGoodId id);

/* Remove the first occurence of a good in the table */
void goodTable_del(tGoodTable *table, tGood good);

/* Load the table of goods from a file */
void goodTable_load(tGoodTable *table, const char* filename, tError *retVal);

/* Save a table of goods to a file */
void goodTable_save(tGoodTable table, const char* filename, tError *retVal);

/* Filter all goods with the given type */
void goodTable_filterByType(tGoodTable table, tGoodType goodType, tGoodTable *result);

/* Filter all goods with a weight wihtin the specified interval */
void goodTable_filterByWeightInterval(tGoodTable tabGood, float minWeight, float maxWeight, tGoodTable *result);

/* Gets the number of fragile goods */
int goodTable_getNumberOfFragileGoods(tGoodTable tabGood);

/* Gets the maximum height of all goods */
float goodTable_getMaxGoodHeight(tGoodTable tabGood);
