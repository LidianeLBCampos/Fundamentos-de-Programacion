#include "data.h"
#include "api.h"

/* Request an option to the user and check its validity */
int getOption(int numOptions);

/* Define the main menu options type */
typedef enum {MAIN_MENU_LOAD, MAIN_MENU_SAVE, MAIN_MENU_GOOD, 
              MAIN_MENU_TRAIN, MAIN_MENU_STAT,
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
              STAT_MENU_EXIT} tStatMenuOptions;

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
