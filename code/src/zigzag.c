#include <zigzag.h>
#include <charging.h>
#include <unistd.h>


int Charge_time = 0;
int Current_Height = 0;
int Current_Speed = 2;
bool status = true; //true: working, false: need to charge


/*
 *
 *Zigzag algorithm
 *
 *zigzag toward the end of grid then circle back to the start
 *and circle back to the start Again
 *use +/- count variable to determine the direction of zigzag
 *
 * */

float zigzag(int **arr, int **cs_arr, int CS_num, int arr_length, int arr_height){	//zigzag
	float life = Battery_Capacity * 60.0; //to second
	printf("Battery Capacity: %f sec\n", life);
	float trip = Pesticide;
	float used_time = 0; //used_time
	float used_pesticide = 0; //used_pesticide
	int charge_time = 0; //charge_time counter
	int temp = 1;//temp variable (use to control the initial number of j(1/arr_length - 1))
	int dir_x = 1;//direction variable (use to control the direction of zigzag)
	bool dir_y = true;//direction variable (use to check the direction of zigzag)
	int nearest_cs_dx = 0;
	int nearest_cs_dy = 0;
	for(int i = 1; i < arr_height; i++){
		for(int j = temp; j < arr_length && j > 0; j += dir_x){
			//debug code
			//debug code
			if(arr[i][j] >= 1 && life > 0 && trip > 0){
				trip -= arr[i][j] * N_F / P_H_TCrop * P_H_CCrop / 60.0 * 0.5;
				used_pesticide += arr[i][j] * N_F / P_H_TCrop * P_H_CCrop / 60.0 * 0.5;
				arr[i][j] = 0;
				printf("Current position: %d, %d --> %d\n", i, j, arr[i][j]);
//				printf("S_trip = %f\n", trip);
#ifdef DEBUG_MODE
				printf("i --> %d\n", i);
				printf("j --> %d\n", j);
#endif
				life -= 0.5;
				used_time += 0.5;

#ifdef DEBUG_MODE
				print_array(arr, arr_length, arr_height);
#elif TEST_MODE
				print_array(arr, arr_length, arr_height);
#endif
			}else if(arr[i][j] >= 1 && life <= 0 && trip > 0){
				printf("Battery is out of power\n");
				/*
				 *do charging and calculation
				 */
				
	/*set speed*/		set_current_speed(&Current_Speed); //set the current speed to 10
				
				printf("***********************************************\n");
				printf("*    Fly toward charging station              *\n");
				if(CS_num == 1){
					printf("*    Position: ( %3d , %3d ) --> ( 1 , 1 )    *\n", i, j);
				}else{
					find_nearest_cs(cs_arr, CS_num, arr_length, arr_height, i, j, &nearest_cs_dx, &nearest_cs_dy);
					printf("*    Position: ( %3d , %3d ) --> ( %3d , %3d )*\n", i, j, nearest_cs_dx, nearest_cs_dy);
				}
				
				printf("*    Current Speed: %2d			      *\n", Current_Speed);
				printf("***********************************************\n");
				
				//initial
				life = Battery_Capacity * 60.0; //Battery recharge
				trip = Pesticide; //Pesticide recharge
				charge_time += 1; //charge time counter

				//charging
				if(CS_num == 1){
					life -= (single_zigzag_charge( i , j , Current_Speed ) / 2 ); //half of the time is used to fly to the power out position
					used_time += single_zigzag_charge( i , j , Current_Speed );
				}else{
					life -= (multi_zigzag_charge( i , j , nearest_cs_dx, nearest_cs_dy , Current_Speed ) / 2); //half of the time is used to fly to the power out position
				 	used_time += multi_zigzag_charge( i , j , nearest_cs_dx, nearest_cs_dy , Current_Speed );
				}

				printf("*    Charging . . . . . . . . . . . . . .     *\n");
				nanosleep((const struct timespec[]){{0, 500000000L}}, NULL);
				printf("*    Charging Done                            *\n");
				nanosleep((const struct timespec[]){{0, 500000000L}}, NULL);
				
	/*set speed*/		set_current_speed(&Current_Speed); //set the current speed to 2
				
				printf("***********************************************\n");
				printf("*    Fly toward power out position            *\n");
				if(CS_num == 1){
					printf("*    Position: ( 1 , 1 ) --> ( %3d , %3d )    *\n", i, j);
				}else{
					printf("*    Position: ( %3d , %3d ) --> ( %3d , %3d )*\n)", nearest_cs_dx, nearest_cs_dy, i, j);
				}
				
				printf("*    Current Speed: %3d                       *\n", Current_Speed);
				printf("***********************************************\n");
				nanosleep((const struct timespec[]){{0, 800000000L}}, NULL);


				trip -= arr[i][j] * N_F / P_H_TCrop * P_H_CCrop / 60.0 * 0.5;

				used_pesticide += arr[i][j] * N_F / P_H_TCrop * P_H_CCrop / 60.0 * 0.5;
				arr[i][j] = 0;
				printf("Current position: %d, %d --> %d\n", i, j, arr[i][j]);
#ifdef DEBUG_MODE
				printf("CHARGING_DONE\n");
				printf("i --> %d\n", i);
				printf("j --> %d\n", j);
#endif
				life -= 0.5;
				used_time += 0.5;

#ifdef DEBUG_MODE
				print_array(arr, arr_length, arr_height);
#elif TEST_MODE
				print_array(arr, arr_length, arr_height);
#endif


			}else if(arr[i][j] >= 1 && life > 0 && trip <= 0){
				printf("Pesticide is empty\n");
				//save the current position into the queue
				/*
				 *do pesticide refill and calculation
				 */
				exit(0);
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
//	printf("Battery_life: %.4f\n", life);
//	printf("Pesticide_amount: %.4f\n", trip);
	printf(" ====================================================\n");
	printf("|   Used time: %18.4f                    |\n", used_time);
	printf("|   Used pesticide: %12.4f                     |\n", used_pesticide);
	printf("|   Charging time count: %2d                          |\n", charge_time);
	printf(" ====================================================\n");
	return 0;
}
