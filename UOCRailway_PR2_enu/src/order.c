#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "order.h"

/* The content of the fields of the order structure is written into the string str */
void getOrderStr(tOrder order, int maxSize, char *str) {

    int length;
	  
    /* Build the string */	
	length = snprintf(str,maxSize-1,"%d %c %c %d %d", 
             (int)order.id, order.originCenter, order.destinationCenter, 
             (int)order.goodsOrdered.id, order.goodsOrdered.qtt );
 	if (length>0) 
		str[length]='\0';
}

/* The content of the string str is parsed into the fields of the order structure */
void getOrderObject(const char *str, tOrder *order) {

	int aux_id, aux2_id;
 	
    /* read train data */
    sscanf(str, "%d %c %c %d %d", 
             &aux_id, &order->originCenter, &order->destinationCenter, 
             &aux2_id, &order->goodsOrdered.qtt );

    order->id = (tOrderId)aux_id;
    order->goodsOrdered.id= (tGoodId)aux2_id;
}

void order_cpy(tOrder *dst, tOrder src) {

    dst->id = src.id;
    dst->originCenter= src.originCenter;
    dst->destinationCenter= src.destinationCenter;
    dst->goodsOrdered.id= src.goodsOrdered.id;
    dst->goodsOrdered.qtt= src.goodsOrdered.qtt;
}

int order_cmp(tOrder d1, tOrder d2)
{
    int result = 0;

    if (d1.id > d2.id)
        result = 1;
    else if (d1.id < d2.id)
        result = -1;
    else 
    {
        if (d1.originCenter > d2.originCenter)
            result = 1;
        else if (d1.originCenter < d2.originCenter)
            result = -1;
        else 
        {
            if (d1.destinationCenter > d2.destinationCenter)
                result = 1;
            else if (d1.destinationCenter < d2.destinationCenter)
                result = -1;
            else 
            {
                if (d1.goodsOrdered.id > d2.goodsOrdered.id)
                    result = 1;
                else if (d1.goodsOrdered.id < d2.goodsOrdered.id)
                    result = -1;
                else 
                {
                    if (d1.goodsOrdered.qtt > d2.goodsOrdered.qtt)
                        result = 1;
                    else if (d1.goodsOrdered.qtt > d2.goodsOrdered.qtt)
                        result = -1;
                }                            
            }            
        }
    }
        
    return result;
}

void ordersTable_init(tOrderTable *ordersTable) {
	
	ordersTable->nOrders= 0;
}

void ordersTable_add(tOrderTable *tabOrders, tOrder order, tError *retVal) {

	*retVal = OK;

	/* Check if there enough space for the new order */
	if(tabOrders->nOrders>=MAX_ORDERS)
		*retVal = ERR_MEMORY;
    
	if (*retVal == OK) {
		/* Add the new order to the end of the table */
		order_cpy(&tabOrders->table[tabOrders->nOrders],order);
		tabOrders->nOrders++;
	}
}

int ordersTable_find(tOrderTable tabOrders, tOrderId id) {

	int idx = NO_ORDER;
	
	int i=0;
	while(i< tabOrders.nOrders && idx==NO_ORDER) {
		/* Check if the id is the same */
		if(id==tabOrders.table[i].id)  {
			idx = i;
		}
		i++;
	}
	
	return idx;
}

void ordersTable_clean(tOrderTable *ordersTable)
{
    ordersTable->nOrders= 0;
}

void ordersTable_save(tOrderTable tabOrders, const char* filename, tError *retVal) {

    *retVal = OK;

	FILE *fout=0;
	int i;
	char str[MAX_LINE];
	
	/* Open the output file */
	if((fout=fopen(filename, "w"))==0) {
		*retVal = ERR_CANNOT_WRITE;
	} else {
	
        /* Save all goods to the file */
        for(i=0;i<tabOrders.nOrders;i++) {
            getOrderStr(tabOrders.table[i], MAX_LINE, str);
            fprintf(fout, "%s\n", str);
        }
            
        /* Close the file */
        fclose(fout);
	}
}

void ordersTable_load(tOrderTable *tabOrders, const char* filename, tError *retVal) {
	
	*retVal = OK;

	FILE *fin=0;
	char line[MAX_LINE];
	tOrder newOrder;
	
	/* Initialize the output table */
	ordersTable_init(tabOrders);
	
	/* Open the input file */
	if((fin=fopen(filename, "r"))!=NULL) {

		/* Read all the trains */
		while(!feof(fin) && tabOrders->nOrders<MAX_ORDERS) {
			/* Remove any content from the line */
			line[0] = '\0';
			/* Read one line (maximum 511 chars) and store it in "line" variable */
			fgets(line, MAX_LINE-1, fin);
			/* Ensure that the string is ended by 0*/
			line[MAX_LINE-1]='\0';
			if(strlen(line)>0) {
				/* Obtain the object */
				getOrderObject(line, &newOrder);
				/* Add the new order to the output table */
				ordersTable_add(tabOrders, newOrder, retVal);		
			}
		}
		/* Close the file */
		fclose(fin);
		
	}else {
		*retVal = ERR_CANNOT_READ;
	}
}

