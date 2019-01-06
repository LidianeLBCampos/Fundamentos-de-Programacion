#include <stdio.h>
#include <string.h>
#include "data.h"
#include "stack.h"
#include "menu.h"
#include "train.h"
#include "good.h"
#include "order.h"

int getOption(int numOptions) {
	int option=0;
		
	while(option<1 || option>numOptions) {
		/* Read the input */
		printf(">> ");
			scanf("%u", &option);
		getchar();
		
		/* Check the user input */
		if(option<1 || option>numOptions) {
			printf("Incorrect option.\n");
		}
	}
	 return option;
}

tTrainId getUnusedTrainId( tTrainTable table )
{
    tBoolean valid;
    tTrainId trainId;
    int trainInt;

	printf("Train id (integer less than %d):\n>> ",MAX_TRAINS);
    scanf("%d",&trainInt);
    trainId= trainInt;
    
    valid= (trainsTable_find(table,trainId) == NO_TRAIN);
    
    while (!valid) {
        printf("Id already in use. Please, try again.\n");
        printf("Train id (integer less than %d):\n>> ",MAX_TRAINS);
        scanf("%d",&trainId);
        valid= (trainsTable_find(table,trainId) == NO_TRAIN);
    }
    
    return trainId;
}

tGoodId getUnusedGoodId( tGoodTable table )
{
    tBoolean valid;
    tGoodId goodId;
    int goodInt;

	printf("Good id (integer less than %d):\n>> ",MAX_GOODS);
    scanf("%d",&goodInt);
    goodId= goodInt;
    
    valid= (goodTable_find(table,goodId) == NO_GOOD);
    
    while (!valid) {
        printf("Id already in use. Please, try again.\n");
        printf("Good id (integer less than %d):\n>> ",MAX_GOODS);
        scanf("%d",&goodId);
        valid= (goodTable_find(table,goodId) == NO_GOOD);
    }
    
    return goodId;
}

tOrderId getUnusedOrderId( tAppData object )
{
    tBoolean valid;
    tOrderId orderId;
    int orderInt;

	printf("Order id (integer less than %d):\n",MAX_ORDERS);
    scanf("%d",&orderInt);
    orderId= orderInt;
    
    valid= (ordersTable_find(object.pendingOrders,orderId) == NO_ORDER) &&
           (ordersTable_find(object.attendedOrders,orderId) == NO_ORDER) &&
           (ordersTable_find(object.unattendedOrders,orderId) == NO_ORDER);
    
    while (!valid) {
        printf("Id already in use. Please, try again.\n");
        printf("Order id (integer less than %d):\n",MAX_ORDERS);
        scanf("%d",&orderId);
        valid= (ordersTable_find(object.pendingOrders,orderId) == NO_ORDER) &&
               (ordersTable_find(object.attendedOrders,orderId) == NO_ORDER) &&
               (ordersTable_find(object.unattendedOrders,orderId) == NO_ORDER);    
    }
    
    return orderId;
}

void readGood(tGood *good, tGoodTable table, tError *retVal) {	

	*retVal = OK;

	int number;
	char buffer[MAX_LINE];
	int length;

	/* Request information from user */ 
    number= (int)(getUnusedGoodId(table));
	if(number>MAX_GOODS) 
		*retVal = ERROR;
	else
		good->id = (tGoodId)number;
	getchar();

    printf("Good name (20 char max, no spaces):\n>> ");
    scanf("%s",buffer);
	length = strlen(buffer);
	if (length<MAX_NAME) {
		strncpy(good->name,buffer,MAX_NAME);
	} else {
		*retVal = ERROR;
	}
	getchar();
	
	printf("Good Type (1 digit being 0=FOOD, 1=CHEMICAL, 2=ANIMALS, 3=VEHICLES, 4=ELECTRONICS, 5=CONSTRUCTION , 6=OTHERS):\n>> ");
	scanf("%d",&number);
	if(number>=0 && number <=6) {
		good->type = (tGoodType)(number);
	} else {
		*retVal = ERROR;
	}
	getchar();

	printf("Price:\n>> ");
	scanf("%f",&good->price);
	getchar();
	
	printf("Weight:\n>> ");
	scanf("%f",&good->weight);
	getchar();
   
	printf("Height:\n>> ");
	scanf("%f",&good->height);
	getchar();
	
	printf("Volume:\n>> ");
	scanf("%f",&good->volume);
	getchar();
	
	printf("Maximum number of layers allowed on top:\n>> ");
	scanf("%d",&number);
    good->layers= (int)number;
	getchar();
	
	printf("Is fragile? (YES/NO):\n>> ");
	scanf("%s", buffer);
	if (strcmp(buffer,"YES") == 0 || strcmp(buffer,"yes") == 0) {
		good->isFragile = TRUE;
	} else if  (strcmp(buffer,"NO") == 0 || strcmp(buffer,"no") == 0) {
		good->isFragile = FALSE;
	} else {
		*retVal = ERROR;
	}
	
	printf("Is dangerous? (YES/NO):\n>> ");
	scanf("%s", buffer);
	if (strcmp(buffer,"YES") == 0 || strcmp(buffer,"yes") == 0) {
		good->isDangerous = TRUE;
	} else if  (strcmp(buffer,"NO") == 0 || strcmp(buffer,"no") == 0) {
		good->isDangerous = FALSE;
	} else {
		*retVal = ERROR;
	}
}

