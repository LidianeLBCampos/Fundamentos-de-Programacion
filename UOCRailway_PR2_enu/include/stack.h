#include "data.h"

/* Creates the stack */
tTrainStack trainStack_create(void);

/* Push an element on the top of the stack */
void trainStack_push(tTrainStack *s, tLoadedTrain e);

/* Pops an element from the top of the stack */
void trainStack_pop(tTrainStack *s);

/* Returns the element on top of the stack */
tLoadedTrain trainStack_top(tTrainStack s);

/* Says if the stack is empty */
tBoolean trainStack_empty(tTrainStack s);

/* Says if the stack is full */
tBoolean trainStack_full(tTrainStack s);

/* Inverts a stack (puts bottom on top and top on bottom) */
void trainStack_invert(tTrainStack *s);

/* Cleans a stack (pops all elements) */
void trainStack_clean(tTrainStack *s);

/* Returns the size (i.e. the number of elements) of the stack */
int trainStack_size(tTrainStack s);

/* Says if the given loaded train is in the stack (on top or in any other position) */
tBoolean trainStack_contains(tTrainStack s, tLoadedTrain e);

/* Saves the stack on file */
void trainStack_save(tTrainStack  stack, const char* filename, tError *retVal);

/* Loads the stack from file */
void trainStack_load(tTrainStack *stack, const char* filename, tError *retVal);

/* Gets the stack as a textual representation (string) */
void getStackStr( tTrainStack stack, int maxSize, char *str);

/* Gets the stack object out of its textual representation (string) */
void getStackObject(const char *str, tTrainStack *stack);
