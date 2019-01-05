#include <stdio.h>
#include <math.h>
#include <string.h>
#include <api.h>
#include "good.h"
#include "train.h"

void appData_init(tAppData *object) {
	/* Set parent folder as the default path */
	strcpy(object->path, "../");
	
	/* Initialize the good table */
	goodTable_init(&(object->goods));
	
	/* Initialize the trains table */
	trainsTable_init(&(object->trains));
	
}

void appData_load(tAppData *object, tError *retVal) {
	char path[MAX_LINE];
	*retVal = OK;
	
	/* Load the table of trains */
	sprintf(path,"%strains.txt", object->path);
	trainsTable_load(&(object->trains), path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error reading the file of trains\n");
	}

	/* Load the table of goods */
	sprintf(path,"%sgoods.txt", object->path);
	goodTable_load(&(object->goods), path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error reading the file of goods\n");
	}

}

void appData_save(tAppData object, tError *retVal)  {
	char path[MAX_LINE];
	*retVal = OK;
	
	/* Save the table of trains */
	sprintf(path,"%strains.txt", object.path);
	trainsTable_save(object.trains, path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error saving the file of trains\n");
	}
	
	/* Save the table of goods */
	sprintf(path,"%sgoods.txt", object.path);
	goodTable_save(object.goods, path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error saving the file of goods\n");
	}
	
}

void appData_setPath(tAppData *object, const char *path)  {		
	strncpy(object->path, path, 255);	
}


/*********************** 
 *        API
 **********************/

void getTrains(tAppData object, tTrainTable *result) {
	*result = object.trains;	
}

void getTrain(tAppData object, tTrainId trainId, tTrain *train, tError *retVal) {
	
	int i;
	*retVal = OK;

	/* Check if there is a train with this id */
	i = trainsTable_find(object.trains, trainId);
	if (i!=NO_TRAIN) {
		train_cpy(train,object.trains.table[i]);
	} else {
		*retVal = ERR_ENTRY_NOT_FOUND;
	}

}

void addTrain(tAppData *object, tTrain train, tError *retVal) {
	*retVal = OK;
	tTrain tmp;

	/* Check if there is another train with the same id */
	getTrain(*object, train.id, &tmp, retVal);
	if(*retVal==OK) {
		*retVal = ERR_DUPLICATED_ENTRY;
	} else {
		/* Add the new train using the train table method */
		trainsTable_add(&(object->trains), train, retVal);
	}

}

void getGoods(tAppData object, tGoodTable *result) {
	*result = object.goods;	
}

void getGood(tAppData object, tGoodId id, tGood *good, tError *retVal) {
	
	int i;
	*retVal = OK;
	
	/* Check if there is a good with this id */
	i = goodTable_find(object.goods, id);
	if (i!=NO_GOOD) {
		good_cpy(good,object.goods.table[i]);
	} else {
		*retVal = ERR_ENTRY_NOT_FOUND;
	}

}

void addGood(tAppData *object, tGood good, tError *retVal) {
	*retVal = OK;
	tGood tmpGood;
    
	/* Check if there is another good with the same id */
	getGood(*object, good.id, &tmpGood, retVal);
	if(*retVal==OK) {
		*retVal = ERR_DUPLICATED_ENTRY;
	} else {
		/* Add the new good using the good table method */
		goodTable_add(&(object->goods), good, retVal);
	}

}

void removeGood(tAppData *object, tGood good) {
	
	/* Call the method from the goods table*/
	goodTable_del(&(object->goods), good);

}
