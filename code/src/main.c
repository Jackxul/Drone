#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<time.h>

//define
#define Grid_Length 30
#define Grid_Height 30
#define Speed 2 /* (m/s) */		// = (1m/0.5s)
#define Droplet 330 /* (m^3/s) */
#define Height 5 /* (m) */
#define Spacing 1 /* (m) */
#define Battery_Capacity  116 /* (min) */
#define Battery_Voltage  52 /* (V) */
#define Battery_Weight  8 /* (kg) */
#define UAV_Postion_up 1
#define UAV_Postion_down 2
#define UAV_Postion_left 3
#define UAV_Postion_right 4
//
//global variable
int Charge_time = 0;
int Current_Height = 0;
int Current_Speed = 0;
int power_out_queue[2][2] = {{0, 0}, {0, 0}};
bool status = true; //true: working, false: need to charge
//time rand
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
//check current status
void check(status){	
	if(status == true){
		Current_Speed = Speed;
		Current_Height = Height;
	}else{	//go to charge station
		Current_Speed = 10;
		Current_Height = 20;
	}
}
/*
 *
 *Zigzag algorithm
 *
 *zigzag toward the end of grid then circle back to the start
 *and circle back to the start Again
 *
 *use +/- count variable to determine the direction of zigzag
 *
 *
 *
 * */
float zigzag(int **arr, int arr_length, int arr_height){	//zigzag
	float life = Battery_Capacity * 60.0; //to second
	printf("Battery Capacity: %f sec\n", life);
	int trip = 0;
	int temp = 1;//temp variable (use to control the initial number of j(1/arr_length - 1))
	int dir_x = 1;//direction variable (use to control the direction of zigzag)
	bool dir_y = true;//direction variable (use to check the direction of zigzag)
	for(int i = 1; i < arr_height; i++){
		for(int j = temp; j < arr_length && j > 0; j + dir_x){
			if(arr[i][j] >= 1 && life > 0){
				arr[i][j]--;
				printf("Current position: %d, %d --> %d\n", i, j, arr[i][j]);
				printf("i --> %d\n", i);
				printf("j --> %d\n", j);
				trip++;
				life -= 0.5;
			}else if(arr[i][j] >= 1 && life <= 0){
				printf("Battery is out of power\n");
				//save the current position into the queue
				power_out_queue[0][0] = i; //Grid_Height
				power_out_queue[0][1] = j; //Grid_Length
				break;
			}else if(dir_y & (j == arr_length - 1)){
				temp = arr_length - 1;
				dir_x = -1;
				dir_y = false;
				break;
			}else if(!(dir_y) & (j == 1)){
				temp = 1;
				dir_x = 1;
				dir_y = true;
				break;
			}
			//printf("check point 2\n");
			//int static count = 0;
			//int staprintf("count: %d\n", ++count);
		}

	}
	return 0;
}
//main
int main(int argc,char *argv[]){
	//argc check
	if(argc != 2){
		printf("Usage: %s <input charging station number>\n", argv[0]);
		return 0;
	}
	//argv
	printf("Charging station number: %s\n", argv[1]);
	//malloc 2D array
	int **Array = (int **)malloc((Grid_Length + 2) * sizeof(int *));
	for (int i = 0; i < Grid_Height; i++)
	{
		Array[i] = (int *)malloc((Grid_Height + 2) * sizeof(int));
	}
	//start point Array[1][1]
	
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
	print_array(Array, Grid_Length, Grid_Height);
//	for (int i = 1; i < Grid_Length; i++)
//	{
//		for (int j = 0; j < Grid_Height; j++)
//		{
//			printf("%2d ", Array[i][j]);
//		}
//		printf("\n");
//	}

	
	zigzag(Array, Grid_Length, Grid_Height);

	printf("check point 3\n");
	print_array(Array, Grid_Length, Grid_Height);
	return 0;
}
