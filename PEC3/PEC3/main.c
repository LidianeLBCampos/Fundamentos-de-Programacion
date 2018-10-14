#include <stdio.h>

const int NUM = 5;
const float MAX_WAGON_CAPACITY = 0.85;
const float MAX_WAGON_CAPACITY_ANIMALS = 0.5;
const  int LIMIT1 = 500;
const  int  LIMIT2 = 2500;
const float FRAGILE = 1.10;
const float DANGEROUS = 1.15;
const float FIRST_PRICE = 0.50;
const float SECOND_PRICE = 0.45;
const float THIRD_PRICE = 0.40;

   enum goodType { FOOD , CHEMICAL ,	ANIMALS , 	VEHICLES,	ELECTRONICS, CONSTRUCTION,	OTHERS} ;
   enum boolean {TRUE,FALSE} ;

	int goodId;
	int nWagons;
	float goodVolume;
	enum boolean isFragile;
	enum boolean isDangerous;
	enum goodType gdType;
	float totalVolAvailable;
	float trainData[5];
	float transportPrice;



int main(){
	
	printf("==============================\n");
	printf("Enter the good data\n");

	printf("Enter the good id: \n");
	scanf("%d", &goodId);
	
	printf("Enter the good volume (m³): \n");
	scanf("%f", &goodVolume);

	printf("Enter the good type (1-FOOD, 2-CHEMICAL, 3-ANIMALS, 4-VEHICLES, 5-ELECTRONICS, 6-CONSTRUCTION, 7-OTHERS)\n");
    scanf( "%u", &gdType);
	
	printf("Is the good fragile? 1-YES 0-NO\n") ;
	scanf( "%u", &isFragile);

	printf("Is the good dangerous?1-YES 0-NO\n");
	scanf( "%u", &isDangerous);
		
    printf("Enter the train informations");
	printf("\nMaximum length's train:");
	scanf( "%f", &trainData[0]);
	printf("\nMaximum length's locomotive: ");
	scanf( "%f", &trainData[1]);
	printf("\nMaximum length's each wagon: ");
	scanf( "%f", &trainData[2]);
	printf("\nThe space between wagons: ");
	scanf( "%f", &trainData[3]);
	printf("\nThe volume of a wagon: ");
	scanf( "%f", &trainData[4]);
	
	nWagons = ((int)(trainData[0] - trainData[1]) / ( trainData[2] + trainData[3]));
	
         if (gdType == ANIMALS){
			 totalVolAvailable = ((nWagons * trainData[4]) * MAX_WAGON_CAPACITY_ANIMALS);
		} else {
              totalVolAvailable = ((nWagons * trainData[4]) * MAX_WAGON_CAPACITY);
        }
		
		if (goodVolume <= totalVolAvailable) {
		if  (goodVolume <= LIMIT1) {
			transportPrice = goodVolume *  FIRST_PRICE;
			} else 
				if ( goodVolume >  LIMIT1 && goodVolume <= LIMIT2) {
					transportPrice = goodVolume *  SECOND_PRICE;
					} else {
						transportPrice = goodVolume *  THIRD_PRICE;
						}
		if (isFragile==1) {
			transportPrice = transportPrice  * FRAGILE;
	}	
	if (isDangerous==1) {
		transportPrice = transportPrice  *  DANGEROUS;
		}
		printf("Wagons number : ");
		printf("%d\n", nWagons);
		printf("Good identifier: ");
		printf("%d\n", goodId);
		printf("Transport price: ");
		printf("%f\n", transportPrice);
		} else {
			printf("The product volume is over the maximum allowed\n");
			}



	return 0;
}
