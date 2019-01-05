#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "train.h"

/* The content of the fields of the train structure is written into the string str */
void getTrainStr(tTrain train, int maxSize, char *str) {

    int length;
	
    /* Build the string */	
	length = snprintf(str,maxSize-1,"%d %s %s %d %d %d %.2f %d %.2f %.2f %.2f", 
             (int)train.id, train.brand, train.model, train.year, 
			 (int)train.propulsionType, train.nWagons, 
			 train.wagonCapacity, (int)train.hasLocomotive,
			 train.weight, train.length, train.maxSpeed);
	if (length>0) 
		str[length]='\0';

}

/* The content of the string str is parsed into the fields of the train structure */
void getTrainObject(const char *str, tTrain *train) {

	int aux_id, aux_propulsion, aux_locomotive;
 	
    /* read train data */
    sscanf(str, "%d %s %s %d %d %d %f %d %f %f %f", 
             &aux_id, train->brand, train->model, &train->year, &aux_propulsion, 
			 &train->nWagons, &train->wagonCapacity, &aux_locomotive,
			 &train->weight, &train->length, &train->maxSpeed);

    train->id = (tTrainId)aux_id;
    train->propulsionType = (tPropulsion)aux_propulsion;
	train->hasLocomotive = (tBoolean)aux_locomotive;
}

void train_cpy(tTrain *dst, tTrain src) {

    dst->id = src.id;
    strcpy(dst->brand,src.brand);
	strcpy(dst->model,src.model);
	dst->year = src.year;
	dst->propulsionType = src.propulsionType;
	dst->nWagons = src.nWagons;
	dst->wagonCapacity = src.wagonCapacity;
	dst->hasLocomotive = src.hasLocomotive;
	dst->weight = src.weight;
	dst->length = src.length;
	dst->maxSpeed = src.maxSpeed;
}

