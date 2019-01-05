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
#define MAX_PATHNAME 500
#define MAX_LINE 512
#define NO_TRAIN -1
#define NO_GOOD -1

/* Definition of a boolean type */
typedef enum {FALSE, TRUE} tBoolean;

/* Definition of the error type. */
typedef enum {OK=1, ERROR=0, ERR_CANNOT_READ=-1, ERR_CANNOT_WRITE=-2, 
              ERR_MEMORY=-3, ERR_DUPLICATED_ENTRY=-4, ERR_INVALID_DATA=-5, 
              ERR_ENTRY_NOT_FOUND=-6,
              ERR_NO_GOOD=-7,ERR_NO_TRAIN=-8,ERR_NO_FREE_GAP=-9} tError;

typedef int tGoodId;
typedef int tTrainId;

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

/* Definition of a good type */
typedef enum{
	FOOD, CHEMICAL, ANIMALS,VEHICLES, ELETRONICS, CONSTRUCTION, OTHERS
} tGoodType; 


typedef struct {
    tGoodId id;
	char name[MAX_NAME];	
	tGoodType type;
	float price;
	float weight;
	float height;
	float volume;
	int maxLayers;
	tBoolean isFragile;
	tBoolean isDangerous;
} tGood;

typedef struct {
	tGood table[MAX_GOODS];
	int nGoods;
} tGoodTable;

/* Definition of the application data structure */
typedef struct {
	/* Path where data will be stored */
	char path[MAX_PATHNAME];
	
	/* Trains table */
	tTrainTable trains;
	
	/* Goods table */
	tGoodTable goods;
	
} tAppData;

#endif /*__DATA_H*/