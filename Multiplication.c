/*
	Multiplication.c
	
	Example of how Booth's Double Algorithm works. Modify 
	num1 and num2 arrays to perform a multiplication. Uses
	4 bits for integer number and 4 bits for decimal.
	

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int num1[] = {1,0,1,1,0,0,0,0};
int num2[] = {1,0,1,1,1,0,0,1};

int size = 0;

int x, y, z;
int r = 0;
int weight = 0;

int temp = 0;
int number =0;
int acc;
int salto=0;

int main(){
	
	int sz_num1 = sizeof(num1)/sizeof(int);
	int sz_num2 = sizeof(num1)/sizeof(int);

	

	size = sz_num2;
	
	if (sz_num1 > sz_num2){
		size = sz_num1;
	}

	printf("size: %d\n", size);

	int array_weight[size/2];
	int preeliminar[size/2];

	// Tabla de verdad de booth doble
	for (int i = 0; i <= size - 2; i += 2){
		x = num2[i];
		y = num2[i+1];
		z = num2[i+2];
		if(i>=size-2){
			z=0;
		}

		r = x << 2 | y << 1 | z;

		switch (r){
			case 0:
				weight = 0;
				break;
			case 1:
				weight = 1;
				break;
			case 2:
				weight = 1;
				break;
			case 3:
				weight = 2;
				break;
			case 4:
				weight = -2;
				break;
			case 5:
				weight = -1;
				break;
			case 6:
				weight = -1;
				break;
			case 7:
				weight = 0;
				break;
		}
		array_weight[i/2] = weight;
	}
	
	// print booth double
	for (int i = 0; i < size / 2; i++){
		printf("%d\n", array_weight[i]);
	}
	printf("\n");


	// Convertir a numero decimal
	if (num1[0] == 1){
		// convierte a negativo
		for (int j = 0; j < size - 1; j++){
			number += (!(num1[size-1 - j]) << j);
			//printf("bits: %d\n", number);
		}
		number ++;
		number = -number;

	}else{
		for (int j = 0; j < size - 1; j++){
			number += (num1[size - 1 - j] << j);
		}
	}

	printf("number: %d\n", number);



	// Suma por partes
	//for (int i = (size/2) - 1; i >= 0; i--){
	for (int i = (size/2)-1; i >=0; i--){
		if (array_weight[i] < 0){
			// temp = number complemento a 2
			temp = -number;
		}else if(array_weight[i] == 0){
			temp = 0;
		}else{
			temp = number;
		}

		
		//preeliminar[i] = temp << i * 2 + abs(array_weight[(size/2)-1-i]) - 1;
		
		if (abs(array_weight[i])==2){
			salto=1;
		}
		else{

			salto=0;
		} 
		int g=((((size/2)-1-i)*2)+salto);
		printf("g=%d\n",g );
		preeliminar[i]= temp<<g;
		printf("pree: %d\n", preeliminar[i]);
	}
		
	for (int i = 0; i < size/2; i++){
		acc += preeliminar[i];
		printf("acc: %d\n",acc);
	}

	printf("%d\n",acc);
}