/*
 ** File: main.c
 ** Author: Lidiane A L B Campos
 ** Date 01-10-2018
 ** Description: PEC1, aplicacion para gestionar los Trenes.
 */



#include <stdio.h>
	typedef enum {ELECTRICAL,CARBON,SOLAR,GASOLINE,DIESEL,MAGNETIC} propulsion;
	
	typedef enum {TRUE,FALSE} boolean;

	int identificador;
	int anyoFabric;
	int cantidVagones;
	char modelo;
	float volumenVagon;
	

int main() {
		
	printf("Introduzca el número identificador del tren:");
	scanf("%d", &identificador);
	
	printf("Introduzca el número el año de fabricación:");
	scanf("%d", &anyoFabric);
	
	printf("Introduzca el la cantidad de vagones:");
	scanf("%d", &cantidVagones);
	
	printf("Introduzca el volumen que tiene el vagon:");
	scanf("%f", &volumenVagon);
	
	printf("Introduzca el modelo del tren:");
	scanf(" %c", &modelo);
	
	printf("\nDatos del Tren: identificador: ");
	printf("%d\n", identificador);
	printf("Anyo de Fabricacion: ");
	printf("%d\n", anyoFabric);
	printf("Cantidad de Vagones: ");
	printf("%d\n", cantidVagones);
	printf("Volumen total de los vagones en metros cubicos: ");
	printf("%f\n", cantidVagones*volumenVagon);
	printf("Modelo del Tren: ");
	printf("%c\n", modelo);
		
	return 0;
}
