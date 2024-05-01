#include<stdio.h>
#include<stdlib.h>
//define
#define Grid_Length 50
#define Grid_Height 50
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
	int **Array = (int **)malloc((Grid_Length + 2) * sizeof(int *));
	for (int i = 0; i < Grid_Height; i++)
	{
		Array[i] = (int *)malloc((Grid_Height + 2) * sizeof(int));
	}
	//initialize array	
	for (int i = 0; i < Grid_Length; i++)
	{

			for(int j = 0; j < Grid_Height; j++)
			{
				//boarder
				if(i == 0 || i == Grid_Length - 1 || j == 0 || j == Grid_Height - 1){
					Array[i][j] = -1;
				//double spray zone
				}else if(i > 0 && i <= 2 || i < Grid_Length - 1 && i >= Grid_Length - 3 || j > 0 && j <= 2 || j < Grid_Height - 1 && j >= Grid_Height - 3){
					Array[i][j] = 2;
				//single spray zone
				}else{
					Array[i][j] = 1;
				}
			}
	}

	//print array
	for (int i = 0; i < Grid_Length; i++)
	{
		for (int j = 0; j < Grid_Height; j++)
		{
			printf("%2d ", Array[i][j]);
		}
		printf("\n");
	}


		
	return 0;
}


