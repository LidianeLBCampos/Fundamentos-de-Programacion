#include "data.h"

/* Get a textual representation of a train */
void getTrainStr(tTrain train, int maxSize, char *str);

/* Get a train object from its textual representation */
void getTrainObject(const char *str, tTrain *train);

/* Get a textual representation of a loaded train */
void getLoadedTrainStr(tLoadedTrain loadedTrain, int maxSize, char *str);

/* Get a loaded train object from its textual representation */
void getLoadedTrainObject(const char *str, tLoadedTrain *loadedTrain);

/* Copy the loaded train data in src to dst*/
void loaded_train_cpy(tLoadedTrain *dst, tLoadedTrain src);

/* Initialize a loaded train */
void loaded_train_init(tLoadedTrain *t);

/* Copy the train data in src to dst*/
void train_cpy(tTrain *dst, tTrain src);

/* Compares the loaded train data of p1 and p2*/
int loaded_train_cmp(tLoadedTrain d1, tLoadedTrain d2);

/* Compares the train data of p1 and p2*/
int train_cmp(tTrain p1, tTrain p2);

/* Initializes the given trains table */
void trainsTable_init(tTrainTable *trainsTable);

/* Add a new train to the table of trains */
void trainsTable_add(tTrainTable *tabTrains, tTrain train, tError *retVal);

/* Find a train in the table */
int trainsTable_find(tTrainTable tabTrains, tTrainId id);

/* Says if the trains table is empty */
tBoolean trainsTable_empty(tTrainTable tabTrains);

/* Gets a train in the table  by its id*/
tTrain trainsTable_get(tTrainTable tabTrains, tTrainId id);

/* Load the table of trains from a file */
void trainsTable_load(tTrainTable *tabTrains, const char* filename, tError *retVal);

/* Save a table of trains to a file */
void trainsTable_save(tTrainTable tabTrains, const char* filename, tError *retVal);

/* Obtain from a table of trains those of a given propulsion type */
void trainsTable_filterByPropulsion(tTrainTable tabTrains, tPropulsion propulsion, tTrainTable *result);

/* Obtain from a table of trains those having a locomotive */
void trainsTable_getTrainsWithLocomotive(tTrainTable tabTrains, tTrainTable *result);

/* Obtain from a table of trains the average capacity by propulsion type */
float trainsTable_getAverageCapacityByPropulsion(tTrainTable tabTrain, tPropulsion propulsion);

/* Obtain from a table of trains the maximum speed of a train */
float trainsTable_getMaxTrainSpeed(tTrainTable tabTrain);