void readTrain(tTrain *train, tTrainTable table, tError *retVal) {	

	*retVal = OK;

	char buffer[MAX_LINE];
	int number, length;

    number= (int)getUnusedTrainId(table);
    if(number>MAX_TRAINS) 
		*retVal = ERROR;
    else 
		train->id= (tTrainId)(number);
	getchar();
	
    printf("Train brand (max 20 char, no spaces):\n>> ");
    scanf("%s",buffer);
	length = strlen(buffer);
	if (length<MAX_NAME) {
		strncpy(train->brand,buffer,MAX_NAME);
	} else {
		*retVal = ERROR;
	}
	getchar();

	printf("Train model (max 20 char, no spaces):\n>> ");
    scanf("%s",buffer);
	length = strlen(buffer);
	if (length<MAX_NAME) {
		strncpy(train->model,buffer,MAX_NAME);
	} else {
		*retVal = ERROR;
	}
	getchar();

	printf("Fabrication year:\n>> ");
	scanf("%d",&(train->year));
	getchar();

	printf("Train type of propulsion (1 digit being 0=ELECTRICAL 1=CARBON 2=SOLAR 3=GASOLINE 4=DIESEL 5=MAGNETIC):\n>> ");
	scanf("%d",&number);
	if(number>=0 && number <=5) {
		train->propulsionType= (tPropulsion)(number);
	} else {
		*retVal = ERROR;
	}
	getchar();

	printf("Number of wagons:\n>> ");
	scanf("%d",&(train->nWagons));
	getchar();
	
	printf("Capacity of each wagon (in cubic meters):\n>> ");
	scanf("%f",&(train->wagonCapacity));
	getchar();

	printf("Has a locomotive? (YES/NO):\n>> ");
	scanf("%s", buffer);
	if (strcmp(buffer,"YES") == 0 || strcmp(buffer,"yes") == 0) {
		train->hasLocomotive = TRUE;
	} else if  (strcmp(buffer,"NO") == 0 || strcmp(buffer,"no") == 0) {
		train->hasLocomotive = FALSE;
	} else {
		*retVal = ERROR;
	}
	getchar();

	printf("Train weight (in tones):\n>> ");
	scanf("%f",&(train->weight));
	getchar();
	
	printf("Train length (in meters):\n>> ");
	scanf("%f",&(train->length));
	getchar();

	printf("Train max speed (in km/h):\n>> ");
	scanf("%f",&(train->maxSpeed));
	getchar();
}

void printTrainTable(tTrainTable table) {
    
  	int i;	
	char trainStr[MAX_LINE];
	
	if(table.nTrains==0) {
		printf("No trains.\n");
	} else {
		for(i=0;i<table.nTrains;i++) {
			getTrainStr(table.table[i], MAX_LINE, trainStr);
			printf("[%u] - %s\n", i+1, trainStr);
		}		
	}
}

void printGoodTable(tGoodTable table) {
	int i;	
	char goodStr[MAX_LINE];
	
	if(table.nGoods==0) {
		printf("No goods.\n");
	} else {
		for(i=0;i<table.nGoods;i++) {
			getGoodStr(table.table[i], MAX_LINE, goodStr);
			printf("[%u] - %s\n", i+1, goodStr);
		}		
	}
}

void printStockTable(tWareHouse wh, tGoodTable goods) {
    
    int i, good_idx;

    if (wh.nGoods == 0)
		printf("No goods in the warehouse.\n");
    else {

        for (i= 0; i< wh.nGoods; i++) {
            
            good_idx= goodTable_find(goods, wh.stock[i].id);
            if (good_idx == NO_GOOD)
                 printf("[%u] - Unknown good\n", i+1);            
            else
                 printf("[%u] - name:%s id:%d qtt:%d\n", i+1, goods.table[good_idx].name, 
                            wh.stock[i].id, wh.stock[i].qtt);            
        }
    }
}

