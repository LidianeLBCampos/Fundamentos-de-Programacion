#include <stdio.h>
#include <string.h>
#include <math.h>
#include "test.h"
#include "good.h"

#define GOOD1 "10 FLOUR 0 0.25 25.00 0.50 0.60 3 0 0"
#define GOOD2 "11 SOLVENT 1 5.00 20.00 0.40 0.40 2 0 1"
#define GOOD3 "05 BOVINE 2 10.50 200.00 0.80 2.00 0 0 0"
#define GOOD4 "15 MOTORBIKE 3 30.00 250.00 1.00 2.00 0 1 0"
#define GOOD5 "16 ACID 1 3.00 15.00 0.40 1.00 3 0 1"
#define GOOD6 "06 POULTRY 2 2.50 30.00 0.20 0.50 0 0 0"

void runTests() {	
	int passedTestPR1, passedTestPR2=0;
	int totalTestPR1, totalTestPR2=0;
	
	printf("=================================================\n");
	printf("====       PRACTICAL ACTIVITY 1 TESTS        ====\n");
	printf("=================================================\n");	
	runTestsPR1(&totalTestPR1, &passedTestPR1);

	printf("===================================\n");
	printf("====       TEST SUMMARY        ====\n");
	printf("===================================\n");		
	printf("\tPR1: Passed %d of %d [%0.2f%%]\n", passedTestPR1, totalTestPR1, (float)passedTestPR1/totalTestPR1*100.0);
	printf("\n\tTotal: Passed %d of %d [%0.2f%%]\n", passedTestPR1+passedTestPR2, totalTestPR1+totalTestPR2, (float)(passedTestPR1+passedTestPR2)/(totalTestPR1+totalTestPR2)*100.0);
	printf("===================================\n");		
}

void runTestsPR1(int *totalTest, int *passedTest) {
	*totalTest=0;
	*passedTest=0;
	
	test_serialization(totalTest, passedTest);
	test_cpycmp(totalTest, passedTest);
	test_persistence(totalTest, passedTest);
	test_search(totalTest, passedTest);
	test_count(totalTest, passedTest);
}

