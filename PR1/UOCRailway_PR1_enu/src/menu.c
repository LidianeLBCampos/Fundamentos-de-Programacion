#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "train.h"
#include "good.h"

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

void readGood(tGood *good, tError *retVal) {	

	*retVal = OK;

    char buffer[MAX_LINE];
	int number, length;

	printf("Good id (integer less than %d):\n>> ", MAX_GOODS);
	scanf("%d",&number);
	if(number>MAX_GOODS) {
		*retVal = ERROR;
	} else {
		good->id= (tGoodId)(number);
	}
	getchar();

	printf("Good name (max 20 char, no spaces):\n>> ");
    scanf("%s",buffer);
	length = strlen(buffer);
	if (length<MAX_NAME) {
		strncpy(good->name,buffer,MAX_NAME);
	} else {
		*retVal = ERROR;
	}
	getchar();

	printf("Good type digit being(1-FOOD, 2-CHEMICAL, 3-ANIMALS, 4-VEHICLES, 5-ELETRONICS, 6-CONSTRUCTION, 0-OTHERS):\n>> ");
   	scanf("%d",&number);
	if(number>=0 && number <=6) {
		good->type= (tGoodType)(number);
	} else {
		*retVal = ERROR;
	}
	getchar();

	printf("Price of each kilogram of the good:\n>> ");
	scanf("%f",&(good->price));
	getchar();

	printf("Good weight (in kilogram: \n>> ");
	scanf("%f", &(good->weight));
	getchar();

	printf("Good height(in metres): \n>> ");
	scanf("%f", &(good->height));
	getchar();

	printf("Good volume (in metres cubic): \n>> ");
	scanf("%f", &(good->volume));
	getchar();

	printf("TThe layers' maximum(digit 0 if no layer is allowed): \n>> ");
	scanf("%d", &(good->maxLayers));
	getchar();

	printf("Is it Fragile? (YES/NO):\n>> ");
	scanf("%s", buffer);
	if (strcmp(buffer,"YES") == 0 || strcmp(buffer,"yes") == 0) {
		good->isFragile = TRUE;
	} else if  (strcmp(buffer,"NO") == 0 || strcmp(buffer,"no") == 0) {
		good->isFragile = FALSE;
	} else {
		*retVal = ERROR;
	}
	getchar();

	printf("Is it Dangerous? (YES/NO):\n>> ");
	scanf("%s", buffer);
	if (strcmp(buffer,"YES") == 0 || strcmp(buffer,"yes") == 0) {
		good->isDangerous = TRUE;
	} else if  (strcmp(buffer,"NO") == 0 || strcmp(buffer,"no") == 0) {
		good->isDangerous = FALSE;
	} else {
		*retVal = ERROR;
	}
	getchar();
}


void readTrain(tTrain *train, tError *retVal) {	

	*retVal = OK;

	char buffer[MAX_LINE];
	int number, length;

	printf("Train id (integer less than %d):\n>> ",MAX_TRAINS);
	scanf("%d",&number);
	if(number>MAX_TRAINS) {
		*retVal = ERROR;
	} else {
		train->id= (tTrainId)(number);
	}
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
	printf("5) View statistics\n");
	printf("6) Exit\n");	
}

tMainMenuOptions getMainMenuOption() {
	/* Convert to the correct type */
	return (tMainMenuOptions)(getOption(6)-1);
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
			readGood(&newGood,&retVal);
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
			printf("Good Type (1 digit being 1=FOOD, 2=CHEMICAL, 3=ANIMALS, 4=VEHICLES, 5=ELECTRONICS, 6=CONSTRUCTION, 0=OTHERS):\n");
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
			readTrain(&newTrain,&retVal);
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
	printf("5) Exit\n");	
}


tStatMenuOptions getStatMenuOption() {
	/* Convert to the correct type */
	return (tStatMenuOptions)(getOption(5)-1);
}

void statMenu(tAppData appData) {
	tStatMenuOptions option;
	tGoodTable goodTable;
	tTrainTable trainTable;
	float maxHeight;
    int propulsion, numFragileGoods;
	
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
			printf("Average capacity by propulsion type: %.2f m3\n", trainTable_getAverageCapacityByPropulsion(trainTable,(tPropulsion)propulsion));
		} else if (option == STAT_MENU_MAX_TRAIN_SPEED) {
			getTrains(appData, &trainTable);
			printf("Maximum speed: %.2f km/h\n", trainTable_getMaxTrainSpeed(trainTable));
		} 
		
	} while(option!=STAT_MENU_EXIT);	
}