void printTrainPlatform(tTrainStack s, tTrainTable trains) {
    
    int i, train_idx;

    if (s.nElem == 0)
		printf("No trains in the platform.\n");
    else {

        for (i= 0; i< s.nElem; i++) {
            
            train_idx= trainsTable_find(trains, s.table[i].id);
            if (train_idx == NO_TRAIN) {
                 printf("[%u] - Unknown train\n", i+1);				
			}				
            else {
                 printf("[%u] - id:%d - train:%s %s (%d)\n", i+1, trains.table[train_idx].id, 
                 trains.table[train_idx].brand, trains.table[train_idx].model, trains.table[train_idx].year);				
			}
        }
    }
}

tTrainId trainAt(tTrainStack s, int index) {
    
    tTrainId id;

    if (index >= 0 && index < s.nElem)
        id= s.table[index].id;
    else
        id= NO_TRAIN;

    return id;
}

void printOrderTable(tOrderTable table) {
	int i;	
	char orderStr[MAX_LINE];
	
	if(table.nOrders==0) {
		printf("No orders.\n");
	} else {
		for(i=0;i<table.nOrders;i++) {
			getOrderStr(table.table[i], MAX_LINE, orderStr);
			printf("[%u] - %s\n", i+1, orderStr);
		}		
	}
}

char getValidCenter( void )
{
    tBoolean valid;
    char center;

    printf("Select distribution center (A or B):\n");
    scanf("%c",&center);
    getchar();
    
    valid= (center=='A' || center=='B');
    
    while (!valid) {
        printf("Incorrect center. Please, try again.\n");
        printf("Select distribution center (A or B):\n");
        scanf("%c",&center);
        getchar();
        valid= (center=='A' || center=='B');
    }
    
    return center;
}

char getValidTypeOfOrder( void )
{
    tBoolean valid;
    char orderList;

    printf("Select order list: P (Pending), A (Attended) or U (Unattended):\n");
    scanf("%c",&orderList);
    getchar();
    
    valid= (orderList=='P' || orderList=='A' || orderList=='U');
    
    while (!valid) {
        printf("Incorrect order list. Please, try again.\n");
        printf("Select order list: P (Pending), A (Attended) or U (Unattended):\n");
        scanf("%c",&orderList);
        getchar();
        valid= (orderList=='P' || orderList=='A' || orderList=='U');
    }
    
    return orderList;
}

char getValidPlatform( void )
{
    tBoolean valid;
    char platform;

    printf("Select platform: M (Main) or S (Siding):\n");
    scanf("%c",&platform);
    getchar();
    
    valid= (platform=='M' || platform=='S');
    
    while (!valid) {
        printf("Incorrect platform. Please, try again.\n");
        printf("Select platform: M (Main) or S (Siding):\n");
        scanf("%c",&platform);
        getchar();
        valid= (platform=='M' || platform=='S');
    }
    
    return platform;
}

tGoodId getValidGood( tGoodTable table )
{
    tBoolean valid;
    tGoodId goodId;
    int goodInt;

    printf("Type the good id:\n");
    scanf("%d",&goodInt);
    goodId= (tGoodId)(goodInt);
    
    valid= (goodTable_find(table,goodId) != NO_GOOD);
    
    while (!valid) {
        printf("Incorrect good. Please, try again.\n");
        printf("Type the good id:\n");
        scanf("%d",&goodId);
        valid= (goodTable_find(table,goodId) != NO_GOOD);
    }
    
    return goodId;
}

tTrainId getValidTrain( tTrainTable table )
{
    tBoolean valid;
    tTrainId trainId;
    int trainInt;

    printf("Type the train id:\n");
    scanf("%d",&trainInt);
    trainId= trainInt;
    
    valid= (trainsTable_find(table,trainId) == NO_TRAIN);
    
    while (!valid) {
        printf("Incorrect train. Please, try again.\n");
        printf("Type the train id:\n");
        scanf("%d",&trainId);
        valid= (trainsTable_find(table,trainId) == NO_TRAIN);
    }
    
    return trainId;
}

tBoolean checkTrainInPlatform( tAppData object, tTrainId trainId )
{
    tBoolean found;
    tLoadedTrain train;
    
    train.id= trainId;
    train.load.id= NO_GOOD;
    train.load.qtt= 0;
    
    if (trainStack_contains(object.centerA.mainPlatform,train))
        found= TRUE;
    else if (trainStack_contains(object.centerA.siding,train))
        found= TRUE;
    else if (trainStack_contains(object.centerB.mainPlatform,train))
        found= TRUE;
    else if (trainStack_contains(object.centerB.siding,train))
        found= TRUE;
    else 
        found= FALSE;
        
    return found;
}

