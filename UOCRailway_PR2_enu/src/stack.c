#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "train.h"

tTrainStack trainStack_create() {
	tTrainStack stack;
    stack.nElem=0;
  	return stack;
}

void trainStack_push(tTrainStack *s, tLoadedTrain t)
{
   if(s->nElem == MAX_TRAINS_IN_STACK) {
      printf("\n Full stack \n");
   }else {
      s->table[s->nElem] = t;
      s->nElem++;
   }
}
    
void trainStack_pop(tTrainStack *s)
{
    int i;
    if(s->nElem == 0) {
        printf("\n Empty Stack \n");
    } else {
        s->nElem--;
    }
}

tLoadedTrain trainStack_top(tTrainStack s)
{
    tLoadedTrain t;
	
	loaded_train_init(&t);
	if(s.nElem == 0) {
        printf("\n Empty Stack \n");
    } else {
        t = s.table[s.nElem-1];
    }
	
    return t;
}

tBoolean trainStack_empty(tTrainStack s)
{
    tBoolean result= TRUE;
    
   if(s.nElem!=0){
    result = FALSE;
   }
    
    return result;
}

tBoolean trainStack_full(tTrainStack s)
{
    tBoolean result= FALSE;
    
    if(s.nElem == MAX_TRAINS_IN_STACK){
        result = TRUE;
    }
    return result;
}

void trainStack_invert(tTrainStack *stack)
{
	if(stack->nElem==0){
		 printf("\n Empty Stack \n");
	} else {
		 tTrainStack *tmp; 
		 *tmp = trainStack_create();
	
	while (stack->nElem>0) {
        tmp->table[tmp->nElem] = stack->table[stack->nElem - 1];
        stack->nElem--;
        tmp->nElem++;
    }
    return tmp;
	}
}

void trainStack_clean(tTrainStack *s)
{
    s->nElem= 0;
}

int trainStack_size(tTrainStack s)
{
    return s.nElem;
}

tBoolean trainStack_contains(tTrainStack s, tLoadedTrain e)
{
    tBoolean found;
    int i;

    i= 0;
    found= FALSE;
    while (i < s.nElem && !found) {
        found= (loaded_train_cmp(s.table[i],e) == 0);
        i++;
    }
    
    return found;
}

void trainStack_save(tTrainStack stack, const char* filename, tError *retVal)
{

*retVal = OK;

    FILE *fout=0;
    int i;
    char str[MAX_LINE];
    
    /* Open the output file */
    if((fout=fopen(filename, "w"))==0) {
        *retVal = ERR_CANNOT_WRITE;
    } else {
       
        for(i=0;i<stack.nElem;i++) {
            getStackStr(stack, MAX_LINE, str);
            fprintf(fout, "%s\n", str);
        }
             /* Close the file */
        fclose(fout);
    }

}

void trainStack_load(tTrainStack *stack, const char* filename, tError *retVal)
{
	*retVal = OK;

    FILE *fin=0;
    char line[MAX_LINE];
    tLoadedTrain newTrain;
	tTrainStack *newStack;
	/* Initialize the output stack */
    trainStack_create();
    
    /* Open the input file */
    if((fin=fopen(filename, "r"))!=NULL) {

        /* Read all the trains */
        while(!feof(fin) && stack->nElem<MAX_TRAINS_IN_STACK) {
            /* Remove any content from the line */
            line[0] = '\0';
            /* Read one line (maximum 511 chars) and store it in "line" variable */
            fgets(line, MAX_LINE-1, fin);
            /* Ensure that the string is ended by 0*/
            line[MAX_LINE-1]='\0';
            if(strlen(line)>0) {
                /* Obtain the object */
                getStackObject(line, stack);
                /* Add the new stack to the output table */
                trainStack_push(newStack, newTrain);       
            }
        }
        /* Close the file */
        fclose(fin);
        
    }else {
        *retVal = ERR_CANNOT_READ;
    }  
}

/* The content of the fields of the stack structure is written into the string str */
void getStackStr( tTrainStack stack, int maxSize, char *str) {

    int length;
	tLoadedTrain loadedTrain;
    char tempStr[MAX_LINE];    
    
    /* invert to allow writting from bottom to top */
    trainStack_invert(&stack);

    /* write the size of the stack */
    length= snprintf(str, maxSize-1, "%d", trainStack_size(stack));
 	if (length>0) 
		str[length]='\0';
    
    while(!trainStack_empty(stack))
    {
        /* copy str into an auxiliar copy of it */
        strcpy(tempStr,str);

        /* get the top of the stack */
        loadedTrain = trainStack_top(stack);
        
        /* write it as a string */
        length= snprintf(str, maxSize-1, "%s %d %d %d", tempStr, 
                loadedTrain.id, loadedTrain.load.id, loadedTrain.load.qtt);
        if (length>0) 
            str[length]='\0';
            
        /* pop the top element to allow writting of next element */
        trainStack_pop(&stack);
    }

 	if (length>0) 
		str[length]='\0';
}

/* The content of the string str is parsed into the fields of the stack structure */
void getStackObject(const char *str, tTrainStack *stack) {

	int i, size, aux_train_id, aux_good_id;
    char tempStr[MAX_LINE];   
    char nextStr[MAX_LINE];   
	tLoadedTrain newTrain;

    /* read stack size */
    sscanf(str, "%d %[^\n]s", &size, tempStr); 
    
    /* Initialize the stack */
    *stack = trainStack_create();
        
    for (i= 0; i< size; i++)
    {
        /* read the loaded train as a string*/
        sscanf(tempStr, "%d %d %d %[^\n]s", &aux_train_id, &aux_good_id, &(newTrain.load.qtt), nextStr); 
        newTrain.id= (tTrainId)(aux_train_id);
        newTrain.load.id= (tGoodId)(aux_good_id);
        
        /* push it on the top of the stack */
        trainStack_push( stack, newTrain );
     
        /* prepare next iteration */
        strcpy(tempStr,nextStr);   
    }
}
