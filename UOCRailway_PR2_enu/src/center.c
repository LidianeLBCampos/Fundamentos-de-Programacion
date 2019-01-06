#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "center.h"
#include "stack.h"

void getWareHouseStr(tWareHouse wh, int maxSize, char *str)
{
    int i, length;
    char tempStr[MAX_LINE];    

    /* Build the string */	
	length = snprintf(str,maxSize-1,"%d", wh.nGoods );
 	if (length>0) 
		str[length]='\0';
        
    for (i= 0; i<wh.nGoods; i++)
    {
        /* copy str into an auxiliar copy of it */
        strcpy(tempStr,str);
        
        /* write it as a string */
        length= snprintf(str, maxSize-1, "%s %d %d", tempStr, 
                wh.stock[i].id, wh.stock[i].qtt);
        if (length>0) 
            str[length]='\0';
    }
}

void getWareHouseObject(const char *str, tWareHouse *wh)
{
	int i, aux_good_id, aux_qtt;
    char tempStr[MAX_LINE];   
    char nextStr[MAX_LINE];   

    /* read stack size */
    sscanf(str, "%d %[^\n]s", &wh->nGoods, tempStr); 
        
    for (i= 0; i< wh->nGoods; i++)
    {
        /* read the loaded train as a string*/
        sscanf(tempStr, "%d %d %[^\n]s", &aux_good_id, &aux_qtt, nextStr); 
        wh->stock[i].id= (tGoodId)aux_good_id;
        wh->stock[i].qtt= aux_qtt;
     
        /* prepare next iteration */
        strcpy(tempStr,nextStr);   
    }
}

void distributionCenter_load(tDistributionCenter *tabCenters, const char* filename, tError *retVal)
{
	*retVal = OK;

	FILE *fin=0;
	char line[MAX_LINE];
		
	/* Open the input file */
	if((fin=fopen(filename, "r"))!=NULL) {

        /* read distribution center id */
        line[0] = '\0';
        fgets(line, MAX_LINE-1, fin);
        line[MAX_LINE-1]='\0';
        if(strlen(line)>0)
           tabCenters->id= line[0];

        /* read main platform of the distribution center */
        line[0] = '\0';
        fgets(line, MAX_LINE-1, fin);
        line[MAX_LINE-1]='\0';
        if(strlen(line)>0) 
            getStackObject(line,&tabCenters->mainPlatform);

        /* read siding of the distribution center */
        line[0] = '\0';
        fgets(line, MAX_LINE-1, fin);
        line[MAX_LINE-1]='\0';
        if(strlen(line)>0) 
            getStackObject(line,&tabCenters->siding);

        /* read warehouse of the distribution center */
        line[0] = '\0';
        fgets(line, MAX_LINE-1, fin);
        line[MAX_LINE-1]='\0';
        if(strlen(line)>0) 
            getWareHouseObject(line,&tabCenters->wareHouse);
   
        /* Close the file */
        fclose(fin);
		
	}else {
		*retVal = ERR_CANNOT_READ;
	}
}

void distributionCenter_save(tDistributionCenter tabCenters, const char* filename, tError *retVal)
{
    *retVal = OK;

	FILE *fout=0;
	char str[MAX_LINE];
	
	/* Open the output file */
	if((fout=fopen(filename, "w"))==0) {
		*retVal = ERR_CANNOT_WRITE;
	} else {
	
        /* write the id of the distribution center */
        fprintf(fout, "%c\n", tabCenters.id);

        /* write the main platform of the distribution center */
        getStackStr( tabCenters.mainPlatform, MAX_LINE, str);
        fprintf(fout, "%s\n", str);

        /* write the siding of the distribution center */
        getStackStr( tabCenters.siding, MAX_LINE, str);
        fprintf(fout, "%s\n", str);

        /* write the warehouse of the distribution center */
        getWareHouseStr( tabCenters.wareHouse, MAX_LINE, str);
        fprintf(fout, "%s\n", str);
            
        /* Close the file */
        fclose(fout);
	}
}

void distributionCenter_init(tDistributionCenter *center, char id)
{
    center->id= id;
    center->mainPlatform= trainStack_create();
    center->siding= trainStack_create();
    center->wareHouse.nGoods= 0;
}

int warehouse_find( tGoodId id, tWareHouse wh )
{
    tBoolean found;
    int i, idx;
    
    i= 0;
    found= FALSE;
    while (i< wh.nGoods && !found) {
        found= (wh.stock[i].id == id);
        i++;
    }
    
    if (found)
        idx= i-1;
    else 
        idx= NO_GOOD;
    
    return idx;
}

void warehouse_addStock( tGoodId id, tWareHouse *wh, int qtt )
{
    wh->stock[ wh->nGoods ].id= id;
    wh->stock[ wh->nGoods ].qtt= qtt;
    wh->nGoods++;
}

void warehouse_updateStock( tGoodId id, tWareHouse *wh, int qtt )
{
    int i;
    tBoolean found;
    
    i= 0;
    found= FALSE;
    while (i< wh->nGoods && !found) {
        found= (wh->stock[i].id == id);
        i++;
    }
    
    if (found) {
        wh->stock[i-1].qtt += qtt;
        if (wh->stock[i-1].qtt < 0)
            wh->stock[i-1].qtt = 0;        
    }        
}

void warehouse_setStock( tGoodId id, tWareHouse *wh, int qtt )
{
    int i;
    tBoolean found;
    
    i= 0;
    found= FALSE;
    while (i< wh->nGoods && !found) {
        found= (wh->stock[i].id == id);
        i++;
    }
    
    if (found) {
        wh->stock[i-1].qtt= qtt;        
        if (wh->stock[i-1].qtt < 0)
            wh->stock[i-1].qtt = 0;
    }
}

int warehouse_getStock( tGoodId id, tWareHouse wh )
{
    int index, qtt;
    
    index= warehouse_find( id, wh );
    if (index != NO_GOOD)
        qtt= wh.stock[index].qtt;
    else 
        qtt= 0;
   
    return qtt;
}

int warehouse_getNumberOfGoods( tWareHouse wh )
{
    return wh.nGoods;
}

void warehouse_cleanAllStocks( tWareHouse *wh )
{
    wh->nGoods= 0;
}