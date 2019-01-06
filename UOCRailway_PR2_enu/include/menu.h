#include "data.h"
#include "api.h"

/* Request an option to the user and check its validity */
int getOption(int numOptions);

/* Define the main menu options type */
typedef enum {MAIN_MENU_LOAD, MAIN_MENU_SAVE, MAIN_MENU_GOOD, MAIN_MENU_TRAIN, 
              MAIN_MENU_CENTER, MAIN_MENU_ORDER,  MAIN_MENU_STAT,
              MAIN_MENU_EXIT} tMainMenuOptions;

/* Define the goods management menu options type */
typedef enum {GOOD_MENU_LIST, GOOD_MENU_ADD, GOOD_MENU_DEL, 
              GOOD_MENU_CLEAR_ALL, GOOD_MENU_GOODS_BY_TYPE,
			  GOOD_MENU_GOODS_BY_WEIGHT_INTERVAL,
              GOOD_MENU_EXIT} tGoodMenuOptions;

/* Define the trains management menu options type */
typedef enum {TRAIN_MENU_LIST, TRAIN_MENU_ADD, TRAIN_MENU_PROPULSION, TRAIN_MENU_LOCOMOTIVES,
              TRAIN_MENU_EXIT} tTrainMenuOptions;

/* Define the status menu options type */
typedef enum {STAT_MENU_NUM_FRAGILE_GOODS,  STAT_MENU_MAX_HEIGHT,
			  STAT_MENU_AVG_CAPACITY, STAT_MENU_MAX_TRAIN_SPEED,
              STAT_MENU_PERCENTAGE_ATTENDED_ORDERS,
              STAT_MENU_EXIT} tStatMenuOptions;

/* Define the centers menu options type */
typedef enum {CENTER_MENU_STOCK, CENTER_MENU_TRAINS_ON_STATION,
              CENTER_MENU_EXIT} tCenterMenuOptions;

/* Define the stock menu options type */
typedef enum {STOCK_MENU_ADD_STOCK_TO_WAREHOUSE, STOCK_MENU_REMOVE_STOCK_FROM_WAREHOUSE,
              STOCK_MENU_CLEAN_ALL_STOCKS, STOCK_MENU_LIST_STOCKS,
              STOCK_MENU_EXIT} tStockMenuOptions;
              
/* Define the trains on station menu options type */
typedef enum {TRAIN_ON_STATION_MENU_ADD_TRAIN, TRAIN_ON_STATION_MENU_REMOVE_TRAIN,
              TRAIN_ON_STATION_MENU_CLEAN_ALL_TRAINS, TRAIN_ON_STATION_MENU_LIST_TRAINS,
              TRAIN_ON_STATION_MENU_EXIT} tTrainOnStationMenuOptions;

/* Define the orders menu options type */
typedef enum {ORDERS_MENU_ADD_PENDING_ORDER, 
              ORDERS_MENU_CLEAN_ALL_ORDERS, ORDERS_MENU_LIST_ORDERS,
              ORDERS_MENU_PROCESS_ORDER,
              ORDERS_MENU_EXIT} tOrderMenuOptions;
              
/* Print the main menu options */
void printMainMenuOptions();

/* Get the option for the main menu */
tMainMenuOptions getMenuOption();

/* Perform the actions for the main menu */
void mainMenu(tAppData *appData);

/* Print the good management menu options */
void printGoodMenuOptions();

/* Get the option for the good management menu */
tGoodMenuOptions getGoodMenuOption();

/* Perform the actions for the good management menu */
void goodMenu(tAppData *appData);

/* Print the trains management menu options */
void printTrainMenuOptions();

/* Get the option for the trains management menu */
tTrainMenuOptions getTrainMenuOption();

/* Perform the actions for the trains management menu */
void trainMenu(tAppData *appData);

/* Print the stats menu options */
void printStatMenuOptions();

/* Get the option for the status menu */
tStatMenuOptions getStatMenuOption();

/* Perform the actions for the status menu */
void statMenu(tAppData appData);

/* Print the centers management menu options */
void printCenterMenuOptions();

/* Get the option for the center management menu */
tCenterMenuOptions getCenterMenuOption();

/* Perform the actions for the center management menu */
void centerMenu(tAppData *appData);

/* Print the stock management menu options */
void printStockMenuOptions();

/* Get the option for the stock management menu */
tStockMenuOptions getStockMenuOption();

/* Perform the actions for the stock management menu */
void stockMenu(tAppData *appData);

/* Print the trains on station management menu options */
void printTrainOnStationMenuOptions();

/* Get the option for the trains on station management menu */
tTrainOnStationMenuOptions getTrainOnStationMenuOption();

/* Perform the actions for the trains on station management menu */
void trainOnStationMenu(tAppData *appData);

/* Print the orders management menu options */
void printOrderMenuOptions();

/* Get the option for the orders management menu */
tOrderMenuOptions getOrderMenuOption();

/* Perform the actions for the orders management menu */
void orderMenu(tAppData *appData);