/*****************
 **   MAIN MENU **
*****************/
void printMainMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Main Menu \n");
	printf("=======================\n");
	printf("1) Load data from file\n");
	printf("2) Save data to file\n");
	printf("3) Manage goods\n");
	printf("4) Manage trains\n");
	printf("5) Manage centers\n");
	printf("6) Manage orders\n");
	printf("7) View statistics\n");
	printf("8) Exit\n");	
}

tMainMenuOptions getMainMenuOption() {
	/* Convert to the correct type */
	return (tMainMenuOptions)(getOption(8)-1);
}

void mainMenu(tAppData *appData) 
{
	tMainMenuOptions option;
	tError retVal;
		
	/* Assign the data path */
	appData_setPath(appData,"../");
		
	/* Start the menu */
	do {
		/* Show list of options and ask the user for an option */
		printMainMenuOptions();
		option=getMainMenuOption();
		
		/* Do the action for the given option */
		if (option == MAIN_MENU_LOAD) {
			appData_load(appData,&retVal);
			if(retVal==OK) {
				printf("Data loaded\n");
			} else {	
				printf("No previous data loaded\n");
			}
		} else if (option == MAIN_MENU_SAVE) {
			appData_save(*appData,&retVal);
			if(retVal==OK) {
				printf("Data saved\n");
			} else {	
				printf("Cannot save the data\n");
			}
		} else if (option == MAIN_MENU_GOOD) {
			goodMenu(appData);
		} else if (option == MAIN_MENU_TRAIN) {
			trainMenu(appData);
		} else if (option == MAIN_MENU_CENTER) {
			centerMenu(appData);
		} else if (option == MAIN_MENU_ORDER) {
			orderMenu(appData);            
		} else if (option == MAIN_MENU_STAT) {
			statMenu(*appData);
		} 
	} while (option!=MAIN_MENU_EXIT);
}

/*********************************
 **   GOOD MANAGEMENT MENU **
*********************************/
void printGoodMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Manage Goods\n");
	printf("=======================\n");
	printf("1) List goods\n");	
	printf("2) Add good\n");
	printf("3) Delete good\n");	
	printf("4) Clear all goods\n");
	printf("5) Get list of goods by type\n");	
	printf("6) Get list of goods by weight interval\n");	
	printf("7) Exit\n");	
}

tGoodMenuOptions getGoodMenuOption() {
	/* Convert to the correct type */
	return (tGoodMenuOptions)(getOption(7)-1);
}

void goodMenu(tAppData *appData) {
	tGoodMenuOptions option;
	tGood newGood;
	tGoodTable goodTable,resultTable;
	char goodStr[MAX_LINE];
	int i, goodType, pos=0;
	float minWeight, maxWeight;
	tError retVal;
			
	/* Start the menu */
	do {
		/* Show list of options and ask the user for an option */
		printGoodMenuOptions();
		option=getGoodMenuOption();
		
		/* Do the action for the given option */
		if (option == GOOD_MENU_LIST ) {
			getGoods(*appData, &goodTable);
			printGoodTable(goodTable);
		} else if (option == GOOD_MENU_ADD) {
			printf("Enter the information for the new good:\n");
			readGood(&newGood,goodTable,&retVal);
			getGoodStr(newGood, MAX_LINE, goodStr);
			if(retVal==OK) {
				addGood(appData, newGood, &retVal);
				if(retVal==OK){
					printf("Good added: %s\n", goodStr);
				} else if(retVal==ERR_DUPLICATED_ENTRY) {
					printf("Duplicated good not added: %s\n", goodStr);
				} else {
					printf("No more space. Good not added: %s\n", goodStr);
				}
			} else {
				printf("Error in input. Good not added: %s\n", goodStr);
			}
		} else if (option == GOOD_MENU_DEL) {
			getGoods(*appData, &goodTable);			
			/* Print the goods */			
			printGoodTable(goodTable);		

			if (goodTable.nGoods > 0) {
				/* Ask the number of the register to be removed */
				printf("Enter the number of the good to delete:\n");
				pos=getOption(goodTable.nGoods);
				/* Remove the selected good */				
				removeGood(appData, goodTable.table[pos-1]);
			}
		} else if (option == GOOD_MENU_CLEAR_ALL) {
			getGoods(*appData, &goodTable);	
			for (i= 0; i< goodTable.nGoods; i++) {
				/* Remove the good */				
				removeGood(appData, goodTable.table[i]);
			}
		} else if (option == GOOD_MENU_GOODS_BY_TYPE) {
			printf("Good Type (1 digit being 0=FOOD, 1=CHEMICAL, 2=ANIMALS, 3=VEHICLES, 4=ELECTRONICS, 5=CONSTRUCTION, 6=OTHERS):\n");
			scanf("%d",&goodType);			
			getGoods(*appData, &goodTable);
			goodTable_filterByType(goodTable,(tGoodType)goodType,&resultTable); 
			printGoodTable(resultTable);	
			
		} else if (option == GOOD_MENU_GOODS_BY_WEIGHT_INTERVAL) {
			printf("Enter minimum value for weight interval (kg):\n");
			scanf("%f",&minWeight);
			printf("Enter maximum value for weight interval (kg):\n");
			scanf("%f",&maxWeight);			
			getGoods(*appData, &goodTable);
			goodTable_filterByWeightInterval(goodTable, minWeight, maxWeight, &resultTable); 
			printGoodTable(resultTable);	
		}

	} while(option!=GOOD_MENU_EXIT);
}

