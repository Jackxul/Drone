#include "common.h"
#include "zigzag.h"


void check(bool status ,int Current_Speed, int Current_Height){	
	if(!status){
		Current_Speed = 10;
		Current_Height = 20;
	}
}


//float zamboni(int **arr, int arr_length, int arr_height){	//zamboni
//	float life = Battery_Capacity * 60.0; //to second
//	printf("Battery Capacity: %f sec\n", life);
//	int trip = 0;
//	int temp = 1;//temp variable (use to control the initial number of j(1/arr_length - 1))
//	int dir_x = 1;//direction variable (use to control the direction of zigzag)
//	bool dir_y = true;//direction variable (use to check the direction of zigzag)
//	for(int i = 1; i < arr_height; i++){
//		for(int j = temp; j < arr_length && j > 0; j += dir_x){
//			//debug code
//			//debug code
//			if(arr[i][j] >= 1 && life > 0){
//				arr[i][j] = 0;
//				printf("Current position: %d, %d --> %d\n", i, j, arr[i][j]);
//				printf("i --> %d\n", i);
//				printf("j --> %d\n", j);
//				trip++;
//				life -= 0.5;
//#ifdef DEBUG_MODE
//				print_array(arr, arr_length, arr_height);
//#elif TEST_MODE
//				print_array(arr, arr_length, arr_height);
//#endif
//			}else if(arr[i][j] >= 1 && life <= 0){
//				printf("Battery is out of power\n");
//				//save the current position into the queue
//				power_out_queue[0][0] = i; //Grid_Height
//				power_out_queue[0][1] = j; //Grid_Length
//				/*
//				 *
//				 *
//				 *do charging and calculation
//				 *
//				 *
//				 *
//				 *
//				 * */
//				exit(0);
//			}else if(dir_y & (j == arr_length - 1)){
//				printf("temp change = %d\n", temp);
//				temp = arr_length - 2;
//				dir_x = -1;
//				dir_y = false;
//				printf("check point --> \n");
//				//print dir_y
//				printf("dir_y = %d\n", dir_y);
//				printf("j = %d\n", j);
//			}else if(arr[i][j] < 1){
//				printf("i = %d\n",i);
//				printf("j = %d\n",j);
//				printf("arr[i][j] = %d\n", arr[i][j]);
//				printf("temp = %d\n", temp);
//				printf("Worng position\n");
//				break;
//
//			}
//			if(!(dir_y) & (j == 1)){
//				temp = 1;
//				printf("temp change = %d\n", temp);
//				dir_x = 1;
//				dir_y = true;
//				//print dir_y
//				printf("dir_y = %d\n", dir_y);
//				printf("j = %d\n", j);
//			}
//			//printf("check point 2\n");
//			//int static count = 0;
//			//int staprintf("count: %d\n", ++count);
//		}
//	}
//	printf("life: %f\n", life);
//	return 0;
//}
//main
int main(int argc,char *argv[]){
	//argc check
	if(argc != 2){
		printf("Usage: %s <input charging station number>\n", argv[0]);
		return 0;
	}
	//argv
	
	int CS_num = atoi(argv[1]);	//charging station number
	
	//printf("Charging station number: %s\n", argv[1]);
	printf("Charging station number: %d\n", CS_num);
	

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
	//zamboni(Array, Grid_Length, Grid_Height);
	print_array(Array, Grid_Length, Grid_Height);
	free(Array);
	return 0;
}