void test_serialization(int *totalTest, int *passedTest) {	

	tGood d1, d2;
    char str[MAX_LINE];
		
	printf("=================================================\n");
	printf(" GOODS SERIALIZATION (Exercise 3)\n");
	printf("=================================================\n");

	printf("\nTest 3.1: Serialitzation");
	(*totalTest)++;
	printf("\n\t->You have to uncomment lines in test_serialization (test.c) in order to pass this test");
/* Uncomment to test
 * 
	d1.id = 10;
    strcpy(d1.name,"FLOUR");
	d1.type = FOOD;
	d1.price = 0.25;
	d1.weight = 25.0;
	d1.height = 0.5;
	d1.volume = 0.6;
	d1.layers = 3;
	d1.isFragile = FALSE;
	d1.isDangerous = FALSE;
    getGoodStr(d1,MAX_LINE,str);
	
    if (strcmp(GOOD1,str)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
*/
	printf("\nTest 3.2: Desserialitzation");
	(*totalTest)++;
	printf("\n\t->You have to uncomment lines in test_serialization (test.c) in order to pass this test");
/* Uncomment to test
 * 
	getGoodObject(GOOD1, &d2);
    if (d1.id==d2.id && strcmp(d1.name,d2.name)==0 && 
		d1.type==d2.type && d1.price==d2.price && d1.weight==d2.weight && d1.height==d2.height &&
		d1.volume==d2.volume && d1.layers==d2.layers && d1.isFragile==d2.isFragile && d1.isDangerous==d2.isDangerous) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
*/
	printf("\nTest 3.3: Equal serialization string after conversion to object");
	(*totalTest)++;
	getGoodObject(GOOD1, &d1);
    getGoodStr(d1,MAX_LINE,str);
    getGoodObject(str,&d2);
    if (strcmp(GOOD1,str)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
    
	printf("\nTest 3.4: Equal serialization object after conversion to string - Comparison");
	(*totalTest)++;
    if (good_cmp(d1, d2)==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;        
	} else {
		printf("\n\t-> FAIL\n");
	}
}	

void test_cpycmp(int *totalTest, int *passedTest) {	

	tGood d1, d2;
    char str[MAX_LINE];
		
	printf("=================================================\n");
	printf(" GOODS COPY AND COMPARE (Exercise 4)\n");
	printf("=================================================\n");
	
	printf("\nTest 4.1: Copy (check by string comparison)");
	(*totalTest)++;
	getGoodObject(GOOD1, &d1);
    d2.id= 0;
	good_cpy(&d2,d1);
    getGoodStr(d2,MAX_LINE,str);
    if (strcmp(GOOD1,str)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 4.2: Compare equal goods");
	(*totalTest)++;
    if (good_cmp(d1,d1)==0){
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
	
	printf("\nTest 4.3: Comparison, second good greater than first");
	(*totalTest)++;
	getGoodObject(GOOD2, &d2);
    if (good_cmp(d2,d1)>0){
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 4.4: Comparison, first good lower than second");
	(*totalTest)++;
    if (good_cmp(d1,d2)<0){
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
    
	printf("\nTest 4.5: Copy (check by structure comparison)");
	(*totalTest)++;
	good_cpy(&d2,d1);
    if (good_cmp(d1,d2)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}    
}	

void test_persistence(int *totalTest, int *passedTest) {
	tGoodTable goods;
	tGood p1, p2;
	tError retVal;
	
	printf("=================================================\n");
	printf(" PERSISTENCE OF GOODS (Exercise 5)\n");
	printf("=================================================\n");
	
	printf("\nTest 5.1: Save and load no data");
	(*totalTest)++;
	goodTable_init(&goods);	
	
	goodTable_save(goods, "./testGoods.csv",&retVal);
	goodTable_init(&goods);		
	goodTable_load(&goods, "./testGoods.csv",&retVal);
	
	if(retVal==OK){
		if(goods.nGoods==0) {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		} else {
			printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, goods.nGoods);
		}
	} else {
		printf("\n\t-> FAIL (problem in file reading/writing)\n");
	}
		
	printf("\nTest 5.2: Save and load goods");
	(*totalTest)++;
	getGoodObject(GOOD1, &p1);
	getGoodObject(GOOD2, &p2);
    goodTable_add(&goods,p1,&retVal);
    goodTable_add(&goods,p2,&retVal);
	goodTable_save(goods, "./testGoods.csv",&retVal);
	goodTable_init(&goods);		
	goodTable_load(&goods, "./testGoods.csv",&retVal);
	
	if(retVal==OK){
		if(goods.nGoods==2) {
			if(good_cmp(goods.table[0], p1) != 0 || 
			   good_cmp(goods.table[1], p2) != 0) {
				printf("\n\t-> FAIL (Values are not correct)\n");
			} else {
				printf("\n\t-> OK\n");
				(*passedTest)++;
			}
		} else {
			printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, goods.nGoods);
		}
	} else {
		printf("\n\t-> FAIL (problem in file reading/writing)\n");
	}
}

void test_search(int *totalTest, int *passedTest) {	
	tGoodTable goods, result;
	tGood good1, good2, good3, good4, good5, good6;	
	tError retVal;
		
	printf("=================================================\n");
	printf(" GOOD TABLE FILTER (Exercise 6)\n");
	printf("=================================================\n");
	
	printf("\nTest 6.1: Goods of a type in empty table");
	(*totalTest)++;
	goodTable_init(&goods);	
	goodTable_init(&result);		
	goodTable_filterByType(goods, 0, &result);
	if(result.nGoods==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.nGoods);
	}

	getGoodObject(GOOD1, &good1);
	getGoodObject(GOOD2, &good2);
    getGoodObject(GOOD3, &good3);
    getGoodObject(GOOD4, &good4);
    getGoodObject(GOOD5, &good5);
    getGoodObject(GOOD6, &good6);
    goodTable_add(&goods,good1,&retVal);
    goodTable_add(&goods,good2,&retVal);
    goodTable_add(&goods,good3,&retVal);
    goodTable_add(&goods,good4,&retVal);
    goodTable_add(&goods,good5,&retVal);	
    goodTable_add(&goods,good6,&retVal);	
	
	printf("\nTest 6.2: Goods of a non existent type in non empty table");
	(*totalTest)++;	
	goodTable_filterByType(goods, 4, &result);
	if(result.nGoods==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.nGoods);
	}

	printf("\nTest 6.3: Goods of an existent type in non empty table");
	(*totalTest)++;	
	goodTable_filterByType(goods, 1, &result);
	if(result.nGoods==2) {
		if((good_cmp(result.table[0], good2)!=0) ||
           (good_cmp(result.table[1], good5)!=0))  {
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, result.nGoods);
	}

	printf("\nTest 6.4: Goods of a weight in empty table");
	(*totalTest)++;
	goodTable_init(&goods);	
	goodTable_filterByWeightInterval(goods, 0.0, 100.0, &result);
	if(result.nGoods==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.nGoods);
	}
	
	printf("\nTest 6.5: Goods of a weight in a non empty table: null interval");
	(*totalTest)++;
    goodTable_add(&goods,good1,&retVal);
    goodTable_add(&goods,good2,&retVal);
    goodTable_add(&goods,good3,&retVal);
    goodTable_add(&goods,good4,&retVal);
    goodTable_add(&goods,good5,&retVal);
    goodTable_add(&goods,good6,&retVal);
	goodTable_filterByWeightInterval(goods, 100.0, 0.0, &result);
	if(result.nGoods==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.nGoods);
	}
	
	printf("\nTest 6.6: Goods of a weight in a non empty table: interval includes some goods");
	(*totalTest)++;
	goodTable_filterByWeightInterval(goods, 0.0, 100.0, &result);
	if(result.nGoods==4) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 4, result.nGoods);
	}
	
	printf("\nTest 6.7: Goods of a weight in a non empty table: interval includes all goods");
	(*totalTest)++;
	goodTable_filterByWeightInterval(goods, 0.0, 250.0, &result);
	if(result.nGoods==6) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 6, result.nGoods);
	}
}
	
