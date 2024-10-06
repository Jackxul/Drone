#include "common.h"
#include "zigzag.h"
#include "spiral.h"
#include "respiral.h"
#include "zamboni.h"

#define L_X_P 1 
#define L_Y_P Grid_Height
#define R_X_P (2 * Grid_Length - 1)
#define	R_Y_P Grid_Height
#define	U_X_P Grid_Length
#define	U_Y_P 1
#define	D_X_P Grid_Length
#define	D_Y_P (2 * Grid_Height - 1)
#define M_X_P Grid_Length
#define M_Y_P Grid_Height


void check(bool status ,int Current_Speed, int Current_Height){	
	if(!status){
		Current_Speed = 10;
		Current_Height = 20;
	}
}


//main
int main(int argc,char *argv[]){
	//argc check
	if(argc != 2){
		JPrintf("Usage: %s <input charging station number>\n", argv[0]);
		return 0;
	}
	//argv
	

	int square_l = Grid_Length * 3 - 2;
	//Create file name based on current time

	int CS_num = atoi(argv[1]);	//charging station number
	
	//printf("Charging station number: %s\n", argv[1]);
	printf("Charging station number: %d\n", CS_num);
	
	//malloc 2D array
	int **cs_arr = (int **)malloc(5 * sizeof(int *));
	for (int i = 0; i < 5; i++)
	{
		cs_arr[i] = (int *)malloc(CS_num * sizeof(int));//array for charging station      -->hash rule = ((side label) * grid_length + station_position)
	}
	//initialize array
	for (int i = 0; i < 5; i++)
	{
		for(int j = 0; j < CS_num; j++)
		{
			cs_arr[i][j] = -1;
		}
	}
							  
	//malloc 2D array
	int **Array = (int **)malloc((square_l) * sizeof(int *));
	for (int i = 0; i < square_l; i++)
	{
		Array[i] = (int *)malloc((square_l) * sizeof(int));
	}
	
	//initialize array	
	
	fill_grid(Array, square_l, Grid_Length, Grid_Height, true);
	set_random_seed();
	
	set_charge_station(Array, cs_arr, CS_num, Grid_Length, square_l);

	//print array
	print_array(Array, square_l, square_l);

	
	
#ifdef ZAMBONI_MODE
	//zigzag(Array, cs_arr, CS_num, Grid_Length, Grid_Height);
	//zamboni(Array, Grid_Length, Grid_Height);
#else
	//zigzag(Array, cs_arr, CS_num, Grid_Length, L_X_P, L_Y_P);
	//zigzag(Array, cs_arr, CS_num, Grid_Length, R_X_P, R_Y_P);
	//zigzag(Array, cs_arr, CS_num, Grid_Length, U_X_P, U_Y_P);
	//zigzag(Array, cs_arr, CS_num, Grid_Length, D_X_P, D_Y_P);
	
	//Zigzag
	zigzag(Array, cs_arr, CS_num, Grid_Length, M_X_P, M_Y_P, true);
	fill_grid(Array, square_l, Grid_Length, Grid_Height, false);

	//Zamboni
	zigzag(Array, cs_arr, CS_num, Grid_Length, M_X_P, M_Y_P, false);
	fill_grid(Array, square_l, Grid_Length, Grid_Height, false);
	
	//Spiral
	spiral(Array, cs_arr, CS_num, Grid_Length, M_X_P, M_Y_P);
	fill_grid(Array, square_l, Grid_Length, Grid_Height, false);
	
	//Reverse-Spiral
	R_spiral(Array, cs_arr, CS_num, Grid_Length, M_X_P, M_Y_P);

#endif
	//printf("Finish\n");
#ifdef DEBUG_MODE
	print_array(Array, square_l, square_l);
#elif TEST_MODE
	//print_array(Array, square_l, square_l);
#endif

//	for(int i = 0; i < CS_num; i++){
//		printf("Charging station %d: %d\n", i, cs_arr[i]);
//	}
	//free 2D array
	for (int i = 0; i < 5; i++)
	{
		free(cs_arr[i]);
	}
	free(cs_arr);
	//free 2D array
	for (int i = 0; i < square_l; i++)
	{
		free(Array[i]);
	}
	free(Array);
	return 0;
}
