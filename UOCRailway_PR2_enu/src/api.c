#include <stdio.h>
#include <math.h>
#include <string.h>
#include <api.h>
#include "good.h"
#include "train.h"
#include "center.h"
#include "order.h"
#include "stack.h"

void appData_init(tAppData *object) {
	/* Set parent folder as the default path */
	strcpy(object->path, "../");
	
	/* Initialize the good table */
	goodTable_init(&(object->goods));
	
	/* Initialize the trains table */
	trainsTable_init(&(object->trains));
	
	/* Initialize the distribution centers */
    distributionCenter_init( &object->centerA, 'A');
    distributionCenter_init( &object->centerB, 'B');
    
	/* Initialize the pending, attended and unattended orders */
    ordersTable_init(&object->pendingOrders);
    ordersTable_init(&object->attendedOrders);
    ordersTable_init(&object->unattendedOrders);
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
    
	/* Load the distribution center A */
	sprintf(path,"%scenterA.txt", object->path);
	distributionCenter_load(&(object->centerA), path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error reading the file of distribution center A\n");
	}

	/* Load the distribution center B */
	sprintf(path,"%scenterB.txt", object->path);
	distributionCenter_load(&(object->centerB), path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error reading the file of distribution center B\n");
	}
    
	/* Load the pending orders */
	sprintf(path,"%sordersPending.txt", object->path);
	ordersTable_load(&(object->pendingOrders), path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error reading the file of pending orders\n");
	}
    
	/* Load the attended orders */
	sprintf(path,"%sordersAttended.txt", object->path);
	ordersTable_load(&(object->attendedOrders), path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error reading the file of attended orders\n");
	}
    
	/* Load the unattended orders */
	sprintf(path,"%sordersUnattended.txt", object->path);
	ordersTable_load(&(object->unattendedOrders), path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error reading the file of unattended orders\n");
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
	
	/* Save the distribution center A */
	sprintf(path,"%scenterA.txt", object.path);
    distributionCenter_save(object.centerA, path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error saving the distribution center A\n");
	}
    
	/* Save the distribution center B */
	sprintf(path,"%scenterB.txt", object.path);
    distributionCenter_save(object.centerB, path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error saving the distribution center B\n");
	}
    
	/* Save the pending orders */
	sprintf(path,"%sordersPending.txt", object.path);
    ordersTable_save(object.pendingOrders, path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error saving the pending orders\n");
	}
    
	/* Save the attended orders */
	sprintf(path,"%sordersAttended.txt", object.path);
    ordersTable_save(object.attendedOrders, path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error saving the attended orders\n");
	}
    
	/* Save the unattended orders */
	sprintf(path,"%sordersUnattended.txt", object.path);
    ordersTable_save(object.unattendedOrders, path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error saving the unattended orders\n");
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
    
    /* Clear stocks for the removed good */
    warehouse_setStock( good.id, &(object->centerA.wareHouse), 0 );
    warehouse_setStock( good.id, &(object->centerB.wareHouse), 0 );
}

void addStock( tAppData *object, char center, tGoodId goodId, int qtt ) {

    if (center == 'A') {
        if (warehouse_find(goodId, object->centerA.wareHouse) == NO_GOOD)
            warehouse_addStock(goodId, &(object->centerA.wareHouse), qtt); 
        else
            warehouse_updateStock(goodId, &(object->centerA.wareHouse), qtt); 
    }
    else if (center == 'B') {
        
        if (warehouse_find(goodId, object->centerB.wareHouse) == NO_GOOD)
            warehouse_addStock(goodId, &(object->centerB.wareHouse), qtt);
        else
            warehouse_updateStock(goodId, &(object->centerB.wareHouse), qtt); 
    }
}

void removeStock( tAppData *object, char center, tGoodId goodId, int qtt ) {

    if (center == 'A')
        warehouse_updateStock(goodId, &(object->centerA.wareHouse), -qtt); 
    else if (center == 'B')
        warehouse_updateStock(goodId, &(object->centerB.wareHouse), -qtt);     
}

void cleanStocks( tAppData *object, char center ) {

    if (center == 'A')
        warehouse_cleanAllStocks( &(object->centerA.wareHouse) ); 
    else if (center == 'B')
        warehouse_cleanAllStocks( &(object->centerB.wareHouse) ); 
}

void addTrainToPlatform(tAppData *object, tTrainId trainId, char center, char platform, tError *retVal) 
{
	*retVal = OK;
    tLoadedTrain loadedTrain;

    loadedTrain.id= trainId;
    loadedTrain.load.id= NO_GOOD;
    loadedTrain.load.qtt= 0;

    if (center=='A')
    {
        if (platform=='M')
            trainStack_push( &object->centerA.mainPlatform, loadedTrain );
        else if (platform=='S')
            trainStack_push( &object->centerA.siding, loadedTrain );
    }   
    else if (center=='B')
    {
        if (platform=='M')
            trainStack_push( &object->centerB.mainPlatform, loadedTrain );
        else if (platform=='S')
            trainStack_push( &object->centerB.siding, loadedTrain );        
    }
}

void removeTrainFromStack( tTrainStack *s, tTrainId trainId ) 
{
    tTrainStack auxStack;
    tLoadedTrain e;
    int i,count;

    if (!trainStack_empty(*s))
    {
        auxStack= trainStack_create();  
        count= 0;
        e= trainStack_top(*s);
        while ( !trainStack_empty(*s) && (e.id != trainId) )
        {  
            trainStack_pop(s);
            trainStack_push(&auxStack, e);
            e= trainStack_top(*s);
            count++;
        }
        trainStack_pop(s);
        for (i= 0; i<count;i++)
        {
            e= trainStack_top(auxStack);
            trainStack_pop(&auxStack);
            trainStack_push(s, e);
        }
    }
}

void removeTrainFromPlatform(tAppData *object, tTrainId trainId, char center, char platform, tError *retVal) 
{
	*retVal = OK;

    if (center=='A')
    {
        if (platform=='M')
            removeTrainFromStack( &object->centerA.mainPlatform, trainId );
        else if (platform=='S')
            removeTrainFromStack( &object->centerA.siding, trainId );
    }   
    else if (center=='B')
    {
        if (platform=='M')
            removeTrainFromStack( &object->centerB.mainPlatform, trainId );
        else if (platform=='S')
            removeTrainFromStack( &object->centerB.siding, trainId );        
    }
}

void removeAllTrainsOfCenter(tAppData *object, char center, tError *retVal) 
{
	*retVal = OK;

    if (center=='A')
    {
        trainStack_clean( &object->centerA.mainPlatform );
        trainStack_clean( &object->centerA.siding );
    }   
    else if (center=='B')
    {
        trainStack_clean( &object->centerB.mainPlatform );
        trainStack_clean( &object->centerB.siding );
    }
}

void cleanAllOrders(tAppData *object)
{
    ordersTable_init( &object->pendingOrders );
    ordersTable_init( &object->attendedOrders );
    ordersTable_init( &object->unattendedOrders );    
}

void addPendingOrder(tAppData *object, tOrder order, tError *retVal)
{
    ordersTable_add(&object->pendingOrders, order, retVal);
}

/********************/
/* Order processing */
/********************/

tBoolean checkStockAtOrigin( tWareHouse wh, tGood good, int qtt )
{
    tBoolean result= FALSE;
    
    /******** PR2 - EX2A.1 *********/
    
    
    
    
    
    /*****************************/
    
    return result;
}

tBoolean searchTrainAtOrigin( tTrainTable trainTable,
                             tTrainStack *mainPlatform,
                             tTrainStack *siding,
                             tGood good, int qtt )
{
    tBoolean success= FALSE;
    
    /******** PR2 - EX2A.2 *********/
    
    
    
    
    
    /*****************************/
    
    return success;
}

void loadTrain( tTrainStack *mainPlatform, tWareHouse *wh, tGood good, int qtt )
{
    /******** PR2 - EX2A.3 *********/
    
    
    
    
    
    /*****************************/ 
}

void moveTrainFromOriginToDestination(  tTrainStack *originPlatform,
                                      tTrainStack *destinationPlatform )
{
    /******** PR2 - EX2B *********/
    
    
    
    
    
    /*****************************/
}

void unloadTrainAtDestination( tTrainStack *mainPlatform, tWareHouse *wh )
{
    /******** PR2 - EX2C *********/
    
    
    
    
    
    /*****************************/
}

tBoolean checkSuitableTrain( tTrain train, tGood good, int qtt )
{
    return (train.wagonCapacity * (float)train.nWagons) >= (good.volume * (float)qtt);
}

tBoolean prepareLoadedTrainAtOrigin( tTrainTable trainTable,
                                     tTrainStack *mainPlatform, tTrainStack *siding, 
                                     tWareHouse *wh, tGood good, int qtt )
{
    tBoolean success;

    /* Check there is enough stock to satisfy the order */
    success= checkStockAtOrigin( *wh, good, qtt );

    /* Search train (let the suitable train on top of the main platform) */
    if (success)
        success= searchTrainAtOrigin( trainTable, mainPlatform, siding, good, qtt );
        
    /* Load the train on top of the main platform (train about to leave origin center) */
    if (success) 
        loadTrain( mainPlatform, wh, good, qtt );
        
    return success;
}

tBoolean tryToAttendOrder(  tTrainTable trainTable,
                            tDistributionCenter *originCenter, 
                            tDistributionCenter *destinationCenter, 
                            tGood good, int qtt )
{
    tBoolean success;
    
    /* Prepare the train and place it in the top of origin main platform */
    success= prepareLoadedTrainAtOrigin( trainTable,
                                         &originCenter->mainPlatform, 
                                         &originCenter->siding, 
                                         &originCenter->wareHouse, 
                                         good, qtt );

    /* Move the goods from origin center to destination center */
    if (success)
        moveTrainFromOriginToDestination( &originCenter->mainPlatform, 
                                          &destinationCenter->mainPlatform );
        
    /* Unload the train at destination center and update stocks on the warehouse */
    if (success)
        unloadTrainAtDestination( &destinationCenter->mainPlatform, 
                                  &destinationCenter->wareHouse );
    
    return success;
}

void processOrders( tAppData *object, tError *retVal )
{
    tBoolean attended;
    tOrder order;
    tGood  good;
    int i, qtt;
    
    for (i= 0; i < object->pendingOrders.nOrders; i++) 
    {
        /* get the current order */
        order= object->pendingOrders.table[i];
        
        /* find out the good and its ordered qtt*/
        good= goodTable_get( object->goods, order.goodsOrdered.id );
        qtt= order.goodsOrdered.qtt;
        
        /* try to attend the order */
        if (order.originCenter=='A')
            attended= tryToAttendOrder( object->trains,
                                        &object->centerA, 
                                        &object->centerB, 
                                        good, qtt );
        else 
            attended= tryToAttendOrder( object->trains,
                                        &object->centerB, 
                                        &object->centerA, 
                                        good, qtt );
            
        /* classify order according to result */
        if (attended)
            ordersTable_add( &object->attendedOrders, order, retVal );
        else
            ordersTable_add( &object->unattendedOrders, order, retVal );            
    }
    
    /* cleans pending list because all orders have been processed */
    ordersTable_clean( &object->pendingOrders );  
}