int train_cmp(tTrain d1, tTrain d2)
{
    int result = 0;
    
    if ( strcmp(d1.brand,d2.brand)>0 )
		result = 1;
	else if ( strcmp(d1.brand,d2.brand)<0 )
		result = -1;
	else {
		if ( strcmp(d1.model,d2.model)>0 )
			result = 1;
		else if ( strcmp(d1.model,d2.model)<0 )
			result = -1;
		else {
			if (d1.year > d2.year) 
				result = 1;
			else if (d1.year < d2.year)
				result = -1;
			else{
				if (d1.id > d2.id)
					result = 1;
				else if (d1.id < d2.id)
					result = -1;
				else{
					if (d1.propulsionType > d2.propulsionType)
						result = 1;
					else if (d1.propulsionType < d2.propulsionType)
						result = -1;
					else{
						if (d1.nWagons > d2.nWagons)
							result = 1;
						else if (d1.nWagons < d2.nWagons)
							result = -1;
						else{
							if (d1.wagonCapacity > d2.wagonCapacity)
								result = 1;
							else if (d1.wagonCapacity < d2.wagonCapacity)
								result = -1;
							else{
								if (d1.hasLocomotive > d2.hasLocomotive)
									result = 1;
								else if (d1.hasLocomotive < d2.hasLocomotive)
									result = -1;
								else{
									if (d1.weight > d2.weight)
										result = 1;
									else if (d1.weight < d2.weight)
										result = -1;
									else{
										if (d1.length > d2.length)
											result = 1;
										else if (d1.length < d2.length)
											result = -1;
										else{
											if (d1.maxSpeed > d2.maxSpeed)
												result = 1;
											else if (d1.maxSpeed < d2.maxSpeed)
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
    }
    
    return result;
}

void trainsTable_init(tTrainTable *trainsTable) {
	
	trainsTable->nTrains= 0;
}

void trainsTable_add(tTrainTable *tabTrains, tTrain train, tError *retVal) {

	*retVal = OK;

	/* Check if there enough space for the new train */
	if(tabTrains->nTrains>=MAX_TRAINS)
		*retVal = ERR_MEMORY;
		

	if (*retVal == OK) {
		/* Add the new train to the end of the table */
		train_cpy(&tabTrains->table[tabTrains->nTrains],train);
		tabTrains->nTrains++;
	}
	
}

int trainsTable_find(tTrainTable tabTrains, tTrainId id) {

	int idx = NO_TRAIN;
	
	int i=0;
	while(i< tabTrains.nTrains && idx==NO_TRAIN) {
		/* Check if the id is the same */
		if(id==tabTrains.table[i].id)  {
			idx = i;
		}
		i++;
	}
	
	return idx;
}

void trainsTable_save(tTrainTable tabTrains, const char* filename, tError *retVal) {

    *retVal = OK;

	FILE *fout=0;
	int i;
	char str[MAX_LINE];
	
	/* Open the output file */
	if((fout=fopen(filename, "w"))==0) {
		*retVal = ERR_CANNOT_WRITE;
	} else {
	
        /* Save all goods to the file */
        for(i=0;i<tabTrains.nTrains;i++) {
            getTrainStr(tabTrains.table[i], MAX_LINE, str);
            fprintf(fout, "%s\n", str);
        }
            
        /* Close the file */
        fclose(fout);
	}
}

void trainsTable_load(tTrainTable *tabTrains, const char* filename, tError *retVal) {
	
	*retVal = OK;

	FILE *fin=0;
	char line[MAX_LINE];
	tTrain newTrain;
	
	/* Initialize the output table */
	trainsTable_init(tabTrains);
	
	/* Open the input file */
	if((fin=fopen(filename, "r"))!=NULL) {

		/* Read all the trains */
		while(!feof(fin) && tabTrains->nTrains<MAX_TRAINS) {
			/* Remove any content from the line */
			line[0] = '\0';
			/* Read one line (maximum 511 chars) and store it in "line" variable */
			fgets(line, MAX_LINE-1, fin);
			/* Ensure that the string is ended by 0*/
			line[MAX_LINE-1]='\0';
			if(strlen(line)>0) {
				/* Obtain the object */
				getTrainObject(line, &newTrain);
				/* Add the new train to the output table */
				trainsTable_add(tabTrains, newTrain, retVal);		
			}
		}
		/* Close the file */
		fclose(fin);
		
	}else {
		*retVal = ERR_CANNOT_READ;
	}
}

void trainsTable_filterByPropulsion(tTrainTable tabTrains, tPropulsion propulsion, tTrainTable *result) {

	tError retVal;
	int i;
	trainsTable_init(result);
	for(i=0;i<tabTrains.nTrains;i++) {
		if (propulsion == tabTrains.table[i].propulsionType){
			trainsTable_add(result, tabTrains.table[i],&retVal);
		/* retVal will always be OK as the result table will be smaller than tabTrains which cannot have more than MAX_TRAINS*/
		}
	}

}

void trainsTable_getTrainsWithLocomotive(tTrainTable tabTrains, tTrainTable *result) {

	tError retVal;
	int i;
	trainsTable_init(result);
	for(i=0;i<tabTrains.nTrains;i++) {
		if (tabTrains.table[i].hasLocomotive){
			trainsTable_add(result, tabTrains.table[i],&retVal);
		/* retVal will always be OK as the result table will be smaller than tabTrains which cannot have more than MAX_TRAINS*/
		}
	}

}

float trainTable_getAverageCapacityByPropulsion(tTrainTable tabTrain, tPropulsion propulsion) {

	float avgCapacity = 0.00;

	int numTrainProp=0, i;
	float sumCapacity = 0;
	
	for(i=0;i<tabTrain.nTrains;i++) {
		if (tabTrain.table[i].propulsionType==propulsion){
			sumCapacity+= (tabTrain.table[i].wagonCapacity * tabTrain.table[i].nWagons);			
			numTrainProp++;
		}
	}
	if (numTrainProp>0)
		avgCapacity = sumCapacity / (float)numTrainProp;

	
	return avgCapacity;
}

float trainTable_getMaxTrainSpeed(tTrainTable tabTrain){
	float maxSpeed = 0;
	int i;
	
	for(i=0;i<tabTrain.nTrains;i++) {
		if (tabTrain.table[i].maxSpeed > maxSpeed){
			maxSpeed = tabTrain.table[i].maxSpeed;
		}
	}
	return maxSpeed;
}
