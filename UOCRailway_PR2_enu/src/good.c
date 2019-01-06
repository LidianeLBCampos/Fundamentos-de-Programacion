#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "good.h"

void getGoodStr(tGood good, int maxSize, char *str) {

	int length;
    
    /* Build the string */
	length = snprintf(str,maxSize-1,"%d %s %d %.2f %.2f %.2f %.2f %d %d %d", 
             good.id, good.name, (int)good.type, good.price, good.weight, good.height, 
			 good.volume, good.layers, (int)good.isFragile, (int)good.isDangerous);
	if (length>0) 
		str[length]='\0';
}


void getGoodObject(const char *str, tGood *good) {
	
    int id, type, isFragile, isDangerous;

    /* read good data */
	sscanf(str, "%d %s %d %f %f %f %f %d %d %d", &(id), good->name, &type, &(good->price), 
		 &(good->weight), &(good->height), &(good->volume), &(good->layers), &isFragile, &isDangerous);

	good->id = (tGoodId)(id);
	good->type = (tGoodType)(type);
	good->isFragile = (tBoolean)(isFragile);
	good->isDangerous = (tBoolean)(isDangerous);
}

void goodTable_init(tGoodTable *goodTable) {
	
	goodTable->nGoods=0;
}
	
int good_cmp(tGood d1, tGood d2) {
	
	int result = 0;

    if ( strcmp(d1.name,d2.name)>0 )
		result = 1;
	else if ( strcmp(d1.name,d2.name)<0 )
		result = -1;
	else {
		if ( d1.type > d2.type )
			result = 1;
		else if ( d1.type < d2.type )
			result = -1;
		else {
			if (d1.id > d2.id) 
				result = 1;
			else if (d1.id < d2.id)
				result = -1;
			else{
				if (d1.layers > d2.layers)
					result = 1;
				else if (d1.layers < d2.layers)
					result = -1;
				else{
					if (d1.isFragile > d2.isFragile)
						result = 1;
					else if (d1.isFragile < d2.isFragile)
						result = -1;
					else{
						if (d1.isDangerous > d2.isDangerous)
							result = 1;
						else if (d1.isDangerous < d2.isDangerous)
							result = -1;
						else{
							if (d1.price > d2.price)
								result = 1;
							else if (d1.price < d2.price)
								result = -1;
							else{
								if (d1.weight > d2.weight)
									result = 1;
								else if (d1.weight < d2.weight)
									result = -1;
								else{
									if (d1.height > d2.height)
										result = 1;
									else if (d1.height < d2.height)
										result = -1;
									else{
										if (d1.volume > d2.volume)
											result = 1;
										else if (d1.volume < d2.volume)
											result = -1;
									}
								}
							}
						}
					}
				}
			}
		}
    }

    return result;
}

void good_cpy(tGood *dst, tGood src) {

	dst->id = src.id; 
    strcpy(dst->name,src.name);
    dst->type= src.type;
    dst->price= src.price;
    dst->weight = src.weight;
	dst->height = src.height;
	dst->volume = src.volume;
	dst->layers = src.layers;
	dst->isFragile = src.isFragile;
	dst->isDangerous = src.isDangerous;
}

void goodTable_add(tGoodTable *tabGood, tGood good, tError *retVal) {

	*retVal = OK;

	/* Check if there enough space for the new good */
	if(tabGood->nGoods>=MAX_GOODS)
		*retVal = ERR_MEMORY;

	if (*retVal == OK) {
		/* Add the new good to the end of the table */
		good_cpy(&tabGood->table[tabGood->nGoods],good);
		tabGood->nGoods++;
	}

}

int goodTable_find(tGoodTable tabGood, tGoodId id) {

	int idx = NO_GOOD;
	
	int i=0;
	while(i< tabGood.nGoods && idx==NO_GOOD) {
		/* Check if the id is the same */
		if(tabGood.table[i].id==id) {
			idx = i;
		}
		i++;
	}
	
	return idx;
}

tGood goodTable_get(tGoodTable tabGood, tGoodId id)
{
    tGood good;
    
	int i=0;
    good.id= NO_GOOD;
	
	while(i< tabGood.nGoods && good.id==NO_GOOD) {
		/* Check if the id is the same */
		if(tabGood.table[i].id==id) {
			good_cpy(&good, tabGood.table[i]);
		}
		i++;
	}
	
	return good;
}