/********************************
 **   TRAIN MANAGEMENT MENU **
********************************/
void printTrainMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Manage trains\n");
	printf("=======================\n");
	printf("1) List trains\n");	
	printf("2) Add train\n");
	printf("3) List by propulsion type\n");
	printf("4) List trains with locomotive\n");
	printf("5) Exit\n");	
}

tTrainMenuOptions getTrainMenuOption() {
	/* Convert to the correct type */
	return (tTrainMenuOptions)(getOption(5)-1);
}

void trainMenu(tAppData *appData) {
	tError retVal = OK;
	tTrainMenuOptions option;
	tTrainTable trainTable, propTable, locomotiveTable;
	tTrain newTrain;
	char trainStr[MAX_LINE];
	int propulsion;
			
	/* Start the menu */
	do {
		/* Show list of options and ask the user for an option */
		printTrainMenuOptions();
		option=getTrainMenuOption();
		
		/* Do the action for the given option */
		if (option == TRAIN_MENU_LIST) {
			getTrains(*appData, &trainTable);
			printTrainTable(trainTable);
		} else if (option == TRAIN_MENU_ADD) {
			readTrain(&newTrain,trainTable,&retVal);
			getTrainStr(newTrain, MAX_LINE, trainStr);
			if(retVal==OK) {
				addTrain(appData, newTrain, &retVal);
				if(retVal==ERR_DUPLICATED_ENTRY) {
					printf("ERROR: A train with the same ID already exists\n");
				} else {
					printf("Train added: %s\n", trainStr);
				}
			} else {
				printf("Error in input. Train not added: %s\n", trainStr);
			}
		} else if (option == TRAIN_MENU_PROPULSION) {
			getTrains(*appData, &trainTable);
			printf("Train type of propulsion (1 digit being 0=ELECTRICAL 1=CARBON 2=SOLAR 3=GASOLINE 4=DIESEL 5=MAGNETIC):\n");
			scanf("%d",&propulsion);
			trainsTable_filterByPropulsion(trainTable, (tPropulsion)propulsion, &propTable);
			printTrainTable(propTable);
		} else if (option == TRAIN_MENU_LOCOMOTIVES) {
			getTrains(*appData, &trainTable);
			trainsTable_getTrainsWithLocomotive(trainTable, &locomotiveTable);
			printTrainTable(locomotiveTable);
		}
	} while(option!=TRAIN_MENU_EXIT);	
}


/******************
 **   STAT MENU **
******************/
void printStatMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Stats \n");
	printf("=======================\n");
	printf("1) Get number of fragile goods\n");	
	printf("2) Get max good height\n");	
	printf("3) Get average train capacity for a type of propulsion\n");	
	printf("4) Get maximum train speed\n");
	printf("5) Get percentage of attended orders\n");	
	printf("6) Exit\n");	
}


tStatMenuOptions getStatMenuOption() {
	/* Convert to the correct type */
	return (tStatMenuOptions)(getOption(6)-1);
}

