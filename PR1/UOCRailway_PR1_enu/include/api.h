#include "data.h"

/* 
 * Methods for application data management 
 */

/* Initialize the application data */
void appData_init(tAppData *object);

/* Load the application data from file */
void appData_load(tAppData *object, tError *error);

/* Save the application data to a file */
void appData_save(tAppData object, tError *error);

/* Allow to assign a path to the application data */
void appData_setPath(tAppData *object, const char *path);

/* 
 * API
 */

/* Return a table with the goods */
void getGoods(tAppData object, tGoodTable *result);

/* Get the good information */
void getGood(tAppData object, tGoodId goodId, tGood *good, tError *retVal);

/* Add a new good */
void addGood(tAppData *object, tGood good, tError *retVal);

/* Remove a certain good */
void removeGood(tAppData *object, tGood good);

/* Return the table of trains */
void getTrains(tAppData object, tTrainTable *result);

/* Get the train information */
void getTrain(tAppData object, tTrainId trainId, tTrain *train, tError *retVal);

/* Add a new train */
void addTrain(tAppData *object, tTrain train, tError *retVal);
