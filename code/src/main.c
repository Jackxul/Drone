#include<stdio.h>
#include<stdlib.h>
//define
#define Grid_Length 500
#define Grid_Height 500
#define Speed 2 /* (m/s) */
#define Droplet 330 /* (m^3/s) */
#define Height 5 /* (m) */
#define Spacing 1 /* (m) */
#define Battery_Capacity  160 /* (Ah) */
#define Battery_Voltage  52 /* (V) */
#define Battery_Weight  8 /* (kg) */
//main
int main(int argc,char *argv[])
{
	int Charge_time = 0;
	int Current_Height = 0;
	int Current_Speed = 0;
	//malloc 2D array
	int **Array = (int **)malloc(Grid_Length * sizeof(int *));
	for (int i = 0; i < Grid_Height; i++)
	{
		Array[i] = (int *)malloc(Grid_Height * sizeof(int));
	}
	//initialize array	
	for (int i = 0; i < Grid_Length; i++)
	{
		if(i <= 2){

			for(int j = 0; j < Grid_Height; j++)
			{
				Array[i][j] = 2;
			}
		}else{
			for(int j = 0; j < Grid_Height; j++)
			{
				Array[i][j] = 1;
			}
		}
	}


	//print array
	for (int i = 0; i < Grid_Length; i++)
	{
		for (int j = 0; j < Grid_Height; j++)
		{
			printf("%d ", Array[i][j]);
		}
		printf("\n");
	}


		
	return 0;
}