tGood goodTable_goodAt(tGoodTable tabGood, int index)
{
	tGood good;

	good.id= NO_GOOD;

	if (index >= 0 && index < tabGood.nGoods) {
		good_cpy(&good, tabGood.table[index]);
	}
		
	return good;
}

void goodTable_del(tGoodTable *tabGood, tGood good) {
	
	int i;
    int pos;

	pos = goodTable_find(*tabGood,good.id);
	if (pos!=NO_GOOD){
	/* If the good is found, all the rest of the elements are displaced one position */
		for(i=pos; i<tabGood->nGoods-1; i++) {		
			good_cpy(&tabGood->table[i],tabGood->table[i+1]);
		}
		tabGood->nGoods=tabGood->nGoods-1;		
	}
}

void goodTable_save(tGoodTable tabGood, const char* filename, tError *retVal) {

	*retVal = OK;
	
	FILE *fout=0;
	int i;
	char str[MAX_LINE];
	
	/* Open the output file */
	if((fout=fopen(filename, "w"))==0) {
		*retVal = ERR_CANNOT_WRITE;
	} else {
	
        /* Save all goods to the file */
        for(i=0;i<tabGood.nGoods;i++) {
            getGoodStr(tabGood.table[i], MAX_LINE, str);
            fprintf(fout, "%s\n", str);
        }
            
        /* Close the file */
        fclose(fout);
	}
}

void goodTable_load(tGoodTable *tabGood, const char* filename, tError *retVal) {
	
	*retVal = OK;
	
	FILE *fin=0;
	char line[MAX_LINE];
	tGood newGood;
	
	/* Initialize the output table */
	goodTable_init(tabGood);
	
	/* Open the input file */
	if((fin=fopen(filename, "r"))!=NULL) {

		/* Read all the lines */
		while(!feof(fin) && tabGood->nGoods<MAX_GOODS) {
			/* Remove any content from the line */
			line[0] = '\0';
			/* Read one line (maximum 511 chars) and store it in "line" variable */
			fgets(line, MAX_LINE-1, fin);
			/* Ensure that the string is ended by 0*/
			line[MAX_LINE-1]='\0';
			if(strlen(line)>0) {
				/* Obtain the object */
				getGoodObject(line, &newGood);
				/* Add the new good to the output table */
				goodTable_add(tabGood, newGood, retVal);		
			}
		}
		/* Close the file */
		fclose(fin);
		
	}else {
		*retVal = ERR_CANNOT_READ;
	}
}

void goodTable_filterByType(tGoodTable tabGood, tGoodType goodType, tGoodTable *result) {

	tError retVal;
	int i;
	goodTable_init(result);
	for(i=0;i<tabGood.nGoods;i++) {
		if (goodType == tabGood.table[i].type){
			goodTable_add(result, tabGood.table[i], &retVal);
			/* retVal will always be OK as the result table will be smaller than tabGood which cannot have more than MAX_GOODS*/
		}
	}
}

void goodTable_filterByWeightInterval(tGoodTable tabGood, float minWeight, float maxWeight, tGoodTable *result){

	tError retVal;
	int i;
	goodTable_init(result);

	for(i=0;i<tabGood.nGoods;i++) {
		if (tabGood.table[i].weight >= minWeight && 
			tabGood.table[i].weight <= maxWeight) {
			goodTable_add(result, tabGood.table[i], &retVal);
			/* retVal will always be OK as the result table will be smaller than tabGood which cannot have more than MAX_GOODS*/
		}
	}
}

int goodTable_getNumberOfFragileGoods(tGoodTable tabGood) {

	int numGoods = 0;

	int i;
	for(i=0;i<tabGood.nGoods;i++) {
		if (tabGood.table[i].isFragile){
			numGoods++;
		}
	}
	return numGoods;
}

float goodTable_getMaxGoodHeight(tGoodTable tabGood){

	float maxHeight = 0;

	int i;
	float height;

	for(i=0;i<tabGood.nGoods;i++) {
		height= (1+tabGood.table[i].layers) * tabGood.table[i].height;
		if (height > maxHeight)
			maxHeight= height;
	}

	return maxHeight;
}

