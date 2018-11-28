#include <stdio.h>

enum  tPropulsion{ ELECTRICAL, CARBON, SOLAR, GASOLINE, DIESEL, MAGNETIC };
const int  MAX_MODEL_LENGTH = 20;

typedef struct {
	int idTrain;
	char model[20] ;
	float locLength;
	float wagonLength;
	int nWagons;
	float spaceBetweenWagons;
	int propulsionType;
	} train;
	
	train train1;
	train train2;
	
	float totalLength1;
	float totalLength2;

int main(int argc, char **argv)
{
		for (int i=0; i<2;i++){
		
		printf("Enter the train id: \n");
        printf("Enter the train model:\n");
		printf("Enter the locomotive’s length:\n");
		printf("Enter the wagon’s Length: \n");
		printf("Enter the number of Wagons:\n");
		printf("Enter the space between the vagons: \n");
		printf("Enter the propulsion type (1-ELECTRICAL, 2-CARBON, 3-	SOLAR, 4-GASOLINE, 5-DIESEL, 6-MAGNETIC ) \n");
		
		
		if (i==0){
			scanf("%d %s %f %f %d %f %d", &train1.idTrain, train1.model, &train1.locLength, &train1.wagonLength, &train1.nWagons, &train1.spaceBetweenWagons, &train1.propulsionType);   
		} else{
			scanf("%d %s %f %f %d %f %d", &train2.idTrain, train2.model, &train2.locLength, &train2.wagonLength, &train2.nWagons, &train2.spaceBetweenWagons, &train2.propulsionType);   
		}
		
	
	}
	
	
		
totalLength1=(float)(train1.locLength+train1.wagonLength+train1.nWagons+(train1.spaceBetweenWagons*train1.nWagons));
totalLength2=(float)(train2.locLength+train2.wagonLength+train2.nWagons+(train2.spaceBetweenWagons*train2.nWagons));
		
		if (train1.locLength >=  train2.locLength) {
			printf("The Train 1 is longer than Train 2\n");
			printf("Id Train: %d \n", train1.idTrain);
			printf( "Model=%s\n", train1.model);
			} else {
				printf("The Train 2 is longer than Train 1");
				printf("Id Train: %d \n", train2.idTrain);
				printf( "Model=%s\n", train2.model);
			
			}
		
	
}
