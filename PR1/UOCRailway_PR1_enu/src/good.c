#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "good.h"

void getGoodStr(tGood good, int maxSize, char *str) {

 int length;
	
    /* Build the string */	
	length = snprintf(str,maxSize-1,"%d %s %d %.2f %.2f %.2f %.2f %d %d %d", 
             (int)good.id, good.name,(int)good.type, good.price, 
			 good.weight, good.height, good.volume, (int)good.maxLayers,
			 (int)good.isFragile, (int)good.isDangerous);
	if (length>0) 
		str[length]='\0';
}


void getGoodObject(const char *str, tGood *good) {
	
int aux_id, aux_type, aux_isFragile, aux_isDangerous;
 	
    /* read good data */
    sscanf(str, "%d %s %d %f %f %f %f %d %d %d", 
             &aux_id, good->name, &aux_type, 
			 &good->price, &good->weight, &good->height,
			 &good->volume, &good->maxLayers, &aux_isFragile, &aux_isDangerous);

    good->id = (tGoodId)aux_id;
    good->type = (tGoodType)aux_type;
	good->isFragile = (tBoolean)aux_isFragile;
	good->isDangerous = (tBoolean) aux_isDangerous;
}

void goodTable_init(tGoodTable *goodTable) {
	
	goodTable->nGoods=0;
}
 /* make a comparison between two goods */
int good_cmp(tGood d1, tGood d2) {
	
	int result = 0;

	if(strcmp(d1.name, d2.name)>0)
		result = 1;
	else if (strcmp(d1.name, d2.name) < 0)
		result= -1;
	else{
		if(d1.type > d2.type)
			result = 1;
		else if(d1.type < d2.type)
			result = -1;
		else{
			if(d1.id > d2.id)
				result = 1;
			else if (d1.id < d2.id)
				result = -1;
			else{
				if(d1.maxLayers > d2.maxLayers)
					result = 1;
				else if (d1.maxLayers < d2.maxLayers)
					result = -1;
				else{
					if(d1.isFragile > d2.isFragile)
						result = 1;
					else if(d1.isFragile < d2.isFragile)
						result= -1;
					else {
						if(d1.isDangerous > d2.isDangerous)
							result = 1;
						else if(d1.isDangerous < d2.isDangerous)
							result = -1;
						else {
							if(d1.price > d2.price)
								result = 1;
							else if(d1.price < d2.price)
								result = -1;
							else {
								if(d1.weight > d2.weight)
									result = 1;
								else if(d1.weight > d2.weight)
									result = -1;
								else {
									if(d1.height > d2.height)
										result = 1;
									else if(d1.height < d2.height)
										result = -1;
									else {
										if(d1.volume > d2.volume)
											result = 1;
										else if (d1.height < d2.height)
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

 /* Make a copy of  one good to another */
void good_cpy(tGood *dst, tGood src) {

	dst->id = src.id;
    strcpy(dst->name,src.name);
	dst->type = src.type;
	dst->weight = src.weight;
	dst->height = src.height;
	dst->volume = src.volume;
	dst->maxLayers= src.maxLayers;
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

		/* Read all the good*/
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
				/* Add the new train to the output table */
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
			goodTable_add(result, tabGood.table[i],&retVal);
		/* retVal will always be OK as the result table will be smaller than tabGood which cannot have more than MAX_GOODS*/
		}
	}
}

void goodTable_filterByWeightInterval(tGoodTable tabGood, float minWeight, float maxWeight, tGoodTable *result){
	tError retVal;
	int i;
	goodTable_init(result);
	for(i=0; i<tabGood.nGoods;i++) {
		if(tabGood.table[i].weight >= minWeight && tabGood.table[i].weight <= maxWeight){
			goodTable_add(result, tabGood.table[i], &retVal);
		}
	}
}

int goodTable_getNumberOfFragileGoods(tGoodTable tabGood) {
	int i;
	int numGoods = 0;
	for(i=0; i<tabGood.nGoods;i++){
		if(tabGood.table[i].isFragile){
			numGoods++;
		}
	}
	return numGoods;
}

 /* Return the max height based on the max layers allowed */
float goodTable_getMaxGoodHeight(tGoodTable tabGood){
	int i;
	float maxHeight = 0;
	for(i=0; i<tabGood.nGoods;i++){
			maxHeight = tabGood.table[i].height * tabGood.table[i].maxLayers;
	}
	return maxHeight;
}