void statMenu(tAppData appData) {
	tStatMenuOptions option;
	tGoodTable goodTable;
	tTrainTable trainTable;
	float maxHeight, percentage;
    int propulsion, numFragileGoods, totalOrders;
	
	/* Start the menu */
	do {
		/* Show list of options and ask the user for an option */
		printStatMenuOptions();
		option=getStatMenuOption();
		
		/* Do the action for the given option */
		if (option == STAT_MENU_NUM_FRAGILE_GOODS) {			
			getGoods(appData, &goodTable);
			numFragileGoods= goodTable_getNumberOfFragileGoods(goodTable); 
			printf("Number of fragile goods: %d\n", numFragileGoods);

		} else if (option == STAT_MENU_MAX_HEIGHT) {
			getGoods(appData, &goodTable);
			maxHeight= goodTable_getMaxGoodHeight(goodTable); 
			printf("Maximum height for a good is: %.2f m\n", maxHeight);
		
		} else if (option == STAT_MENU_AVG_CAPACITY) {
			getTrains(appData, &trainTable);
			printf("Train type of propulsion (1 digit being 0=ELECTRICAL 1=CARBON 2=SOLAR 3=GASOLINE 4=DIESEL 5=MAGNETIC):\n");
			scanf("%d",&propulsion);
			printf("Average capacity by propulsion type: %.2f m3\n", trainsTable_getAverageCapacityByPropulsion(trainTable,(tPropulsion)propulsion));

		} else if (option == STAT_MENU_MAX_TRAIN_SPEED) {
			getTrains(appData, &trainTable);
			printf("Maximum speed: %.2f km/h\n", trainsTable_getMaxTrainSpeed(trainTable));

		} else if (option == STAT_MENU_PERCENTAGE_ATTENDED_ORDERS) {
            totalOrders= appData.attendedOrders.nOrders + appData.unattendedOrders.nOrders;
            if (totalOrders > 0)
                percentage= (float)appData.attendedOrders.nOrders / (float)totalOrders;
            else
                percentage= 0.0;
			printf("Percentage of attended orders (considering only processed orders): %.2f %%\n", percentage);
		} 

	} while(option!=STAT_MENU_EXIT);	
}

/******************
 **  CENTER MENU **
******************/

void printCenterMenuOptions()
{
	/* Show menu options */
	printf("=======================\n");
	printf(" Distribution Centers \n");
	printf("=======================\n");
	printf("1) Stock management\n");	
	printf("2) Trains on station management\n");	
	printf("3) Exit\n");	
}

tCenterMenuOptions getCenterMenuOption()
{
	/* Convert to the correct type */
	return (tCenterMenuOptions)(getOption(3)-1);
}

void centerMenu(tAppData *appData)
{
	tCenterMenuOptions option;
	
	/* Start the menu */
	do {
		/* Show list of options and ask the user for an option */
		printCenterMenuOptions();
		option=getCenterMenuOption();
		
		/* Do the action for the given option */
		if (option == CENTER_MENU_STOCK) {			
            stockMenu(appData);
            
		} else if (option == CENTER_MENU_TRAINS_ON_STATION) {
            trainOnStationMenu(appData);
		} 
		
	} while(option!=CENTER_MENU_EXIT);
}

/******************
 **  STOCK MENU **
******************/

void printStockMenuOptions()
{
	/* Show menu options */
	printf("=======================\n");
	printf(" Manage stocks \n");
	printf("=======================\n");
	printf("1) Add stock to warehouse\n");	
	printf("2) Remove stock from warehouse\n");	
	printf("3) Clean all stocks\n");	
	printf("4) List stocks\n");	
	printf("5) Exit\n");	
}

tStockMenuOptions getStockMenuOption()
{
	/* Convert to the correct type */
	return (tStockMenuOptions)(getOption(5)-1);
}

void stockMenu(tAppData *appData)
{
	tStockMenuOptions option;
    int goodId, qtt, index;
    char center;
	
	/* Start the menu */
	do {
		/* Show list of options and ask the user for an option */
		printStockMenuOptions();
		option=getStockMenuOption();
		              
		/* Do the action for the given option */
		if (option == STOCK_MENU_ADD_STOCK_TO_WAREHOUSE) {	

            if (appData->goods.nGoods > 0)
            {
                center= getValidCenter();  

                printf("Enter the number of the good to increase stock:\n");
                printGoodTable(appData->goods);
                index=getOption(appData->goods.nGoods)-1;
                goodId= appData->goods.table[index].id;

                printf("Specify the number of (positive) units to increase stock:\n");
                scanf("%d",&qtt);
                
                addStock(appData, center, goodId, qtt);
                printf("Stock added successfuly\n");
            }
            else 
                printf("No goods\n");                
		
		} else if (option == STOCK_MENU_REMOVE_STOCK_FROM_WAREHOUSE) {

            if (appData->goods.nGoods > 0)
            {
                center= getValidCenter();
                
                printf("Enter the number of the good to decrease stock:\n");
                if (center == 'A') {
                    printStockTable(appData->centerA.wareHouse, appData->goods);
                    index=getOption(appData->centerA.wareHouse.nGoods)-1;
                    goodId= appData->centerA.wareHouse.stock[index].id;
                } else {
                    printStockTable(appData->centerB.wareHouse, appData->goods);                    
                    index=getOption(appData->centerB.wareHouse.nGoods)-1;
                    goodId= appData->centerB.wareHouse.stock[index].id;
                }
            
                printf("Specify the number of (positive) units to decrease stock:\n");
                scanf("%d",&qtt);
            
                removeStock(appData, center, goodId, qtt);
            }
            else
                printf("No goods\n");                

		} else if (option == STOCK_MENU_CLEAN_ALL_STOCKS) {
            
            center= getValidCenter();
            cleanStocks(appData,center);
            printf("Stocks cleaned successfuly\n");

		} else if (option == STOCK_MENU_LIST_STOCKS) {
            
            center= getValidCenter();

            if (center == 'A')
                printStockTable(appData->centerA.wareHouse, appData->goods);
            else 
                printStockTable(appData->centerB.wareHouse, appData->goods);
        } 		
	} while(option!=STOCK_MENU_EXIT);
}

