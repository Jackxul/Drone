#include <zigzag.h>
#include <charging.h>
#include <unistd.h>


#define time_penalty ZTP
#define energy_penalty ZEP
int Charge_time = 0;
int Current_Height = 0;
int Current_Speed = 2;
bool status = true; //true: working, false: need to charge
static double zam_life = Battery_Capacity * 60.0; //to second
static double zam_used_time = 0; //used_time
static double zam_used_pesticide = 0; //used_pesticide
static double zam_energy = 0; //used_energy
static double zam_charge_time = 0; //charge_time counter
static int zam_travel_distance = 0; //travel_distance


/*
 *
 *Zigzag algorithm
 *
 *zigzag toward the end of grid then circle back to the start
 *and circle back to the start Again
 *use +/- count variable to determine the direction of zigzag
 *
 * */

float zigzag(int **arr, int **cs_arr, int CS_num, int square_length, int x_base, int y_base, bool check){	//zigzag
											
	if(check){

		//get current time
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		char filename[100];	
		snprintf(filename, sizeof(filename), "output/zigzag/result_%04d%02d%02d_%02d%02d%2d.txt", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
		fp = fopen(filename, "w");
		if(fp == NULL){
			printf("Error: cannot open file\n");
			return 1;
		}
	}else{
		//get current time
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		char filename[100];
		snprintf(filename, sizeof(filename), "output/zamboni/result_%04d%02d%02d_%02d%02d%2d.txt", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
		fp = fopen(filename, "w");
		if(fp == NULL){
			printf("Error: cannot open file\n");
			return 1;
		}
	}

	float life = Battery_Capacity * 60.0; //to second
	if(check){
		zam_life = life;
		JPrintf("Battery Capacity: %f sec\n", life);
	}else{
		JPrintf("Battery Capacity: %f sec\n", zam_life);
	}
	float trip = Pesticide;
	float energy = 0;
	float used_time = 0; //used_time
	float used_pesticide = 0; //used_pesticide
	int charge_time = 0; //charge_time counter
	int travel_distance = pow((square_length - 2), 2) + square_length - 2 - 1;
	int temp = x_base;//base variable (use to control the initial number of j(1/square_length - 1))
	int dir_x = 1;//direction variable (use to control the direction of zigzag)
	bool dir_y = true;//direction variable (use to check the direction of zigzag)
	int nearest_cs_dx = 0;
	int nearest_cs_dy = 0;
	for(int i = y_base; i < y_base + square_length - 2; i++){
		for(int j = temp; j < x_base + square_length - 1 && j > x_base - 1; j += dir_x){
			//debug code
			//debug code
			if(arr[i][j] >= 1 && life > 0 && trip > 0){
				trip -= arr[i][j] * N_F / P_H_TCrop * P_H_CCrop / 60.0 * 0.5;
				used_pesticide += arr[i][j] * N_F / P_H_TCrop * P_H_CCrop / 60.0 * 0.5;
				//JPrintf("Current position: #[%d, %d] %d --> %d\n", i, j, arr[i][j], 0);
				arr[i][j] = 0;
//				JPrintf("S_trip = %f\n", trip);
#ifdef DEBUG_MODE
				JPrintf("i --> %d\n", i);
				JPrintf("j --> %d\n", j);
#endif
				life -= 0.5;
				used_time += 0.5;
				energy += 0.5;

#ifdef DEBUG_MODE
				print_array(arr, square_length, square_length);
#elif TEST_MODE
				print_array(arr, square_length, square_length);
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
					find_nearest_cs(cs_arr, CS_num, square_length, square_length, i, j, &nearest_cs_dx, &nearest_cs_dy);
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
					energy += single_zigzag_charge( i , j , Current_Speed );
				}else{
					life -= (multi_zigzag_charge( i , j , nearest_cs_dx, nearest_cs_dy , Current_Speed ) / 2); //half of the time is used to fly to the power out position
				 	used_time += multi_zigzag_charge( i , j , nearest_cs_dx, nearest_cs_dy , Current_Speed );
					energy += multi_zigzag_charge( i , j , nearest_cs_dx, nearest_cs_dy , Current_Speed );
				}

				printf("*    Charging . . . . . . . . . . . . . .     *\n");
				//nanosleep((const struct timespec[]){{0, 200000000L}}, NULL);
				printf("*    Charging Done                            *\n");
				//nanosleep((const struct timespec[]){{0, 200000000L}}, NULL);
				
	/*set speed*/		set_current_speed(&Current_Speed); //set the current speed to 2
				
				printf("***********************************************\n");
				printf("*    Fly toward power out position            *\n");
				if(CS_num == 1){
					printf("*    Position: ( 1 , 1 ) --> ( %3d , %3d )    *\n", i, j);
				}else{
					printf("*    Position: ( %3d , %3d ) --> ( %3d , %3d )*\n)", nearest_cs_dx, nearest_cs_dy, i, j);
				}
				
				printf("*    Current Speed: %2d                        *\n", Current_Speed);
				printf("***********************************************\n");
				//nanosleep((const struct timespec[]){{0, 200000000L}}, NULL);


				trip -= arr[i][j] * N_F / P_H_TCrop * P_H_CCrop / 60.0 * 0.5;

				used_pesticide += arr[i][j] * N_F / P_H_TCrop * P_H_CCrop / 60.0 * 0.5;
				printf("Current position: #[%d, %d] %d --> %d\n", i, j, arr[i][j], 0);
				arr[i][j] = 0;
#ifdef DEBUG_MODE
				printf("CHARGING_DONE\n");
				printf("i --> %d\n", i);
				printf("j --> %d\n", j);
#endif
				life -= 0.5;
				used_time += 0.5;
#ifdef DEBUG_MODE
				print_array(arr, square_length, square_length);
#elif TEST_MODE
				print_array(arr, square_length, square_length);
#endif


			}else if(arr[i][j] >= 1 && life > 0 && trip <= 0){
				printf("Pesticide is empty\n");
				//save the current position into the queue
				/*
				 *do pesticide refill and calculation
				 */
				exit(0);
			}else if(dir_y & (j == x_base + square_length - 2)){
#ifdef DEBUG_MODE
				printf("temp change = %d\n", temp);
#endif
				temp = x_base + square_length - 3;
				dir_x = -1;
				dir_y = false;
				life -= energy_penalty;
				used_time *= time_penalty;
				//JPrintf("check point --> \n");
#ifdef DEBUG_MODE
				JPrintf("dir_y = %d\n", dir_y);
				JPrintf("j = %d\n", j);
#endif
			}else if(arr[i][j] < 1){
#ifdef DEBUG_MODE
				JPrintf("i = %d\n",i);
				JPrintf("j = %d\n",j);
				JPrintf("arr[i][j] = %d\n", arr[i][j]);
				JPrintf("temp = %d\n", temp);
				JPrintf("Worng position\n");
#endif
				break;

			}
			if(!(dir_y) & (j == x_base)){
				temp = x_base;
				dir_x = 1;
				dir_y = true;
#ifdef DEBUG_MODE
				JPrintf("temp change = %d\n", temp);
				JPrintf("dir_y = %d\n", dir_y);
				JPrintf("j = %d\n", j);
				life -= energy_penalty;
				used_time *= time_penalty;
#endif
			}
			//JPrintf("check point 2\n");
			//int static count = 0;
		}
	}
	
	if(check){
	//	JPrintf("Battery_life: %.4f\n", life);
	//	JPrintf("Pesticide_amount: %.4f\n", trip);
		JPrintf(" ====================================================\n");
		JPrintf("|   Zigzag Algorithm                                 |\n");
		JPrintf("|   Grid Length: %d (square)                        |\n", square_length);
		JPrintf("|   Travel distance: %12d m                  |\n", travel_distance);
		JPrintf("|   Used time: %18.4f                    |\n", used_time);
		JPrintf("|   Used pesticide: %12.4f                     |\n", used_pesticide);
		JPrintf("|   Charging time count: %2d                          |\n", charge_time);
		JPrintf("|   Energy: %25.4f                |\n", energy * Power_Watt);
		JPrintf(" ====================================================\n");
		fclose(fp);
	}else{
		zam_used_time = used_time;
		zam_used_pesticide = used_pesticide;
		zam_energy = energy;
		zam_charge_time = charge_time;
		zam_travel_distance = travel_distance;
		
		set_multi(&zam_used_pesticide, 0);
		set_multi(&zam_charge_time, 1);
		set_multi(&zam_used_time, 2);
		set_multi(&zam_energy, 2);
		set_multi(&zam_travel_distance, 3);
		printf("set_multi\n");

		JPrintf(" ====================================================\n");
		JPrintf("|   Zamboni Algorithm                                |\n");
		JPrintf("|   Grid Length: %d (square)                        |\n", square_length);
		JPrintf("|   Travel distance: %12d ( m )              |\n", zam_travel_distance / 1);
		JPrintf("|   Used time: %18.4f                    |\n", zam_used_time);
		JPrintf("|   Used pesticide: %12.4f                     |\n", zam_used_pesticide);
		JPrintf("|   Charging time count: %2d                          |\n", (int)(zam_charge_time / 1));
		JPrintf("|   Energy: %25.4f                |\n", zam_energy * Power_Watt);
		JPrintf(" ====================================================\n");
		fclose(fp);	
	}

	return 0;
}




