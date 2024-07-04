#include <common.h>


int rand_time(int min, int max)
{
	return min + rand() % (max - min + 1);
}
//sqrt
double distance(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
//time calculate
float route_time(double route, int speed)
{
	return (route / speed);
}
void print_array(int **arr, int arr_length, int arr_height){
	for(int i = 0; i < arr_length; i++){
		for(int j = 0; j < arr_height; j++){
			printf("%2d ", arr[i][j]);
		}
		printf("\n");
	}
}
void set_charge_station(int **arr, int *cs_arr, int CS_num, int arr_length, int arr_height){
/*
 *up 	--> 1
 *down	--> 2
 *left	--> 3
 *right	--> 4
 */	
	for(int count = 0; count < CS_num; count++){

	}
	
	
	
	
}