/*****************************
 **  TRAINS ON STATION MENU **
******************************/

void printTrainOnStationMenuOptions()
{
	/* Show menu options */
	printf("==========================\n");
	printf(" Manage trains on station \n");
	printf("==========================\n");
	printf("1) Add train to station\n");	
	printf("2) Remove train from station\n");	
	printf("3) Clean all trains\n");	
	printf("4) List trains on station\n");
	printf("5) Exit\n");	
}

tTrainOnStationMenuOptions getTrainOnStationMenuOption()
{
	/* Convert to the correct type */
	return (tTrainOnStationMenuOptions)(getOption(5)-1);
}

void trainOnStationMenu(tAppData *appData)
{
	tTrainOnStationMenuOptions option;
    tTrainId trainId;
    char center, platform;
    int index;
	tError retVal;

    retVal= OK;
    index= NO_TRAIN;
    trainId= NO_TRAIN;
	
	/* Start the menu */
	do {
		/* Show list of options and ask the user for an option */
		printTrainOnStationMenuOptions();
		option=getTrainOnStationMenuOption();

		/* Do the action for the given option */
		if (option == TRAIN_ON_STATION_MENU_ADD_TRAIN) {	
            
            if (appData->trains.nTrains > 0)
            {
                printf("Enter the number of the train to add to the platform:\n");
                printTrainTable(appData->trains);
                index=getOption(appData->trains.nTrains)-1;
                trainId= appData->trains.table[index].id;
                
                if (!checkTrainInPlatform(*appData,trainId)) 
                {
                    center= getValidCenter();
                    platform= getValidPlatform();
                    addTrainToPlatform(appData,trainId,center,platform,&retVal);
                    if (retVal != OK)
                        printf("Error adding a train to the platform.\n");
                    else
                        printf("Train successfuly added to the platform.\n");
                }
                else
                        printf("Train already in a platform. Please, remove from the current platform first.\n");
            }
            else
                printf("No trains\n");
            
		} else if (option == TRAIN_ON_STATION_MENU_REMOVE_TRAIN) {
            
            if (appData->trains.nTrains > 0)
            {
                center= getValidCenter();
                platform= getValidPlatform();
                trainId= NO_TRAIN;
                
                printf("Enter the number of the train to remove from the platform:\n");
                if (center=='A' && platform=='M') {
                    printTrainPlatform(appData->centerA.mainPlatform,appData->trains);
                    if (appData->centerA.mainPlatform.nElem>0) {
                        index=getOption(appData->centerA.mainPlatform.nElem)-1;
                        trainId= trainAt(appData->centerA.mainPlatform, index);                        
                    }
                }
                else if (center=='A' && platform=='S') {
                    printTrainPlatform(appData->centerA.siding,appData->trains);  
                    if (appData->centerA.siding.nElem>0) {
                        index=getOption(appData->centerA.siding.nElem)-1;
                        trainId= trainAt(appData->centerA.siding, index);                        
                    }
                }
                else if (center=='B' && platform=='M') {
                    printTrainPlatform(appData->centerB.mainPlatform,appData->trains);
                    if (appData->centerB.mainPlatform.nElem>0) {
                        index=getOption(appData->centerB.mainPlatform.nElem)-1;
                        trainId= trainAt(appData->centerB.mainPlatform, index);                        
                    }
                }
                else if (center=='B' && platform=='S') 
                {
                    printTrainPlatform(appData->centerB.siding,appData->trains);
                    if (appData->centerB.siding.nElem>0) {
                        index=getOption(appData->centerB.siding.nElem)-1;
                        trainId= trainAt(appData->centerB.siding, index);                        
                    }
                }
                                
                if (trainId != NO_TRAIN) 
                {
                    removeTrainFromPlatform(appData,trainId,center,platform,&retVal);
                    if (retVal != OK)
                        printf("Error removing a train from the platform.\n");
                    else 
                        printf("Train succesfuly removed from the platform.\n");                    
                }
            }
            else
                printf("No trains\n");

		} else if (option == TRAIN_ON_STATION_MENU_CLEAN_ALL_TRAINS) {
            
            if (appData->trains.nTrains > 0)
            {
                center= getValidCenter();
                removeAllTrainsOfCenter(appData,center,&retVal);
                if (retVal != OK)
                    printf("Error cleaning trains of a distribution center.\n");
                else
                    printf("Trains succesfuly cleaned from the distribution center.\n");
            }
            else
                printf("No trains\n");

		} else if (option == TRAIN_ON_STATION_MENU_LIST_TRAINS) {
            
            if (appData->trains.nTrains > 0)
            {
                center= getValidCenter();
                
                if (center=='A') {
                    printf("Distribution center A. Main platform:\n");
                    printTrainPlatform(appData->centerA.mainPlatform, appData->trains); 
                    printf("\n");
                    printf("Distribution center A. Siding:\n");
                    printTrainPlatform(appData->centerA.siding, appData->trains);                
                }
                else if (center=='B')
                {
                    printf("Distribution center B. Main platform:\n");
                    printTrainPlatform(appData->centerB.mainPlatform, appData->trains);
                    printf("\n");
                    printf("Distribution center B. Siding:\n");
                    printTrainPlatform(appData->centerB.siding, appData->trains);                                     
                }
            }
            else
                printf("No trains\n");
        } 		
	} while(option!=TRAIN_ON_STATION_MENU_EXIT);
}

