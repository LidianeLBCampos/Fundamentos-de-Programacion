/* This code ensures that this file is included only once */
#ifndef __DATA_H
#define __DATA_H
/* If the constant DATA_H is not defined (ifndef), the code is added, otherwise,
 * this code is excluded. When the code is added, the constant is defined, 
 * therefore next time this file will be included it will be defined and no 
 * inclusion will be done. */

#define MAX_NAME 20+1
#define MAX_GOODS 100
#define MAX_TRAINS 20
#define MAX_PATHNAME 480
#define MAX_LINE 512
#define MAX_TRAINS_IN_STACK 20
#define MAX_ORDERS 100
#define NO_TRAIN -1
#define NO_GOOD -1
#define NO_ORDER -1

/* Definition of a boolean type */
typedef enum {FALSE, TRUE} tBoolean;

/* Definition of the error type. */
typedef enum {OK=1, ERROR=0, ERR_CANNOT_READ=-1, ERR_CANNOT_WRITE=-2, 
              ERR_MEMORY=-3, ERR_DUPLICATED_ENTRY=-4, ERR_INVALID_DATA=-5, 
              ERR_ENTRY_NOT_FOUND=-6,
              ERR_NO_GOOD=-7,ERR_NO_TRAIN=-8,ERR_NO_FREE_GAP=-9} tError;

typedef int tGoodId;
typedef int tTrainId;
typedef int tOrderId;

typedef enum {
	ELECTRICAL, CARBON, SOLAR, GASOLINE, DIESEL, MAGNETIC 
} tPropulsion;

typedef struct {
    tTrainId id; 
	char brand[MAX_NAME]; 
	char model[MAX_NAME]; 
	int  year; 
	tPropulsion propulsionType; 
	int  nWagons; 
	float wagonCapacity; 
	tBoolean hasLocomotive; 
	float weight; 
	float length; 
	float maxSpeed; 
} tTrain;

typedef struct {
	tTrain table[MAX_TRAINS];
	int nTrains;
} tTrainTable;

typedef enum {
  FOOD, CHEMICAL, ANIMALS, VEHICLES, ELECTRONICS, CONSTRUCTION, OTHERS
} tGoodType;

typedef struct {
    tGoodId id;
	char name[MAX_NAME];	
	tGoodType type;
	float price;
	float weight;
	float height;
	float volume;
	int layers;
	tBoolean isFragile;
	tBoolean isDangerous;
} tGood;

typedef struct {
	tGood table[MAX_GOODS];
	int nGoods;
} tGoodTable;

typedef struct {
    tGoodId id;
    int qtt;
} tGoodQtt;

typedef struct {
  tTrainId id;
  tGoodQtt load;
} tLoadedTrain;

typedef struct {
	tLoadedTrain table[MAX_TRAINS_IN_STACK];
	unsigned int nElem;
} tTrainStack;

typedef struct {
  tGoodQtt stock[MAX_GOODS];
  int nGoods;
} tWareHouse;

typedef struct {
  char id;
  tTrainStack mainPlatform; /* main platform, where trains get in and out of the station */
  tTrainStack siding; /* seconday platform, where trains may be moved in and out temporaly for several purposes*/
  tWareHouse wareHouse;
} tDistributionCenter;

typedef struct {
  tOrderId id;
  char originCenter;
  char destinationCenter;
  tGoodQtt goodsOrdered;
} tOrder;

typedef struct {
  tOrder table[MAX_ORDERS];
  int nOrders;
} tOrderTable;

/* Definition of the application data structure */
typedef struct {
	/* Path where data will be stored */
	char path[MAX_PATHNAME];
	
	/* Trains table */
	tTrainTable trains;
	
	/* Goods table */
	tGoodTable goods;
    
    /* Distribution center at location A */
    tDistributionCenter centerA;
    
    /* Distribution center at location B */
    tDistributionCenter centerB;
    
    /* Pending orders */
    tOrderTable pendingOrders;

    /* Attended orders */
    tOrderTable attendedOrders;
    
    /* Unattended orders */
    tOrderTable unattendedOrders;
	
} tAppData;

#endif /*__DATA_H*/