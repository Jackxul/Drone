#include <spiral.h>
#include <charging.h>
#include <unistd.h>
#include <common.h>


int S_Charge_time = 0;
int S_Current_Height = 0;
int S_Current_Speed = 2;

/*
 *
 *Spiral algorithm
 *
 *
 *
 *
 *
 * */

int is_valid(int **arr, int square_l, int cx, int cy, int dir) { //check if the next position is valid(-1 or 0)
	if(dir == UP){
		return (arr[cy - 1][cx] > 0 ? UP : RIGHT);
	}else if(dir == DOWN){
		return (arr[cy + 1][cx] > 0 ? DOWN : LEFT);
	}else if(dir == LEFT){
		return (arr[cy][cx - 1] > 0 ? LEFT : UP);
	}else if(dir == RIGHT){
		return (arr[cy][cx + 1] > 0 ? RIGHT : DOWN);
	}else{
		printf("Error: invalid direction\n");
		exit(1);
	}
}


float spiral(int **arr, int **cs_arr, int CS_num, int square_l, int x_base, int y_base){	//spiral

	//get current time and create file to store the result
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	char filename[100];	
	snprintf(filename, sizeof(filename), "output/spiral/result_%04d%02d%02d_%02d%02d%2d.txt", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	sp_fp = fopen(filename, "w");
	if(sp_fp == NULL){
		printf("Error: cannot open file\n");
		return 1;
	}
	printf("spiral debug1\n");
	float life = Battery_Capacity * 60.0; //to second
	JPrintf("Battery Capacity: %f sec\n", life);
	float trip = Pesticide;
	float energy = 0;
	float used_time = 0; //used_time
	float used_pesticide = 0; //used_pesticide
	int charge_time = 0; //charge_time counter
	int x = x_base, y = y_base; //start position 
	int dir = RIGHT;  // 方向的指標，從右方向開始
	int final_x, final_y;
    	long int max_cells = pow(square_l - 2, 2); // 方形內的總格子數
	int temp = x_base;//base variable (use to control the initial number of j(1/square_length - 1))
	int nearest_cs_dx = 0;
	int nearest_cs_dy = 0;
	printf("spiral debug2\n");


    	while (max_cells) {
        // 檢查當前位置是否合法（在該方形內且不為邊界）
		if(arr[y][x] == 1 || arr[y][x] == 2){
			trip -= arr[y][x] * N_F / P_H_TCrop * P_H_CCrop / 60.0 * 0.5;
			used_pesticide += arr[y][x] * N_F / P_H_TCrop * P_H_CCrop / 60.0 * 0.5;
			arr[y][x] = 0;
#ifdef DEBUG_MODE
			//JPrintf("[ x , y ] --> [ %d , %d ]\n", x, y);
#endif
			life -= 0.5;
			used_time += 0.5;
			energy += 0.5;
#ifdef DEBUG_MODE			
			print_array(arr, square_l, square_l);
#endif
#ifdef TEST_MODE
			//print_array(arr, square_l, square_l);
#endif
			max_cells--;
			if(life <= 0){
				JPrintf("Battery is out of power\n");
				set_current_speed(&S_Current_Speed); //set current speed to 10
				
				life = Battery_Capacity * 60.0;//Battery recharge
				trip = Pesticide;//Pesticide refill
				charge_time += 1;//charge time counter

				if(CS_num == 1){
					printf("spiral debug3\n");
					life -= (single_zigzag_charge( x, y, S_Current_Speed ) / 2 ); //half of the time is used to fly to the power out position
					used_time += (single_zigzag_charge( x, y, S_Current_Speed ) / 2 );
					energy += (single_zigzag_charge( x, y, S_Current_Speed ) / 2 );
				}else{
					printf("spiral debug4\n");
					find_nearest_cs(cs_arr, CS_num, square_l, square_l, x, y, &nearest_cs_dx, &nearest_cs_dy);
					life -= (multi_zigzag_charge( x, y, nearest_cs_dx, nearest_cs_dy, S_Current_Speed ) / 2 ); //half of the time is used to fly to the power out position
					used_time += (multi_zigzag_charge( x, y, nearest_cs_dx, nearest_cs_dy, S_Current_Speed ) / 2 );
					energy += (multi_zigzag_charge( x, y, nearest_cs_dx, nearest_cs_dy, S_Current_Speed ) / 2 );
				}
				set_current_speed(&S_Current_Speed); //set current speed to 2
			}
			switch(is_valid(arr, square_l, x, y, dir)){
				case UP:
					printf("max_cells: %ld\n", max_cells);
					y--;
					dir = UP;
					break;
				case DOWN:
					printf("max_cells: %ld\n", max_cells);
					y++;
					dir = DOWN;
					break;
				case LEFT:
					printf("max_cells: %ld\n", max_cells);
					x--;
					dir = LEFT;
					break;
				case RIGHT:
					printf("max_cells: %ld\n", max_cells);
					x++;
					dir = RIGHT;
					break;
				default:
					printf("Error: invalid direction\n");
					exit(1);
			}
		}
	}

	final_x = x;
	final_y = y;
	
	printf("x_final: %d\n", final_x);
	printf("y_final: %d\n", final_y);


	JPrintf(" ====================================================\n");
	JPrintf("|   Spiral Algorithm                               |\n");
	JPrintf("|   Used time: %18.4f                    |\n", used_time);
	JPrintf("|   Used pesticide: %12.4f                     |\n", used_pesticide);
	JPrintf("|   Charging time count: %2d                          |\n", charge_time);
	JPrintf("|   Energy: %25.4f             |\n", energy * Power_Watt);
	JPrintf(" ====================================================\n");
	fclose(sp_fp);
	return 0;
}


