#include <stdio.h>
#include <string.h>
#include <math.h>
#include "test.h"
#include "good.h"
#include "train.h"
#include "stack.h"
#include "center.h"

#define GOOD1 "10 FLOUR 0 0.25 25.00 0.50 0.60 3 0 0"
#define GOOD2 "11 SOLVENT 1 5.00 20.00 0.40 0.40 2 0 1"
#define GOOD3 "05 BOVINE 2 10.50 200.00 0.80 2.00 0 0 0"
#define GOOD4 "15 MOTORBIKE 3 30.00 250.00 1.00 2.00 0 1 0"
#define GOOD5 "16 ACID 1 3.00 15.00 0.40 1.00 3 0 1"
#define GOOD6 "06 POULTRY 2 2.50 30.00 0.20 0.50 0 0 0"

#define TRAIN1 "10 ALSTOM DUALIS 2017 0 5 200.00 1 1.50 15.00 250.00"
#define TRAIN2 "11 ALSTOM CORADIA 2015 1 8 150.00 0 2.00 12.00 225.00"
#define TRAIN3 "5 TALGO AVRIL 2015 0 7 125.00 1 1.00 13.00 300.00"
#define TRAIN4 "15 SIEMENS VELARO 2018 2 6 225.00 0 1.50 15.00 250.00"
#define TRAIN5 "16 SIEMENS ICE4 2016 3 5 100.00 1 2.00 10.00 200.00"
#define TRAIN6 "6 TALGO AVRIL2 2018 3 5 100.00 1 2.00 10.00 200.00"

#define LOADED_TRAIN1 "10 06 100"
#define LOADED_TRAIN2 "11 16 150"
#define LOADED_TRAIN3 "5 15 200"
#define LOADED_TRAIN4 "15 05 250"
#define LOADED_TRAIN5 "16 11 300"
#define LOADED_TRAIN6 "6 10 350"

#define WAREHOUSE_1 "2 10 150 5 100"

#define PLATFORM_STACK1 "2 11 -1 0 10 -1 0"
#define PLATFORM_STACK2 "0"
#define PLATFORM_STACK3 "1 5 15 50"
#define PLATFORM_STACK4 "1 5 10 50"

void runTests() {	
	int passedTestPR2=0;
	int totalTestPR2=0;

	printf("=================================================\n");
	printf("====       PRACTICAL ACTIVITY 2 TESTS        ====\n");
	printf("=================================================\n");	
	runTestsPR2(&totalTestPR2, &passedTestPR2);   
        
	printf("===================================\n");
	printf("====       TEST SUMMARY        ====\n");
	printf("===================================\n");
    if (totalTestPR2 > 0)
        printf("\tPR2: Passed %d of %d [%0.2f%%]\n", passedTestPR2, totalTestPR2, (float)passedTestPR2/totalTestPR2*100.0);
    printf("===================================\n");		
}

void runTestsPR2(int* totalTest, int* passedTest)
{
	*totalTest=0;
	*passedTest=0;

	/* Exercise 1 */
	test_init(totalTest, passedTest);
	test_push(totalTest, passedTest);
	test_top(totalTest, passedTest);
	test_pop(totalTest, passedTest);
	test_empty(totalTest, passedTest);
	test_full(totalTest, passedTest);
    test_invert(totalTest, passedTest);
	test_stack_persistence(totalTest, passedTest);

	/* Exercise 2 */
	test_check_stocks(totalTest, passedTest);
    test_search_train(totalTest, passedTest);
    test_load_train(totalTest, passedTest);
    test_train_transport(totalTest, passedTest);    
    test_unload_train(totalTest, passedTest);  
}

