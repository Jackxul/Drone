#include <zamboni.h>
#include <zigzag.h>

static float life = Battery_Capacity * 60.0; //to second
static float trip = Pesticide;
bool locker1 = true;	//lock the col, locker for col
bool locker2 = false;	//unlock the row, locker for row

void set_lock(){
	if(locker1){
		locker1 = false;
		locker2 = true;

	}else{
		locker1 = true;
		locker2 = false;
	}
}

int set_col(int col , int value){
	if(locker1){
		int const l_col = col;
		return l_col;
	}else{
		return col + value;
	}
}

int set_row(int row , int value){
	if(locker2){
		int const l_row = row;
		return l_row;
	}else{
		return row + value;
	}
}

void visit(int **arr, int point_x, int point_y){
	printf("Current position: arr[ %d, %d ] | %d --> 0\n", point_x, point_y, arr[point_x][point_y]);
	life -= 0.5;
	trip -= arr[point_x][point_y] * N_F / 60.0 * 0.5;
	arr[point_x][point_y] = 0;
#ifdef DEBUG_MODE
	print_array(arr, Grid_Length, Grid_Height);
#elif TEST_MODE
	print_array(arr, Grid_Length, Grid_Height);
#endif
}


float zamboni(int **arr, int **cs_arr, int CS_num, int square_length, int x_base, int y_base){	//zamboni

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	char filename[100];
	snprintf(filename, sizeof(filename), "output/zamboni/result_%04d%02d%02d_%02d%02d%2d.txt", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	fp = fopen(filename, "w");
	if(fp == NULL){
		printf("Error: cannot open file\n");
		return 1;
	}

	zigzag(arr, cs_arr, CS_num, square_length, x_base, y_base, false);

//	printf("Battery Capacity: %f sec\n", life);
//	int start_row = 1;
//	int end_row = arr_height / 2;
//#ifdef DEBUG_MODE
//	printf("start_row: %d\n", start_row);
//	printf("end_row: %d\n", end_row);
//#endif
//#ifdef GRID_SIZE
//	printf("start_row: %d\n", start_row);
//	printf("end_row: %d\n", end_row);
//#endif
//	
//		
//	for(int i = 1; i < arr_length - 1; i++){
//		for(int j = 1; j < arr_height - 1; j++){
//
//			
//
//			visit(arr , i, j);
//		}
//
//	}
//
//	printf("Battery_life: %.4f\n", life);
//	printf("Pesticide_amount: %.4f\n", trip);
//	return 0;

	fclose(fp);
}

void zamboni_path(int **arr, int arr_length, int arr_height) {
    int direction = 1;  // 1 for right, -1 for left
    for (int i = 0; i < arr_length; i++) {
        if (direction == 1) {
            for (int j = 0; j < arr_height; j++) {
                printf("Visiting arr[%d][%d]\n", i, j);
                arr[i][j] = 0;  // Mark as visited
		print_array(arr, arr_length, arr_height);
            }
        } else {
            for (int j = arr_height - 1; j >= 0; j--) {
                printf("Visiting arr[%d][%d]\n", i, j);
                arr[i][j] = 0;  // Mark as visited
		print_array(arr, arr_length, arr_height);
            }
        }
        direction = -direction;  // Change direction for next row
    }
}