/*******************
 **  ORDERS MENU **
*******************/

void printOrderMenuOptions()
{
	/* Show menu options */
	printf("==========================\n");
	printf(" Manage orders  \n");
	printf("==========================\n");
	printf("1) Add pending order\n");	
	printf("2) Clean all orders\n");	
	printf("3) List orders\n");
	printf("4) Process order\n");
	printf("5) Exit\n");	
}

tOrderMenuOptions getOrderMenuOption()
{
	/* Convert to the correct type */
	return (tOrderMenuOptions)(getOption(5)-1);
}

void orderMenu(tAppData *appData)
{
	tOrderMenuOptions option;
    tOrder order;
    char orderType;
    int number, qtt, index;
    tError retVal;
	
	/* Start the menu */
    retVal= OK;
	do {
		/* Show list of options and ask the user for an option */
		printOrderMenuOptions();
		option=getOrderMenuOption();

		/* Do the action for the given option */
		if (option == ORDERS_MENU_ADD_PENDING_ORDER) 
        {            
            if (appData->goods.nGoods > 0)
            {
                /* Get a valid id for this order */
                number= (int)getUnusedOrderId(*appData);
                while (number > MAX_ORDERS || number < 0) {
                    printf("Invalid id for a order. Please, try again\n");
                    number= (int)getUnusedOrderId(*appData);
                }
                order.id = (tOrderId)number;
                getchar();

                /* Ask for origin center */
                printf("Origin location. ");
                order.originCenter= getValidCenter();
                
                /* Ask for destination center */
                if (order.originCenter == 'A')
                {
                    printf("Destination location:\nB\n");
                    order.destinationCenter= 'B';
                }
                else
                {
                    printf("Destination location:\nA\n");
                    order.destinationCenter= 'A';           
                }

                /* Ask for the good to move */
                printf("Select the order good:\n");
                printGoodTable( appData->goods );
                index= getOption( appData->goods.nGoods )-1;
                order.goodsOrdered.id= goodTable_goodAt(appData->goods,index).id;
                
                /* Ask for the quantity of good to move */
                printf("Type the number of units of the good for this order:\n");
                scanf("%d",&qtt);
                order.goodsOrdered.qtt= qtt;
                
                addPendingOrder(appData, order, &retVal);
                printf("Pending order succesfuly added.\n");
            }
            else
                printf("No goods.\n");

		} else if (option == ORDERS_MENU_CLEAN_ALL_ORDERS) {

            cleanAllOrders(appData);
            printf("Orders succesfuly cleaned.\n");
                
		} else if (option == ORDERS_MENU_LIST_ORDERS) {
            
            orderType= getValidTypeOfOrder();
            if (orderType == 'P')                 
                printOrderTable( appData->pendingOrders );
            else if (orderType == 'A')
                printOrderTable( appData->attendedOrders );
            else
                printOrderTable( appData->unattendedOrders );
            
		} else if (option == ORDERS_MENU_PROCESS_ORDER) {
            
            processOrders( appData, &retVal );
            if(retVal==OK) {
                printf("Orders sucessfuly processed\n");
            } else {	
                printf("Error while processing orders\n");
            }
        } 		
	} while(option!=ORDERS_MENU_EXIT);
}