void test_init(int *totalTest, int *passedTest) 
{	
	tTrainStack s;

	printf("=================================================\n");
	printf(" STACK INIT (Exercise 1A)\n");
	printf("=================================================\n");

	printf("\nTest 1A.1: Initialization");
	(*totalTest)++;
	s = trainStack_create();

    if (s.nElem==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
}

void test_top(int *totalTest, int *passedTest) 
{	
	tTrainStack s;
	tLoadedTrain t1, t2, t3;

	printf("=================================================\n");
	printf(" STACK TOP (Exercise 1C)\n");
	printf("=================================================\n");

	printf("\nTest 1C.1: Top of a one element stack");
	(*totalTest)++;

	s.nElem=0;
	getLoadedTrainObject(LOADED_TRAIN1,&t1);
	loaded_train_cpy(&(s.table[0]),t1);

	s.nElem=1;
	t2 = trainStack_top(s);

    if (loaded_train_cmp(t1,t2)==0 && loaded_train_cmp(s.table[0],t2)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 1C.2: Top of a two element stack");
	(*totalTest)++;
	getLoadedTrainObject(LOADED_TRAIN2,&t2);
	loaded_train_cpy(&(s.table[1]),t2);
	s.nElem=2;
	t3 = trainStack_top(s);

    if (loaded_train_cmp(t2,t3)==0 && loaded_train_cmp(s.table[1],t3)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
}

void test_empty(int *totalTest, int *passedTest) 
{	
	tTrainStack s;

	printf("=================================================\n");
	printf(" STACK EMPTY (Exercise 1E)\n");
	printf("=================================================\n");
	printf("\nTest 1E.1: Check empty (simple)");
    
	(*totalTest)++;
	s.nElem=0;

    if (trainStack_empty(s)) {
        printf("\n\t-> OK\n");
		(*passedTest)++;

	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 1E.2: Check empty (using init)");
	(*totalTest)++;
	s = trainStack_create();
    if (trainStack_empty(s)) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
}

void test_full(int *totalTest, int *passedTest) 
{	
	tTrainStack s;
	tLoadedTrain t;

	int i;
	printf("=================================================\n");
	printf(" STACK FULL (Exercise 1F)\n");
	printf("=================================================\n");

	printf("\nTest 1F.1: Check full (simple)");
	(*totalTest)++;
    
	s.nElem = MAX_TRAINS_IN_STACK;
    if (trainStack_full(s)) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 1F.2: Check full (pushing)");
	(*totalTest)++;
	s.nElem=0;
	getLoadedTrainObject(LOADED_TRAIN1,&t);

	for(i=0;i<MAX_TRAINS_IN_STACK;i++)
		trainStack_push(&s,t);

    if (trainStack_full(s)) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
}

void test_invert(int *totalTest, int *passedTest) 
{	
	tTrainStack s;
	tLoadedTrain t1, t2, t3, t;
	tLoadedTrain tout1, tout2, tout3;

	printf("=================================================\n");
	printf(" STACK INVERT (Exercise 1G)\n");
	printf("=================================================\n");

	printf("\nTest 1G.1: Invert empty stack");
	(*totalTest)++;
    
	s= trainStack_create();
    trainStack_invert(&s);
    if (trainStack_empty(s)) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 1G.2: Invert non empty stack (odd size)");
	(*totalTest)++;
	getLoadedTrainObject(LOADED_TRAIN1,&t1);
	getLoadedTrainObject(LOADED_TRAIN2,&t2);
	s= trainStack_create();
    trainStack_push(&s,t1);
    trainStack_push(&s,t2);
    trainStack_invert(&s);
    t= trainStack_top(s);
    if (loaded_train_cmp(t,t1)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 1G.3: Invert non empty stack (even size)");
	(*totalTest)++;
	s= trainStack_create();
	getLoadedTrainObject(LOADED_TRAIN3,&t3);
    trainStack_push(&s,t1);
    trainStack_push(&s,t2);
    trainStack_push(&s,t3);
    trainStack_invert(&s);
    tout1= trainStack_top(s);
    trainStack_pop(&s);
    tout2= trainStack_top(s);
    trainStack_pop(&s);
    tout3= trainStack_top(s);
    trainStack_pop(&s);
    if (trainStack_empty(s) && 
        loaded_train_cmp(tout1,t1)==0 &&
        loaded_train_cmp(tout2,t2)==0 &&
        loaded_train_cmp(tout3,t3)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
}

void test_push(int *totalTest, int *passedTest) 
{	
	tTrainStack s;
	tLoadedTrain t, t2;
	int i, prev_size, post_size;
    
	printf("=================================================\n");
	printf(" STACK PUSH (Exercise 1B)\n");
	printf("=================================================\n");

	printf("\nTest 1B.1: Push in empty stack");

	(*totalTest)++;
	s = trainStack_create();
	getLoadedTrainObject(LOADED_TRAIN1,&t);
	trainStack_push(&s,t);

    if ( s.nElem==1 && loaded_train_cmp(s.table[0],t)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
    
	printf("\nTest 1B.2: Push in not empty stack");
	(*totalTest)++;
	getLoadedTrainObject(LOADED_TRAIN2,&t2);
	trainStack_push(&s,t2);

    if ( s.nElem==2 && loaded_train_cmp(s.table[1],t2)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
    
	printf("\nTest 1B.3: Push in almost full stack");
	(*totalTest)++;
	s = trainStack_create();
	getLoadedTrainObject(LOADED_TRAIN1,&t);

	for(i=0;i<MAX_TRAINS_IN_STACK;i++)
		trainStack_push(&s,t);

    if (s.nElem==MAX_TRAINS_IN_STACK && 
        loaded_train_cmp(s.table[MAX_TRAINS_IN_STACK-1],t)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
    
	printf("\nTest 1B.4: Push in full stack");
	(*totalTest)++;
    prev_size= trainStack_size(s);
    trainStack_push(&s,t);
    post_size= trainStack_size(s);
    if (prev_size == MAX_TRAINS_IN_STACK && 
        prev_size == post_size) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
}

void test_pop(int *totalTest, int *passedTest) 
{	
	tTrainStack s;
	tLoadedTrain t1in, t1out, t2in, t2out;
	int i, prev_size, post_size;
    
	printf("=================================================\n");
	printf(" STACK POP (Exercise 1D)\n");
	printf("=================================================\n");

	printf("\nTest 1D.1: Pop in one element stack");
	(*totalTest)++;

	s = trainStack_create();
	getLoadedTrainObject(LOADED_TRAIN1,&t1in);
	trainStack_push(&s,t1in);
	t1out = trainStack_top(s);
	trainStack_pop(&s);

    if (s.nElem==0 && loaded_train_cmp(t1in,t1out)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
    
	printf("\nTest 1D.2: Pop in not empty stack");
	(*totalTest)++;
	s = trainStack_create();
	getLoadedTrainObject(LOADED_TRAIN1,&t1in);
	getLoadedTrainObject(LOADED_TRAIN2,&t2in);
	trainStack_push(&s,t1in);
	trainStack_push(&s,t2in);
	t1out = trainStack_top(s);
	trainStack_pop(&s);

    if (s.nElem==1 && 
        loaded_train_cmp(s.table[0],t1in)==0 && 
        loaded_train_cmp(t2in,t1out)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
    
	printf("\nTest 1D.3: Pop in full stack");
	(*totalTest)++;
	s = trainStack_create();
	getLoadedTrainObject(LOADED_TRAIN1,&t1in);
	trainStack_push(&s,t1in);
	getLoadedTrainObject(LOADED_TRAIN2,&t2in);

	for(i=1;i<MAX_TRAINS_IN_STACK;i++)
		trainStack_push(&s,t2in);

	t1out = trainStack_top(s);
	trainStack_pop(&s);

    if (s.nElem==MAX_TRAINS_IN_STACK-1 && 
        loaded_train_cmp(s.table[MAX_TRAINS_IN_STACK-2],t2in)==0 && 
        loaded_train_cmp(t2in,t1out)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 1D.4: Clear a full stack by popping elements");
	(*totalTest)++;
	s = trainStack_create();
	getLoadedTrainObject(LOADED_TRAIN1,&t1in);
	trainStack_push(&s,t1in);
	getLoadedTrainObject(LOADED_TRAIN2,&t2in);
	for(i=1;i<MAX_TRAINS_IN_STACK;i++)
		trainStack_push(&s,t2in);

	t1out = trainStack_top(s);
	trainStack_pop(&s);

	for(i=1;i<MAX_TRAINS_IN_STACK;i++) {
		t2out = trainStack_top(s);
		trainStack_pop(&s);
	}
	if ( s.nElem==0 && loaded_train_cmp(t1in,t2out)==0 && loaded_train_cmp(t2in,t1out)==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
    
	printf("\nTest 1D.5: Pop on empty stack");
	(*totalTest)++;
    prev_size= trainStack_size(s);
	trainStack_pop(&s);
    post_size= trainStack_size(s);
	if (prev_size==0 && 
        prev_size==post_size) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
}

void test_stack_persistence(int *totalTest, int *passedTest) 
{
	tTrainStack stack;
	tLoadedTrain t1, t2;
	tError retVal;

	printf("=================================================\n");
	printf(" PERSISTENCE OF TRAIN STACK (Exercise 1H/I)\n");
	printf("=================================================\n");

	printf("\nTest 1HI.1: Save and load no data");

	(*totalTest)++;
	stack = trainStack_create();	
	trainStack_save(stack, "./testTrains.csv",&retVal);

	stack = trainStack_create();	
	trainStack_load(&stack, "./testTrains.csv",&retVal);

	if(retVal==OK){

		if(trainStack_empty(stack)) {
			printf("\n\t-> OK\n");
			(*passedTest)++;

		} else {
			printf("\n\t-> FAIL (unexpected number of registers in the stack. Expected %d and returned %d)\n", 0, stack.nElem);
		}

	} else {
		printf("\n\t-> FAIL (problem in file reading/writing)\n");
	}

	printf("\nTest 1HI.2: Save and load trains");

	(*totalTest)++;

	getLoadedTrainObject(LOADED_TRAIN1, &t1);
	getLoadedTrainObject(LOADED_TRAIN2, &t2);
    trainStack_push(&stack,t1);
    trainStack_push(&stack,t2);
	trainStack_save(stack, "./testTrains.csv",&retVal);

	stack = trainStack_create();	
	trainStack_load(&stack, "./testTrains.csv",&retVal);
	trainStack_save(stack, "./testTrains2.csv",&retVal);

	if(retVal==OK){

		if(stack.nElem==2) {

			if(loaded_train_cmp(stack.table[1], t2) != 0 || 
			   loaded_train_cmp(stack.table[0], t1) != 0) {
				printf("\n\t-> FAIL (Values are not correct)\n");
			} else {
				printf("\n\t-> OK\n");
				(*passedTest)++;
			}

		} else {
			printf("\n\t-> FAIL (unexpected number of registers in the stack. Expected %d and returned %d)\n", 2, stack.nElem);
		}

	} else {
		printf("\n\t-> FAIL (problem in file reading/writing)\n");
	}
}

void test_check_stocks(int *totalTest, int *passedTest) {
	
	tBoolean result;
	tWareHouse wh;
	tGood good;
	
	printf("========================================\n");
	printf(" CHECK WAREHOUSE STOCKS (Exercise 2A.1) \n");
	printf("========================================\n");

	getGoodObject(GOOD1,&good);

	printf("\nTest 2A1.1: Check stock on an empty warehouse");
	(*totalTest)++;
	warehouse_cleanAllStocks(&wh);
	result= checkStockAtOrigin(wh, good, 10);
	if (!result) {
			printf("\n\t-> OK\n");
			(*passedTest)++;
	}
	else {
			printf("\n\t-> FAIL (Good found on an empty warehouse)\n");
	}

	getWareHouseObject(WAREHOUSE_1, &wh);
	
	printf("\nTest 2A1.2: Check enough stock of existing good on non-empty warehouse");
	(*totalTest)++;
	result= checkStockAtOrigin(wh, good, 150);
	if (result) {
			printf("\n\t-> OK\n");
			(*passedTest)++;
	}
	else {
			printf("\n\t-> FAIL (Returned \"enough stock\", \"not enough\" expected)\n");
	}
	
	printf("\nTest 2A1.3: Check not enough stock of existing good on non-empty warehouse");
	(*totalTest)++;
	result= checkStockAtOrigin(wh, good, 151);
	if (!result) {
			printf("\n\t-> OK\n");
			(*passedTest)++;
	}
	else {
			printf("\n\t-> FAIL (Returned \"enough stock\", \"not enough\" expected)\n");
	}
	
	printf("\nTest 2A1.4: Check stock of non-existing good on non-empty warehouse");
	(*totalTest)++;
	good.id= 90;
	result= checkStockAtOrigin(wh, good, 5);
	if (!result) {
			printf("\n\t-> OK\n");
			(*passedTest)++;
	}
	else {
			printf("\n\t-> FAIL (Returned \"enough stock\" for a non-existing good)\n");
	}
	
	printf("\nTest 2A1.5: Check null-stock of non-existing good on non-empty warehouse");
	(*totalTest)++;
	good.id= 90;
	result= checkStockAtOrigin(wh, good, 0);
	if (result) {
			printf("\n\t-> OK\n");
			(*passedTest)++;
	}
	else {
			printf("\n\t-> FAIL (Returned \"not enough stock\" when asked for a quantity of 0)\n");
	}
}

void test_search_train(int *totalTest, int *passedTest)
{
    tTrainStack mainPlatform, siding;
    tTrainTable table;
    tTrain train1, train2;
    tGood good1, good2, good3, good4;
 	char str[MAX_LINE];
    tBoolean result;
    tError retVal;

    /* Initialize structures */
    trainsTable_init(&table);
    mainPlatform= trainStack_create();
    siding= trainStack_create();

    /* Load goods */
    getGoodObject(GOOD1,&good1); /* Volume = 0.6 m3 per unit */
    getGoodObject(GOOD2,&good2); /* Volume = 0.4 m3 per unit */
    getGoodObject(GOOD3,&good3); /* Volume = 2.0 m3 per unit */
    getGoodObject(GOOD4,&good4); /* Volume = 2.0 m3 per unit */

    /* Load trains */
    getTrainObject(TRAIN1, &train1); /* Capacity = 5 wagons x 200.0 = 1000.0 m3 */
    getTrainObject(TRAIN2, &train2); /* Capacity = 8 wagons x 150.0 = 1200.0 m3 */
    trainsTable_add(&table,train1,&retVal); 
    trainsTable_add(&table,train2,&retVal); 

	printf("=======================================\n");
	printf(" SUITABLE TRAIN SEARCH (Exercise 2A.2) \n");
	printf("=======================================\n");
    
	printf("\nTest 2A2.1: Search train on empty main-platform and empty siding");
	(*totalTest)++;
	result= searchTrainAtOrigin(table,&mainPlatform,&siding,good1,1);
	if (!result) {
			printf("\n\t-> OK\n");
			(*passedTest)++;
	}
	else {
			printf("\n\t-> FAIL (Train found on an empty station)\n");
	}
        
    /* train1 at top and train2 at bottom of main platform; siding empty */
    getStackObject(PLATFORM_STACK1,&mainPlatform);
    getStackObject(PLATFORM_STACK2,&siding);
    
	printf("\nTest 2A2.2: Search train: Success at first attempt (stack remains the same)");
	(*totalTest)++;
	result= searchTrainAtOrigin(table,&mainPlatform,&siding,good3,450);
	if (result) {
            getStackStr(mainPlatform,MAX_LINE,str);
            if (strcmp(PLATFORM_STACK1,str)==0) {
                printf("\n\t-> OK\n");
                (*passedTest)++;                
            }
            else
                printf("\n\t-> FAIL (Train stack changed)\n");
	}
	else {
			printf("\n\t-> FAIL (Train not found)\n");
	}

    getStackObject(PLATFORM_STACK1,&mainPlatform);
    getStackObject(PLATFORM_STACK2,&siding);

	printf("\nTest 2A2.3: Search train: Success at second attempt");
	(*totalTest)++;
	result= searchTrainAtOrigin(table,&mainPlatform,&siding,good3,550);
	if (result) {
            result= (trainStack_size(mainPlatform) == 1 && 
                     trainStack_size(siding) == 1 &&
                     trainStack_top(mainPlatform).id == 11 &&
                     trainStack_top(siding).id == 10);
            if (result) {
                printf("\n\t-> OK\n");
                (*passedTest)++;                
            }
            else
                printf("\n\t-> FAIL (Train stack configuration different than expected)\n");
	}
	else {
			printf("\n\t-> FAIL (Train not found)\n");
	}

    getStackObject(PLATFORM_STACK1,&mainPlatform);
    getStackObject(PLATFORM_STACK2,&siding);

	printf("\nTest 2A2.4: Search train: No success (stack remains the same)");
	(*totalTest)++;
	result= searchTrainAtOrigin(table,&mainPlatform,&siding,good3,650);
	if (!result) {
            getStackStr(mainPlatform,MAX_LINE,str);
            if (strcmp(PLATFORM_STACK1,str)==0) {
                printf("\n\t-> OK\n");
                (*passedTest)++;                
            }
            else
                printf("\n\t-> FAIL (Train stack changed)\n");
	}
	else {
			printf("\n\t-> FAIL (Train not found)\n");
	}
    
    getStackObject(PLATFORM_STACK1,&siding);
    getStackObject(PLATFORM_STACK2,&mainPlatform);

	printf("\nTest 2A2.5: Search train: No success (siding moves to main platform)");
	(*totalTest)++;
	result= searchTrainAtOrigin(table,&mainPlatform,&siding,good3,700);
	if (!result) {
            result= (trainStack_size(mainPlatform) == 2 && 
                     trainStack_size(siding) == 0 &&
                     trainStack_top(mainPlatform).id == 11);
            if (result) {
                printf("\n\t-> OK\n");
                (*passedTest)++;                
            }
            else
                printf("\n\t-> FAIL (Train stack configuration different than expected)\n");
	}
	else {
			printf("\n\t-> FAIL (Train not found)\n");
	}
    
	printf("\nTest 2A2.6: Search train: Success (empty main platform, suitable train at top of siding)");
	(*totalTest)++;
    getStackObject(PLATFORM_STACK1,&siding);
    getStackObject(PLATFORM_STACK2,&mainPlatform);
	result= searchTrainAtOrigin(table,&mainPlatform,&siding,good3,450);
	if (result) {
            result= (trainStack_size(mainPlatform) == 1 && 
                     trainStack_size(siding) == 1);
            if (result) {
                printf("\n\t-> OK\n");
                (*passedTest)++;                
            }
            else
                printf("\n\t-> FAIL (Train stack configuration different than expected)\n");
	}
	else {
			printf("\n\t-> FAIL (Train not found)\n");
	}
}

void test_load_train(int *totalTest, int *passedTest) 
{
    tTrainStack mainPlatform;
    tBoolean result;
    tWareHouse wh;
    tGood good;
    
    mainPlatform= trainStack_create();
	warehouse_cleanAllStocks(&wh);
	getGoodObject(GOOD1,&good); /* id = 10 */

	printf("=======================================\n");
	printf(" LOADING TRAIN (Exercise 2A.3) \n");
	printf("=======================================\n");
    
	printf("\nTest 2A3.1: Try to load a non-existing train of an empty platform");
	(*totalTest)++;
	loadTrain(&mainPlatform,&wh,good,100);
    result= trainStack_empty(mainPlatform) &&
            warehouse_getStock(good.id,wh) == 0;
	if (result) {
			printf("\n\t-> OK\n");
			(*passedTest)++;
	}
	else {
			printf("\n\t-> FAIL (Loading performed on non-existing train and empty warehouse)\n");
	}

    getWareHouseObject(WAREHOUSE_1,&wh); /* Initial stock for good 10 is 150 */
    getStackObject(PLATFORM_STACK1,&mainPlatform); /* Two trains on main platform */

	printf("\nTest 2A3.2: Try to load a train with existing goods");
	(*totalTest)++;
	loadTrain(&mainPlatform,&wh,good,100);
    result= (trainStack_size(mainPlatform) == 2 &&
             trainStack_top(mainPlatform).load.id == 10 &&
             trainStack_top(mainPlatform).load.qtt == 100 &&
             warehouse_getStock(good.id,wh) == 50);
	if (result) {
        printf("\n\t-> OK\n");
        (*passedTest)++;                
	}
	else {
            printf("\n\t-> FAIL (Train not properly loaded)\n");
	}
}

void test_train_transport(int *totalTest, int *passedTest)  
{
    tTrainStack origin, destination;

    origin= trainStack_create();
    destination= trainStack_create();

	printf("=====================================\n");
	printf(" TRAINS TRANSPORTATION (Exercise 2B) \n");
	printf("=====================================\n");
    
	printf("\nTest 2B.1: Try to load a non-existing train of an empty platform");
	(*totalTest)++;
    moveTrainFromOriginToDestination(&origin, &destination);
    if (trainStack_empty(origin) && 
        trainStack_empty(destination)) {
            printf("\n\t-> OK\n");
            (*passedTest)++;                
    }
    else
    {
            printf("\n\t-> FAIL (Not able to transport goods if no trains at origin)\n");
    }
    
    getStackObject(PLATFORM_STACK1,&origin); /* Two trains on main platform at origin (none at destination) */

	printf("\nTest 2B.2: Try to move goods from an origin platform to a destination platform");
	(*totalTest)++;
    moveTrainFromOriginToDestination(&origin, &destination);
    if (trainStack_size(origin) == 1 && 
        trainStack_size(destination) == 1) {
            printf("\n\t-> OK\n");
            (*passedTest)++;                
    }
    else
    {
            printf("\n\t-> FAIL (Wrong transportation)\n");
    }
    
	printf("\nTest 2B.3: Keep moving goods until origin becomes empty");
	(*totalTest)++;
    moveTrainFromOriginToDestination(&origin, &destination);
    if (trainStack_size(origin) == 0 && 
        trainStack_size(destination) == 2) {
            printf("\n\t-> OK\n");
            (*passedTest)++;                
    }
    else
    {
            printf("\n\t-> FAIL (Wrong transportation)\n");
    }
}

void test_unload_train(int *totalTest, int *passedTest) {
        
    tTrainStack mainPlatform;
    tBoolean result;
    tWareHouse wh;
    tGood good;
    
    mainPlatform= trainStack_create();
	warehouse_cleanAllStocks(&wh);
	getGoodObject(GOOD1,&good); /* id = 10 */

	printf("=======================================\n");
	printf(" UNLOADING TRAIN (Exercise 2C) \n");
	printf("=======================================\n");

	printf("\nTest 2C.1: Try to unload a non-existing train of an empty platform");
	(*totalTest)++;
	unloadTrainAtDestination(&mainPlatform,&wh);
    result= trainStack_empty(mainPlatform) && 
            warehouse_getNumberOfGoods(wh) == 0;
	if (result) {
			printf("\n\t-> OK\n");
			(*passedTest)++;
	}
	else {
			printf("\n\t-> FAIL (Wrong unload process)\n");
	}

    getStackObject(PLATFORM_STACK3,&mainPlatform); 

	printf("\nTest 2C.2: Try to unload an existing train (previously non-existing good)");
	(*totalTest)++;
	unloadTrainAtDestination(&mainPlatform,&wh);
    result= trainStack_size(mainPlatform) == 1 &&
            trainStack_top(mainPlatform).id == 5 &&
            trainStack_top(mainPlatform).load.id == NO_GOOD &&
            trainStack_top(mainPlatform).load.qtt == 0 &&
            warehouse_getStock(15,wh) == 50; 
	if (result) {
			printf("\n\t-> OK\n");
			(*passedTest)++;
	}
	else {
			printf("\n\t-> FAIL (Stocks do not match)\n");
	}

    getStackObject(PLATFORM_STACK4,&mainPlatform);
	getWareHouseObject(WAREHOUSE_1, &wh);

	printf("\nTest 2C.3: Try to unload an existing train (previously existing good)");
	(*totalTest)++;
	unloadTrainAtDestination(&mainPlatform,&wh);
    result= trainStack_size(mainPlatform) == 1 &&
            trainStack_top(mainPlatform).id == 5 &&
            trainStack_top(mainPlatform).load.id == NO_GOOD &&
            trainStack_top(mainPlatform).load.qtt == 0 &&
            warehouse_getStock(10,wh) == 200; 
	if (result) {
			printf("\n\t-> OK\n");
			(*passedTest)++;
	}
	else {
			printf("\n\t-> FAIL (Stocks do not match)\n");
	}
}