void test_count(int *totalTest, int *passedTest) {

    tAppData appData;
    tGood good1, good2, good3, good4, good5, good6;
	int count;
	float max;
	tError retVal;
   
    appData_init(&appData);

	printf("=================================================\n");
	printf(" GOODS STATISTICS (Exercise 7)\n");
	printf("=================================================\n");
	
	printf("\nTest 7.1: Number of fragile goods in empty table");
	(*totalTest)++;
	count= goodTable_getNumberOfFragileGoods(appData.goods);
	if (count==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers found. Expected %d and returned %d)\n", 0, count);
	}
	
	printf("\nTest 7.2: Number of fragile goods in non empty table (without hits)");
	(*totalTest)++;
	getGoodObject(GOOD1, &good1);
	getGoodObject(GOOD2, &good2);
    getGoodObject(GOOD3, &good3);
	addGood(&appData,good1,&retVal);
	addGood(&appData,good2,&retVal);
	addGood(&appData,good3,&retVal);
	count= goodTable_getNumberOfFragileGoods(appData.goods);
	if (count==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers found. Expected %d and returned %d)\n", 0, count);
	}
	
	printf("\nTest 7.3: Number of fragile goods in non empty table (with hits)");
	(*totalTest)++;
	getGoodObject(GOOD4, &good4);
    getGoodObject(GOOD5, &good5);
    getGoodObject(GOOD6, &good6);
	addGood(&appData,good4,&retVal);
	addGood(&appData,good5,&retVal);
	addGood(&appData,good6,&retVal);
	count= goodTable_getNumberOfFragileGoods(appData.goods);
	if (count==1) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers found. Expected %d and returned %d)\n", 1, count);
	}
		
	appData_init(&appData);

	printf("\nTest 7.4: Maximum height for a good in empty table:");
	(*totalTest)++;
	max = goodTable_getMaxGoodHeight(appData.goods);
	if(max==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected height. Expected %.2f and returned %.2f)\n", 0.0, max);
	}

    addGood(&appData,good4,&retVal);
	
	printf("\nTest 7.5: Maximum height for a good - case 1 good:");
	(*totalTest)++;
	max = goodTable_getMaxGoodHeight(appData.goods);
	if(max==1.0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected height. Expected %.2f and returned %.2f)\n", 1.0, max);
	}

    addGood(&appData,good1,&retVal);
	
	printf("\nTest 7.6: Maximum height for a good - case 2 goods in descending order:");
	(*totalTest)++;
	max = goodTable_getMaxGoodHeight(appData.goods);
	if(max==2.0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected height. Expected %.2f and returned %.2f)\n", 2.0, max);
	}   

	appData_init(&appData);
    addGood(&appData,good1,&retVal);
    addGood(&appData,good4,&retVal);
	
	printf("\nTest 7.7: Maximum height for a good - case 2 goods in ascending order:");
	(*totalTest)++;
	max = goodTable_getMaxGoodHeight(appData.goods);
	if(max==2.0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of goods. Expected %.2f and returned %.2f)\n", 2.0, max);
	}  
}
	