#include <zamboni.h>

float zamboni(int **arr, int arr_length, int arr_height) {
	float life = Battery_Capacity * 60.0; //to second
	printf("Battery Capacity: %f sec\n", life);
	float trip = Pesticide;
	int start_row = 1;
	int end_row = arr_height / 2;
	int temp_row = 1;
	int temp_col = 1;
#ifdef DEBUG_MODE
	printf("start_row: %d\n", start_row);
	printf("end_row: %d\n", end_row);
#endif
#ifdef GRID_SIZE
	printf("start_row: %d\n", start_row);
	printf("end_row: %d\n", end_row);
#endif
	
	for(int i = temp_row; i < arr_length; i++){
		


	}
	//int temp = 1;//temp variable (use to control the initial number of j(1/arr_length - 1))
	//int dir_x = 1;//direction variable (use to control the direction of zigzag)
	//bool dir_y = true;//direction variable (use to check the direction of zigzag)
/*	for(int i = 1; i < arr_height; i++){
		for(int j = temp; j < arr_length && j > 0; j += dir_x){
			//debug code
			//debug code
			if(arr[i][j] >= 1 && life > 0){
				trip -= arr[i][j] * N_F / 60.0 * 0.5;
				arr[i][j] = 0;
				printf("Current position: %d, %d --> %d\n", i, j, arr[i][j]);
#ifdef DEBUG_MODE
				printf("i --> %d\n", i);
				printf("j --> %d\n", j);
#endif
				life -= 0.5;
#ifdef DEBUG_MODE
				print_array(arr, arr_length, arr_height);
#elif TEST_MODE
				print_array(arr, arr_length, arr_height);
#endif
			}else if(arr[i][j] >= 1 && life <= 0){
				printf("Battery is out of power\n");
				//save the current position into the queue
				singleZ_power_out_queue[0][0] = i; //Grid_Height
				singleZ_power_out_queue[0][1] = j; //Grid_Length
			*/	/*
				 *
				 *do charging and calculation
				 *
				 * */
			/*	exit(0);
			}else if(arr[i][j] >= 1 && trip <= 0){
				printf("Pesticide is empty\n");
				//save the current position into the queue
				singleZ_power_out_queue[0][0] = i; //Grid_Height
				singleZ_power_out_queue[0][1] = j; //Grid_Length
			*/	/*
				 *
				 *do charging and calculation
				 *
				 * */
			/*	exit(0);
			}else if(dir_y & (j == arr_length - 1)){
#ifdef DEBUG_MODE
				printf("temp change = %d\n", temp);
#endif
				temp = arr_length - 2;
				dir_x = -1;
				dir_y = false;
				//printf("check point --> \n");
#ifdef DEBUG_MODE
				printf("dir_y = %d\n", dir_y);
				printf("j = %d\n", j);
#endif
			}else if(arr[i][j] < 1){
#ifdef DEBUG_MODE
				printf("i = %d\n",i);
				printf("j = %d\n",j);
				printf("arr[i][j] = %d\n", arr[i][j]);
				printf("temp = %d\n", temp);
				printf("Worng position\n");
#endif
				break;

			}
			if(!(dir_y) & (j == 1)){
				temp = 1;
				dir_x = 1;
				dir_y = true;
#ifdef DEBUG_MODE
				printf("temp change = %d\n", temp);
				printf("dir_y = %d\n", dir_y);
				printf("j = %d\n", j);
#endif
			}
			//printf("check point 2\n");
			//int static count = 0;
			//int staprintf("count: %d\n", ++count);
		}
	}
*/
	printf("Battery_life: %.4f\n", life);
	printf("Pesticide_amount: %.4f\n", trip);
	return 0;
}
