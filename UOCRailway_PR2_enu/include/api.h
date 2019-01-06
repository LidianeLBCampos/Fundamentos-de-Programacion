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

/* Adds stock for a good in a distribution center */
void addStock( tAppData *object, char center, tGoodId goodId, int qtt );

/* Removes stock for a good in a distribution center */
void removeStock( tAppData *object, char center, tGoodId goodId, int qtt );

/* Clean stocks for all goods in the specified distribution center */
void cleanStocks( tAppData *object, char center );

/* Adds a train to the specified platform of a distribution center */
void addTrainToPlatform(tAppData *object, tTrainId trainId, char center, char platform, tError *retVal);

/* Removes a train from the specified platform of a distribution center */
void removeTrainFromPlatform(tAppData *object, tTrainId trainId, char center, char platform, tError *retVal);

/* Removes all trains from all platforms of a distribution center */
void removeAllTrainsOfCenter(tAppData *object, char center, tError *retVal);

/* Removes all orders from the panding, attended and unattended orders */
void cleanAllOrders(tAppData *object);

/* Adds a pending order to the system */
void addPendingOrder(tAppData *object, tOrder order, tError *retVal);

/* Checks if there's enough stock at the given warehouse */
tBoolean checkStockAtOrigin( tWareHouse wh, tGood good, int qtt );

/* Loads a train with the order and updates the warehouse' stock */
void loadTrain( tTrainStack *mainPlatform, tWareHouse *wh, tGood good, int qtt );

/* Unloads a loaded train and updates the warehouse' stock */
void unloadTrainAtDestination( tTrainStack *mainPlatform, tWareHouse *wh );
                                  
/* Moves a train form an origin platform to a destination platform */
void moveTrainFromOriginToDestination( tTrainStack *originPlatform, tTrainStack *destinationPlatform );

/* Says if a train is suitable to be loaded with qtt units of the good */
tBoolean checkSuitableTrain( tTrain train, tGood good, int qtt );

/* Searches (and place on top of main platform) a suitable train to be loaded with qtt units of good */
tBoolean searchTrainAtOrigin( tTrainTable trainTable,
                              tTrainStack *mainPlatform, 
                              tTrainStack *siding, 
                              tGood good, int qtt );

/* Prepares a loades train to move de ordered good from origin to destination */
tBoolean prepareLoadedTrainAtOrigin( tTrainTable trainTable,
                                     tTrainStack *mainPlatform, tTrainStack *siding, 
                                     tWareHouse *wh, tGood good, int qtt );

/* Tries to attend the given order */
tBoolean tryToAttendOrder(  tTrainTable trainTable,
                            tDistributionCenter *originCenter, 
                            tDistributionCenter *destinationCenter, 
                            tGood good, int qtt );

/* Processes all orders and classifies then between unattented and attended */
void processOrders( tAppData *object, tError *retVal );