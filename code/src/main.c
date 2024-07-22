#include "common.h"
#include "zigzag.h"
#include "zamboni.h"

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
	//get current time
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	
	int square_l = Grid_Length * 3 - 2;

	//Create file name based on current time
	char filename[100];
#ifdef ZAMBONI_MODE
	snprintf(filename, sizeof(filename), "output/zamboni/result_%04d%02d%02d_%02d%02d.txt", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min);
#else
	snprintf(filename, sizeof(filename), "output/zigzag/result_%04d%02d%02d_%02d%02d.txt", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min);
#endif
	//open file
	fp = fopen(filename, "w");
	if(fp == NULL){
		printf("Error: cannot open file\n");
		return 1;
	}

	int CS_num = atoi(argv[1]);	//charging station number
	
	//printf("Charging station number: %s\n", argv[1]);
	printf("Charging station number: %d\n", CS_num);
	
	//malloc 1D array
	int *cs_arr = (int *)malloc(CS_num * sizeof(int));//array for charging station      -->hash rule = ((side label) * grid_length + station_position)
							  
	//malloc 2D array
	int **Array = (int **)malloc((square_l) * sizeof(int *));
	for (int i = 0; i < square_l; i++)
	{
		Array[i] = (int *)malloc((square_l) * sizeof(int));
	}
	//start point Array[1][1]
	
	//initialize array	
	for (int i = 0; i < square_l; i++)
	{
			for(int j = 0; j < square_l; j++)
			{
				//boarder
				if(i == 0 || i == Grid_Length - 1 || i == 2 * Grid_Length - 2 || i == 3 * Grid_Length - 3 || j == 0 || j == Grid_Height - 1 || j == 2 * Grid_Height - 2 || j == 3 * Grid_Height - 3){
					Array[i][j] = -1;
				//double spray zone
				}else if(i > 0 && i <= 2 || i < Grid_Length - 1 && i >= Grid_Length - 3 || i >= Grid_Length && i < Grid_Length + 2 || i >= 2 * Grid_Length - 4 && i < 2 * Grid_Length - 2 || i >= 2 * Grid_Length - 1 && i < 2 * Grid_Length + 1 || i >= 3 * Grid_Length - 5 && i < 3 * Grid_Length - 3 ||j > 0 && j <= 2 || j < Grid_Height - 1 && j >= Grid_Height - 3 || j >= Grid_Height && j < Grid_Height + 2 || j >= 2 * Grid_Height - 4 && j < 2 * Grid_Height - 2 || j >= 2 * Grid_Height - 1 && j < 2 * Grid_Height + 1 || j >= 3 * Grid_Height - 5 && j < 3 * Grid_Height - 3){
					Array[i][j] = 2;
				//single spray zone
				}else{
					Array[i][j] = 1;
				}
			}
	}
	set_random_seed();
	
//	set_charge_station(Array, cs_arr, CS_num, Grid_Length, Grid_Height);

	//print array
	print_array(Array, square_l, square_l);

	
	
#ifdef ZAMBONI_MODE
	//zigzag(Array, cs_arr, CS_num, Grid_Length, Grid_Height);
	zamboni(Array, Grid_Length, Grid_Height);
#else
	zigzag(Array, cs_arr, CS_num, 30, 1);
#endif

#ifdef DEBUG_MODE
	print_array(Array, Grid_Length, Grid_Height);
#elif TEST_MODE
	print_array(Array, Grid_Length, Grid_Height);
#endif

//	for(int i = 0; i < CS_num; i++){
//		printf("Charging station %d: %d\n", i, cs_arr[i]);
//	}
	//free 1D array
	free(cs_arr);
	//free 2D array
	for (int i = 0; i < square_l; i++)
	{
		free(Array[i]);
	}
	free(Array);
	fclose(fp);
	return 0;
}
