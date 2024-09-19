#include <respiral.h>
#include <charging.h>
#include <unistd.h>
#include <common.h>


int RS_Charge_time = 0;
int RS_Current_Height = 0;
int RS_Current_Speed = 2;
//
/*
 *
 *Spiral algorithm
 *
 *
 *
 *
 *
 * */

static int max_l = 1;

int R_is_valid(int **arr, int square_l, int dir, int *count, int *travel_l) { //for decision of when should turn the direction of respiral
	*travel_l -= 1;
	bool flag = false; //ture for turn the direction
	if(*travel_l == 0 && *count == 0){ //need to turn the direction and increase the length
		max_l += 1; //next length will increase 1 in respiral
		*count = 2; //recharge the count to 2 for next turn
		*travel_l = max_l; //recharge the travel_l
		flag = true; //turn the direction
	}else if(*travel_l == 0 && *count == 1){ //need to turn the direction
		*count -= 1; //decrease the count to 1 for next turn
		*travel_l = max_l; //recharge the travel_l
		flag = true; //turn the direction
	}else{ 
		flag = false;
		//do nothing
	}
	//turn the direction
	if(dir == UP){
		return (flag ? LEFT : UP);
	}else if(dir == DOWN){
		return (flag ? RIGHT : DOWN);
	}else if(dir == LEFT){
		return (flag ? DOWN : LEFT);
	}else if(dir == RIGHT){
		return (flag ? UP : RIGHT);
	}else{
		printf("Error: invalid direction\n");
		exit(1);
	}
}


float R_spiral(int **arr, int **cs_arr, int CS_num, int square_l, int x_base, int y_base){	//respiral main function
	
	int center_x = square_l / 2; //discard unconditionally
	int center_y = (square_l % 2 == 0 ) ? center_x + 1 : center_x; // if even, center_y is at the left-bottom coner of the center square
	
	int final_x, final_y;
	final_x = x_base + center_x - 1;
	final_y = y_base + center_y - 1;
	int dir = (square_l % 2 == 0 ? RIGHT : LEFT);  // if even, start from right, else start from left
    	int max_cells = pow(square_l - 2, 2); // 方形內的總格子數 (1 center + 1 + 1 + 2 + 2 + ... + n-1 + n-1 + n + n + n ends)
	int loop_count = 1, tail_route_count = 0;
	max_cells--; //remove the center cell
	while(max_cells){ // break when becomes 0
		max_cells -= 2 * loop_count;
		if(max_cells == loop_count){
			max_cells -= loop_count;
			tail_route_count = loop_count;
		}else{
			loop_count++;
		}
	}	
    	max_cells = pow(square_l - 2, 2); // 方形內的總格子數 (1 center + 1 + 1 + 2 + 2 + ... + n-1 + n-1 + n + n + n ends)
	printf("max_cells: %d\n", max_cells);
	printf("loop_count: %d\n", loop_count);
	printf("tail_route_count: %d\n", tail_route_count);
	int travel_length = 1; //initial travel length
	int travel_count = 2; //initial count

	//get current time and create file to store the result
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	char filename[100];	
	snprintf(filename, sizeof(filename), "output/respiral/result_%04d%02d%02d_%02d%02d%2d.txt", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	fp = fopen(filename, "w");
	if(fp == NULL){
		printf("Error: cannot open file\n");
		return 1;
	}
	printf("R_spiral debug1\n");
	float life = Battery_Capacity * 60.0; //to second
	JPrintf("Battery Capacity: %f sec\n", life);
	float trip = Pesticide;
	float energy = 0;
	float used_time = 0; //used_time
	float used_pesticide = 0; //used_pesticide
	int charge_time = 0; //charge_time counter
	int temp = x_base;//base variable (use to control the initial number of j(1/square_length - 1))
	int nearest_cs_dx = 0;
	int nearest_cs_dy = 0;
	printf("R_spiral debug2\n");
	
	//起始點當作已走訪過
	trip -= arr[final_y][final_x] * N_F / P_H_TCrop * P_H_CCrop / 60.0 * 0.5;
	used_pesticide += arr[final_y][final_x] * N_F / P_H_TCrop * P_H_CCrop / 60.0 * 0.5;
	arr[final_y][final_x] = 0;
#ifdef DEBUG_MODE
	JPrintf("[ x , y ] --> [ %d , %d ]\n", final_x, final_y);
#endif
	life -= 0.5;
	used_time += 0.5;
	energy += 0.5;
	max_cells--;
	
	final_x = (square_l % 2 == 0 ? final_x++ : final_x--);


    	while (max_cells) {
        // 檢查當前位置是否合法（在該方形內且不為邊界）
		trip -= arr[final_y][final_x] * N_F / P_H_TCrop * P_H_CCrop / 60.0 * 0.5;
		used_pesticide += arr[final_y][final_x] * N_F / P_H_TCrop * P_H_CCrop / 60.0 * 0.5;
		arr[final_y][final_x] = 0;
#ifdef DEBUG_MODE
		JPrintf("[ x , y ] --> [ %d , %d ]\n", final_x, final_y);
#endif
		life -= 0.5;
		used_time += 0.5;
		energy += 0.5;
		//print_array(arr, square_l, square_l);
		max_cells--;
#ifdef DEBUG_MODE
		print_array(arr, square_l, square_l);
#endif
		print_array(arr, square_l, square_l);
		switch(R_is_valid(arr, square_l, dir, &travel_count, &travel_length)){
			case UP:
				printf("max_cells: %d\n", max_cells);
				final_y--;
				dir = UP;
				break;
			case DOWN:
				printf("max_cells: %d\n", max_cells);
				final_y++;
				dir = DOWN;
				break;
			case LEFT:
				printf("max_cells: %d\n", max_cells);
				final_x--;
				dir = LEFT;
				break;
			case RIGHT:
				printf("max_cells: %d\n", max_cells);
				final_x++;
				dir = RIGHT;
				break;
			default:
				printf("Error: invalid direction\n");
				exit(1);
		}
	}

	

	JPrintf(" ====================================================\n");
	JPrintf("|   Used time: %18.4f                    |\n", used_time);
	JPrintf("|   Used pesticide: %12.4f                     |\n", used_pesticide);
	JPrintf("|   Charging time count: %2d                          |\n", charge_time);
	JPrintf("|   Energy: %25.4f             |\n", energy * Power_Watt);
	JPrintf(" ====================================================\n");
	fclose(fp);
	return 0;
}


