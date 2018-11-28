#include <stdio.h>

const int  MAX_TRAINS = 10;
const int  MAX_TRAIN_LENGTH = 450;

enum boolean {TRUE,FALSE};
enum  tPropulsion{ ELECTRICAL, CARBON, SOLAR, GASOLINE, DIESEL, MAGNETIC };
enum boolean isOverMaxTrainLength;


int main(int argc, char **argv)
{
	int trainQuantity;
	int overMaxTrainLength[trainQuantity] ;
	int  idTrain[trainQuantity] ;
	int locLength[trainQuantity];
	int propulsionType[trainQuantity];
	float wagonLength[trainQuantity];
	float spaceBetweenVagons[trainQuantity];
	int nWagons[trainQuantity];
	int trainLength[trainQuantity];
	
	printf("==============================\n");
	printf("Enter quantity of trains:\n");
	scanf("%d", &trainQuantity);
	
	while(trainQuantity < 0 || trainQuantity > MAX_TRAINS){
		printf("Enter correct quantity of trains it must be between 1 and 10: ");
		scanf("%d", &trainQuantity);

	}
	
	
	for(int i =0; i < trainQuantity; i++){
	printf("Enter the train id: ");
	scanf( "%d", &idTrain[i]);

	printf("Enter the locomotive’s length ");
 	scanf( "%d", &locLength[i]);
	
	printf("Enter the propulsion type (1-ELECTRICAL, 2-CARBON, 3-SOLAR,  4-GASOLINE, 5-DIESEL, 6-MAGNETIC ) ");
	scanf( "%u", &propulsionType[i]);
	
    printf("Enter the wagon’s Length: ");
	scanf( "%f", &wagonLength[i]);

    printf("Enter the space between the vagons: ");
	scanf( "%f", &spaceBetweenVagons[i]);

    printf("Enter the number of Wagons: ");
    scanf( "%d", &nWagons[i]);
	trainLength[i] = (int)(locLength[i] + wagonLength[i] +(spaceBetweenVagons[i] * 	nWagons[i]) +nWagons[i]);
	
	}
	
	for(int j =0; j < trainQuantity; j++){
		if (trainLength[j] > MAX_TRAIN_LENGTH){
				overMaxTrainLength[j] = 1;
		} else {
			overMaxTrainLength[j] = 0;
			
		}
	}
	
	for(int k=0; k< trainQuantity; k++){
		printf("Train id: ");
		printf("%d\n", idTrain[k]);

		printf("The locomotive’s length ");
		printf("%d\n",locLength[k]);
	
		printf("The propulsion type (1-ELECTRICAL, 2-CARBON, 3-SOLAR,  4-GASOLINE, 5-DIESEL, 6-MAGNETIC ) ");
		printf("%u\n",propulsionType[k]);
	
        printf("The wagon’s Length: ");
        printf("%f\n", wagonLength[k]);

        printf("The space between the vagons: ");
        printf( "%f\n", spaceBetweenVagons[k]);

		printf("The number of Wagons: ");
		printf("%d\n", nWagons[k]);
		
		printf("The Train length: ");
		printf("%d\n", trainLength[k]);
		
		printf("The train is over the max length?");
		printf("%u\n", overMaxTrainLength[k] );
		
	}
	
}
