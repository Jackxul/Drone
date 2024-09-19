#include <common.h>


FILE *fp;
FILE *sp_fp;

// Declare the custom printf function
void JPrintf(const char *format, ...) {
    va_list args;

    // Print to console
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    // Print to file
    if (fp) {
        va_start(args, format);
        vfprintf(fp, format, args);
        va_end(args);
    }
    //if(sp_fp){
    //    va_start(args, format);
    //    vfprintf(sp_fp, format, args);
    //    va_end(args);
    //}
}
int single_cs[4] = {
	UP,
	DOWN,
	LEFT,
	RIGHT
};
int double_cs[6][2] = {
	{UP,DOWN},
	{UP,LEFT},
	{UP,RIGHT},
	{DOWN,LEFT},
	{DOWN,RIGHT},
	{LEFT,RIGHT}
};
int triple_cs[4][3] = {
	{UP,DOWN,LEFT},
	{UP,DOWN,RIGHT},
	{UP,LEFT,RIGHT},
	{DOWN,LEFT,RIGHT}
};

unsigned int combine_primes_with_time(unsigned int prime1, unsigned int prime2) {
	//get current time
	unsigned int current_time = (unsigned int)time(NULL);
	//combine two prime numbers with current time
    return ((prime1 * prime2) ^ current_time) * UNIQUE_GRID_NUMBER; // XOR
}
void set_random_seed() {
	unsigned int seed = combine_primes_with_time(PRIME1, PRIME2);
	//set random seed
	srand(seed);
}
double skewed_random(double min, double max, double skew_num){

	double rand_r = (double)rand() / RAND_MAX; // 0 ~ 1
	// Apply logarithmic scaling to the grid value for wider range control
    // This makes the skew effect grow smoothly with larger grid values
    double skew_factor = log1p(skew_num) / 9.0;  // Use log1p for stability at small grid values					

	rand_r = pow(rand_r, skew_factor); // Skew the random number
	return min + rand_r * (max - min);
}
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
void print_array(int **arr, int arr_length, int arr_height){
	for(int i = 0; i < arr_length; i++){
		for(int j = 0; j < arr_height; j++){
			printf("%2d ", arr[i][j]);
		}
		printf("\n");
	}
}
void set_charge_station(int **arr, int **cs_arr, int CS_num, int arr_length, int square_l){
/*
 *up 	--> 1
 *down	--> 2
 *left	--> 3
 *right	--> 4
 */	
	int index = 0;
	int rand_temp = 0;
	// n * arr_length + 0 ~ arr_length - 1 //預留一位給下一個方向當起始頭
	switch(CS_num){
		case 1://select a direction ramdomly from single_cs array
		       	rand_temp = rand() % 4;
			cs_arr[GRID_MIDDLE][index] = single_cs[rand_temp] * arr_length + (rand() % (arr_length - 1));
			break;
		case 2:
			rand_temp = rand() % 6;
			cs_arr[GRID_MIDDLE][index++] = double_cs[rand_temp][0] * arr_length + (rand() % (arr_length - 1));
			cs_arr[GRID_MIDDLE][index] = double_cs[rand_temp][1] * arr_length + (rand() % (arr_length - 1));
			break;
		case 3:
			rand_temp = rand() % 4;
			cs_arr[GRID_MIDDLE][index++] = triple_cs[rand_temp][0] * arr_length + (rand() % (arr_length - 1));
			cs_arr[GRID_MIDDLE][index++] = triple_cs[rand_temp][1] * arr_length + (rand() % (arr_length - 1));
			cs_arr[GRID_MIDDLE][index] = triple_cs[rand_temp][2] * arr_length + (rand() % (arr_length - 1));
			break;
		default:
			printf("Error: charging station num is out of range\n");
			exit(0);
	}
	//set charging station position for MIDDLE GRID 	DONE
	for(int count = 0; count < CS_num; count++){
		int cs_position = cs_arr[GRID_MIDDLE][count];
		if(cs_position / arr_length == UP){
			arr[arr_length - 1][cs_position % (arr_length - 1) + arr_length] = -8;
			cs_arr[GRID_UP][0] = cs_position;
			printf("\n temp UP \n");
		}else if(cs_position / arr_length == DOWN){
			arr[2 * (arr_length - 1)][cs_position % (arr_length - 1) + arr_length - 1] = -8;
			cs_arr[GRID_DOWN][0] = cs_position;
			printf("\n temp DOWN \n");
		}else if(cs_position / arr_length == LEFT){
			arr[cs_position % (arr_length - 1) + arr_length - 1][arr_length - 1] = -8;
			cs_arr[GRID_LEFT][0] = cs_position;
			printf("\n temp LEFT \n");
			printf("coount now is = %d\n", count);
		}else if(cs_position / arr_length == RIGHT){
			arr[cs_position % (arr_length - 1) + arr_length][2 * (arr_length - 1)] = -8;
			cs_arr[GRID_RIGHT][0] = cs_position;
			printf("\n temp RIGHT \n");
		}else{
			printf("Error: charging station position is out of range\n");
			//exit(0);
		}
	}
	//set charging station position for UP GRID
	//set the current side as number 0
	if(cs_arr[GRID_UP][0] != -1){
		//down occupied
		int temp_double_dice[3] = {UP,LEFT,RIGHT};	//1,3,4
		int temp_triple_dice[3][2] = {
			{UP,LEFT},	//1,3
			{UP,RIGHT},	//1,4
			{LEFT,RIGHT}	//3,4
		};
		if(CS_num == 2){	//set one more charging station
			rand_temp = rand() % 3;	//0,1,2
			cs_arr[GRID_UP][1] = temp_double_dice[rand_temp] * arr_length + (rand() % (arr_length - 1));
			if(temp_double_dice[rand_temp] / 3 != 0){ //LEFT or RIGHT
				arr[cs_arr[GRID_UP][1] % arr_length + (temp_double_dice[rand_temp] / 4)][(arr_length - 1) * (temp_double_dice[rand_temp] / 2)] = -8;	//左邊從高度0開始 右邊從高度1開始	
			}else{ //UP
				arr[0][(cs_arr[GRID_UP][1] % arr_length) + arr_length] = -8;	//上面從寬度1開始
			}
		}else if(CS_num == 3){	//set two more charging station
			rand_temp = rand() % 3;	//0,1,2
			cs_arr[GRID_UP][1] = temp_triple_dice[rand_temp][0] * arr_length + (rand() % (arr_length - 1));
			cs_arr[GRID_UP][2] = temp_triple_dice[rand_temp][1] * arr_length + (rand() % (arr_length - 1));
			if(temp_triple_dice[rand_temp][0] / 3 && temp_triple_dice[rand_temp][1] / 3 != 0){ //LEFT AND RIGHT
				arr[cs_arr[GRID_UP][1] % arr_length + (temp_triple_dice[rand_temp][0] / 4)][(arr_length - 1) * (temp_triple_dice[rand_temp][0] / 2)] = -8;	//左邊從高度0開始 右邊從高度1開始	
				arr[cs_arr[GRID_UP][2] % arr_length + (temp_triple_dice[rand_temp][1] / 4)][(arr_length - 1) * (temp_triple_dice[rand_temp][1] / 2)] = -8;	//左邊從高度0開始 右邊從高度1開始
			}else{	//有上的充電站 (上跟左右的共通式)
				arr[(temp_triple_dice[rand_temp][0] / 3) * (cs_arr[GRID_UP][1] % arr_length) + (temp_triple_dice[rand_temp][0] / 4)][arr_length - 1 + (1 - (temp_triple_dice[rand_temp][0] / 3)) * (cs_arr[GRID_UP][1] % arr_length + 1) + ((temp_triple_dice[rand_temp][0] & 4) / 4 * (arr_length - 1))] = -8;
				arr[(temp_triple_dice[rand_temp][1] / 3) * (cs_arr[GRID_UP][2] % arr_length) + (temp_triple_dice[rand_temp][1] / 4)][arr_length - 1 + (1 - (temp_triple_dice[rand_temp][1] / 3)) * (cs_arr[GRID_UP][2] % arr_length + 1) + ((temp_triple_dice[rand_temp][1] & 4) / 4 * (arr_length - 1))] = -8;
			}

		//	arr[temp_triple_dice[rand_temp]][] = -8;
		//	arr[][] = -8;
		}
		printf("debug1\n");
	}else{	

		printf("debug2\n");
		//rand from up, left, right 1,3,4
		int temp_single_dice[3] = {UP,LEFT,RIGHT};
		//rand from up-left, up-right, left-right 1 + 3, 1 + 4, 3 + 4
		int temp_double_dice[3][2] = {
			{UP,LEFT},
			{UP,RIGHT},
			{LEFT,RIGHT}
		};
		rand_temp = rand() % 3;
		switch(CS_num){
			case 1:
				cs_arr[GRID_UP][0] = temp_single_dice[rand_temp] * arr_length + (rand() % (arr_length - 1));
				arr[(temp_single_dice[rand_temp] / 3) * (cs_arr[GRID_UP][0] % arr_length) + (temp_single_dice[rand_temp] / 4)][arr_length - 1 + (1 - (temp_single_dice[rand_temp] / 3)) * (cs_arr[GRID_UP][0] % arr_length + 1) + ((temp_single_dice[rand_temp] & 4) / 4 * (arr_length - 1))] = -8; //上跟左右的共通式
				break;
			case 2:
				cs_arr[GRID_UP][0] = temp_double_dice[rand_temp][0] * arr_length + (rand() % (arr_length - 1));
				cs_arr[GRID_UP][1] = temp_double_dice[rand_temp][1] * arr_length + (rand() % (arr_length - 1));
				arr[(temp_double_dice[rand_temp][0] / 3) * (cs_arr[GRID_UP][0] % arr_length) + (temp_double_dice[rand_temp][0] / 4)][arr_length - 1 + (1 - (temp_double_dice[rand_temp][0] / 3)) * (cs_arr[GRID_UP][0] % arr_length + 1) + ((temp_double_dice[rand_temp][0] & 4) / 4 * (arr_length - 1))] = -8; //上跟左右的共通式
				arr[(temp_double_dice[rand_temp][1] / 3) * (cs_arr[GRID_UP][1] % arr_length) + (temp_double_dice[rand_temp][1] / 4)][arr_length - 1 + (1 - (temp_double_dice[rand_temp][1] / 3)) * (cs_arr[GRID_UP][1] % arr_length + 1) + ((temp_double_dice[rand_temp][1] & 4) / 4 * (arr_length - 1))] = -8; //上跟左右的共通式
				break;
			case 3:
				//rand from up-left-right 1 + 3 + 4
				cs_arr[GRID_UP][0] = UP * arr_length + (rand() % (arr_length - 1));
				cs_arr[GRID_UP][1] = LEFT * arr_length + (rand() % (arr_length - 1));
				cs_arr[GRID_UP][2] = RIGHT * arr_length + (rand() % (arr_length - 1));
				arr[0][cs_arr[GRID_UP][0] % arr_length + arr_length] = -8;	//上面從寬度1開始
				arr[cs_arr[GRID_UP][1] % arr_length][arr_length - 1] = -8;	//左邊從高度0開始
				arr[cs_arr[GRID_UP][2] % arr_length + 1][2 * (arr_length - 1)] = -8;	//右邊從高度1開始
				break;
			default:
				break;
		}
	}
	//set charging station position for DOWN GRID
	if(cs_arr[GRID_DOWN][0] != -1){
		printf("debug 3\n");
		//up occupied
		int temp_double_dice[3] = {DOWN,LEFT,RIGHT};	//2,3,4
		int temp_triple_dice[3][2] = {
			{DOWN,LEFT},	//2,3
			{DOWN,RIGHT},	//2,4
			{LEFT,RIGHT}	//3,4
		};
		if(CS_num == 2){	//set one more charging station
			rand_temp = rand() % 3;	//0,1,2
			cs_arr[GRID_DOWN][1] = temp_double_dice[rand_temp] * arr_length + (rand() % (arr_length - 1));
			if(temp_double_dice[rand_temp] / 3 != 0){ //LEFT or RIGHT
				arr[cs_arr[GRID_DOWN][1] % arr_length + (2 * (arr_length - 1)) + (temp_double_dice[rand_temp] / 4)][(arr_length - 1) * (temp_double_dice[rand_temp] / 2)] = -8;	//左邊從高度0開始 右邊從高度1開始	
			}else{ //DOWN
				arr[3 * (arr_length - 1)][(cs_arr[GRID_DOWN][1] % arr_length) + arr_length] = -8;	//下面從寬度0開始
			}
		}else if(CS_num == 3){	//set two more charging station
			rand_temp = rand() % 3;	//0,1,2
			cs_arr[GRID_DOWN][1] = temp_triple_dice[rand_temp][0] * arr_length + (rand() % (arr_length - 1));
			cs_arr[GRID_DOWN][2] = temp_triple_dice[rand_temp][1] * arr_length + (rand() % (arr_length - 1));
			if(temp_triple_dice[rand_temp][0] / 3 && temp_triple_dice[rand_temp][1] / 3 != 0){ //LEFT AND RIGHT
				arr[cs_arr[GRID_DOWN][1] % arr_length + (2 * (arr_length - 1)) + (temp_triple_dice[rand_temp][0] / 4)][(arr_length - 1) * (temp_triple_dice[rand_temp][0] / 2)] = -8;	//左邊從高度0開始 右邊從高度1開始	
				arr[cs_arr[GRID_DOWN][2] % arr_length + (2 * (arr_length - 1)) + (temp_triple_dice[rand_temp][1] / 4)][(arr_length - 1) * (temp_triple_dice[rand_temp][1] / 2)] = -8;	//左邊從高度0開始 右邊從高度1開始
			}else{	//有下的充電站 (下跟左右的共通式)
				arr[((3 - (temp_triple_dice[rand_temp][0] / 3)) * (arr_length - 1)) + (temp_triple_dice[rand_temp][0] / 3) * (cs_arr[GRID_DOWN][1] % arr_length) + (temp_triple_dice[rand_temp][0] / 4)][(temp_triple_dice[rand_temp][0] / 2) * (arr_length - 1) + ((1 - (temp_triple_dice[rand_temp][0] / 3)) * (cs_arr[GRID_DOWN][1] % arr_length))] = -8;
				arr[((3 - (temp_triple_dice[rand_temp][1] / 3)) * (arr_length - 1)) + (temp_triple_dice[rand_temp][1] / 3) * (cs_arr[GRID_DOWN][2] % arr_length) + (temp_triple_dice[rand_temp][1] / 4)][(temp_triple_dice[rand_temp][1] / 2) * (arr_length - 1) + ((1 - (temp_triple_dice[rand_temp][1] / 3)) * (cs_arr[GRID_DOWN][2] % arr_length))] = -8;
			}
		}
	}else{
		//rand from down, left, right 2,3,4
		int temp_single_dice[3] = {DOWN,LEFT,RIGHT};
		//rand from down-left, down-right, left-right 2 + 3, 2 + 4, 3 + 4
		int temp_double_dice[3][2] = {
			{DOWN,LEFT},
			{DOWN,RIGHT},
			{LEFT,RIGHT}
		};
		rand_temp = rand() % 3;
		switch(CS_num){
			case 1:
				cs_arr[GRID_DOWN][0] = temp_single_dice[rand_temp] * arr_length + (rand() % (arr_length - 1));
				arr[(3 - (temp_single_dice[rand_temp] / 3)) * (arr_length - 1) + (temp_single_dice[rand_temp] / 3) * (cs_arr[GRID_DOWN][0] % arr_length) + (temp_single_dice[rand_temp] / 4)][(temp_single_dice[rand_temp] / 2) * (arr_length - 1) + ((1 - (temp_single_dice[rand_temp] / 3)) * (cs_arr[GRID_DOWN][0] % arr_length))] = -8; //下跟左右的共通式
				break;
			case 2:
				cs_arr[GRID_DOWN][0] = temp_double_dice[rand_temp][0] * arr_length + (rand() % (arr_length - 1));
				cs_arr[GRID_DOWN][1] = temp_double_dice[rand_temp][1] * arr_length + (rand() % (arr_length - 1));
				arr[((3 - (temp_double_dice[rand_temp][0] / 3)) * (arr_length - 1)) + (temp_double_dice[rand_temp][0] / 3) * (cs_arr[GRID_DOWN][0] % arr_length) + (temp_double_dice[rand_temp][0] / 4)][(temp_double_dice[rand_temp][0] / 2) * (arr_length - 1) + ((1 - (temp_double_dice[rand_temp][0] / 3)) * (cs_arr[GRID_DOWN][0] % arr_length))] = -8; //下跟左右的共通式
				arr[((3 - (temp_double_dice[rand_temp][1] / 3)) * (arr_length - 1)) + (temp_double_dice[rand_temp][1] / 3) * (cs_arr[GRID_DOWN][1] % arr_length) + (temp_double_dice[rand_temp][1] / 4)][(temp_double_dice[rand_temp][1] / 2) * (arr_length - 1) + ((1 - (temp_double_dice[rand_temp][1] / 3)) * (cs_arr[GRID_DOWN][1] % arr_length))] = -8; //下跟左右的共通式
				break;
			case 3:
				//rand from down-left-right 2 + 3 + 4
				cs_arr[GRID_DOWN][0] = DOWN * arr_length + (rand() % (arr_length - 1));
				cs_arr[GRID_DOWN][1] = LEFT * arr_length + (rand() % (arr_length - 1));
				cs_arr[GRID_DOWN][2] = RIGHT * arr_length + (rand() % (arr_length - 1));
				arr[3 * (arr_length - 1)][cs_arr[GRID_DOWN][0] % arr_length + arr_length] = -8;	//下面從寬度0開始
				arr[cs_arr[GRID_DOWN][1] % arr_length][arr_length - 1] = -8;	//左邊從高度0開始
				arr[cs_arr[GRID_DOWN][2] % arr_length + 1][2 * (arr_length - 1)] = -8;	//右邊從高度1開始
				break;
			default:
				break;
		}
		printf("SET DOWN GRID\n");
	}
	printf("debug 4\n");
	//set charging station position for LEFT GRID
	if(cs_arr[GRID_LEFT][0] != -1){
		//right occupied
		int temp_double_dice[3] = {UP,DOWN,LEFT};	//1,2,3
		int temp_triple_dice[3][2] = {
			{UP,DOWN},	//1,2
			{UP,LEFT},	//1,3
			{DOWN,LEFT}	//2,3
		};
		if(CS_num == 2){	//set one more charging station
			rand_temp = rand() % 3;	//0,1,2
			cs_arr[GRID_LEFT][1] = temp_double_dice[rand_temp] * arr_length + (rand() % (arr_length - 1));
			if(temp_double_dice[rand_temp] / 3 == 0){ //UP or DOWN
				arr[(arr_length - 1) * temp_double_dice[rand_temp]][cs_arr[GRID_LEFT][1] % arr_length + 1 - (temp_double_dice[rand_temp] / 2)] = -8;	//上面從寬度1開始 下面從寬度0開始	
			}else{ //LEFT
				arr[cs_arr[GRID_LEFT][1] % arr_length + (arr_length - 1)][0] = -8;	//左邊從高度0開始
			}
		}else if(CS_num == 3){	//set two more charging station
			rand_temp = rand() % 3;	//0,1,2
			cs_arr[GRID_LEFT][1] = temp_triple_dice[rand_temp][0] * arr_length + (rand() % (arr_length - 1));
			cs_arr[GRID_LEFT][2] = temp_triple_dice[rand_temp][1] * arr_length + (rand() % (arr_length - 1));
			if(temp_triple_dice[rand_temp][0] / 3 && temp_triple_dice[rand_temp][1] / 3 == 0){ //UP AND DOWN
				arr[temp_triple_dice[rand_temp][0] * (arr_length - 1)][cs_arr[GRID_LEFT][1] % arr_length + 1 - (temp_triple_dice[rand_temp][0] / 2)] = -8;	//上面從寬度1開始 下面從寬度0開始
				arr[temp_triple_dice[rand_temp][1] * (arr_length - 1)][cs_arr[GRID_LEFT][2] % arr_length + 1 - (temp_triple_dice[rand_temp][1] / 2)] = -8;	//上面從寬度1開始 下面從寬度0開始
			}else{	//有左的充電站 (左跟上下的共通式)
				arr[(temp_triple_dice[rand_temp][0] / 3) * (cs_arr[GRID_LEFT][1] % arr_length) + ((arr_length - 1) * ((2 - temp_triple_dice[rand_temp][0] % 2)))][((1 - (temp_triple_dice[rand_temp][0] / 3)) * (cs_arr[GRID_LEFT][1] % arr_length)) + (1 - (temp_triple_dice[rand_temp][0] / 2))] = -8;
				arr[(temp_triple_dice[rand_temp][1] / 3) * (cs_arr[GRID_LEFT][2] % arr_length) + ((arr_length - 1) * ((2 - temp_triple_dice[rand_temp][1] % 2)))][((1 - (temp_triple_dice[rand_temp][1] / 3)) * (cs_arr[GRID_LEFT][2] % arr_length)) + (1 - (temp_triple_dice[rand_temp][1] / 2))] = -8;
			}
		}
	}else{
		//rand from up, down, left 1,2,3
		int temp_single_dice[3] = {UP,DOWN,LEFT};
		//rand from up-down, up-left, down-left 1 + 2, 1 + 3, 2 + 3	
		int temp_double_dice[3][2] = {
			{UP,DOWN},
			{UP,LEFT},
			{DOWN,LEFT}
		};
		rand_temp = rand() % 3;
		switch(CS_num){
			case 1:
				cs_arr[GRID_LEFT][0] = temp_single_dice[rand_temp] * arr_length + (rand() % (arr_length - 1));
				arr[(temp_single_dice[rand_temp] / 3) * (cs_arr[GRID_LEFT][0] % arr_length) + ((arr_length - 1) * ((2 - temp_single_dice[rand_temp] % 2)))][((1 - (temp_single_dice[rand_temp] / 3)) * (cs_arr[GRID_LEFT][0] % arr_length)) + (1 - (temp_single_dice[rand_temp] / 2))] = -8;
				break;
			case 2:
				cs_arr[GRID_LEFT][0] = temp_double_dice[rand_temp][0] * arr_length + (rand() % (arr_length - 1));
				cs_arr[GRID_LEFT][1] = temp_double_dice[rand_temp][1] * arr_length + (rand() % (arr_length - 1));
				arr[(temp_double_dice[rand_temp][0] / 3) * (cs_arr[GRID_LEFT][0] % arr_length) + ((arr_length - 1) * ((2 - temp_double_dice[rand_temp][0] % 2)))][((1 - (temp_double_dice[rand_temp][0] / 3)) * (cs_arr[GRID_LEFT][0] % arr_length)) + (1 - (temp_double_dice[rand_temp][0] / 2))] = -8;
				arr[(temp_double_dice[rand_temp][1] / 3) * (cs_arr[GRID_LEFT][1] % arr_length) + ((arr_length - 1) * ((2 - temp_double_dice[rand_temp][1] % 2)))][((1 - (temp_double_dice[rand_temp][1] / 3)) * (cs_arr[GRID_LEFT][1] % arr_length)) + (1 - (temp_double_dice[rand_temp][1] / 2))] = -8;

				break;
			case 3:
				//rand from up-down-left 1 + 2 + 3
				cs_arr[GRID_LEFT][0] = UP * arr_length + (rand() % (arr_length - 1));
				cs_arr[GRID_LEFT][1] = DOWN * arr_length + (rand() % (arr_length - 1));
				cs_arr[GRID_LEFT][2] = LEFT * arr_length + (rand() % (arr_length - 1));
				arr[cs_arr[GRID_LEFT][0] % arr_length + arr_length][(arr_length - 1)] = -8;	//上面從寬度1開始
				arr[cs_arr[GRID_LEFT][1] % arr_length + 2 * (arr_length - 1)][(arr_length - 1)] = -8;	//下面從寬度0開始
				arr[cs_arr[GRID_LEFT][2] % arr_length + arr_length - 1][0] = -8;	//左邊從高度29開始
				break;
			default:
				break;
		}
		printf("SET LEFT GRID\n");
	}
	printf("debug 5\n");
	//set charging station position for RIGHT GRID
	printf("debug = %d\n", cs_arr[GRID_UP][0]);
	printf("debug = %d\n", cs_arr[GRID_DOWN][0]);
	printf("debug = %d\n", cs_arr[GRID_LEFT][0]);
	printf("debug = %d\n", cs_arr[GRID_RIGHT][0]);

	if(cs_arr[GRID_RIGHT][0] != -1){
	printf("debug 6\n");
		//left occupied
		int temp_double_dice[3] = {UP,DOWN,RIGHT};	//1,2,4
		int temp_triple_dice[3][2] = {
			{UP,DOWN},	//1,2
			{UP,RIGHT},	//1,4
			{DOWN,RIGHT}	//2,4
		};
		if(CS_num == 2){	//set one more charging station
			rand_temp = rand() % 3;	//0,1,2
			cs_arr[GRID_RIGHT][1] = temp_double_dice[rand_temp] * arr_length + (rand() % (arr_length - 1));
			if(temp_double_dice[rand_temp] / 3 == 0){ //UP or DOWN
				arr[(arr_length - 1) * temp_double_dice[rand_temp]][2 * (arr_length - 1) + cs_arr[GRID_RIGHT][1] % arr_length + 1 - (temp_double_dice[rand_temp] / 2)] = -8;	//上面從寬度1開始 下面從寬度0開始	
			}else{ //RIGHT
				arr[cs_arr[GRID_RIGHT][1] % arr_length + (arr_length - 1) + (temp_double_dice[rand_temp] / 4)][3 * (arr_length - 1)] = -8;	//右邊從高度1開始
			}
		}else if(CS_num == 3){	//set two more charging station
			printf("debug 7\n");
			rand_temp = rand() % 3;	//0,1,2
			cs_arr[GRID_RIGHT][1] = temp_triple_dice[rand_temp][0] * arr_length + (rand() % (arr_length - 1));
			cs_arr[GRID_RIGHT][2] = temp_triple_dice[rand_temp][1] * arr_length + (rand() % (arr_length - 1));
			if(temp_triple_dice[rand_temp][0] / 3 && temp_triple_dice[rand_temp][1] / 3 == 0){ //UP AND DOWN
	printf("debug 8\n");
				arr[temp_triple_dice[rand_temp][0] * (arr_length - 1)][2 * (arr_length - 1) + (cs_arr[GRID_RIGHT][1] % arr_length) + 1 - (temp_triple_dice[rand_temp][0] / 2)] = -8;	//上面從寬度1開始 下面從寬度0開始
				arr[temp_triple_dice[rand_temp][1] * (arr_length - 1)][2 * (arr_length - 1) + (cs_arr[GRID_RIGHT][2] % arr_length) + 1 - (temp_triple_dice[rand_temp][1] / 2)] = -8;	//上面從寬度1開始 下面從寬度0開始
			}else{	//有右的充電站 (右跟上下的共通式)
	printf("debug 9\n");
				arr[(temp_triple_dice[rand_temp][0] / 4) * (cs_arr[GRID_RIGHT][1] % arr_length) + ((temp_triple_dice[rand_temp][0] % 3) * (arr_length - 1)) + (temp_triple_dice[rand_temp][0] / 4)][((1 - (temp_triple_dice[rand_temp][0] / 4)) * cs_arr[GRID_RIGHT][1] % arr_length) + (temp_triple_dice[rand_temp][0] % 2) + ((arr_length - 1) * (2 + (temp_triple_dice[rand_temp][0] / 4)))]= -8; //右邊從高度1開始 上面從寬度1開始 下面從寬度0開始
				arr[(temp_triple_dice[rand_temp][1] / 4) * (cs_arr[GRID_RIGHT][2] % arr_length) + ((temp_triple_dice[rand_temp][1] % 3) * (arr_length - 1)) + (temp_triple_dice[rand_temp][1] / 4)][((1 - (temp_triple_dice[rand_temp][1] / 4)) * cs_arr[GRID_RIGHT][2] % arr_length) + (temp_triple_dice[rand_temp][1] % 2) + ((arr_length - 1) * (2 + (temp_triple_dice[rand_temp][1] / 4)))]= -8; //右邊從高度1開始 上面從寬度1開始 下面從寬度0開始
			}
		}
	}else{
		printf("debug 10\n");
		//rand from up, down, right 1,2,4
		int temp_single_dice[3] = {UP,DOWN,RIGHT};
		//rand from up-down, up-right, down-right 1 + 2, 1 + 4, 2 + 4
		int temp_double_dice[3][2] = {
			{UP,DOWN},
			{UP,RIGHT},
			{DOWN,RIGHT}
		};
		rand_temp = rand() % 3;
		switch(CS_num){
			case 1:
				cs_arr[GRID_RIGHT][0] = temp_single_dice[rand_temp] * arr_length + (rand() % (arr_length - 1));
				arr[(temp_single_dice[rand_temp] / 3) * (cs_arr[GRID_RIGHT][0] % arr_length) + ((temp_single_dice[rand_temp] % 3) * (arr_length - 1)) + (temp_single_dice[rand_temp] / 4)][((1 - (temp_single_dice[rand_temp] / 3)) * cs_arr[GRID_RIGHT][0] % arr_length) + (temp_single_dice[rand_temp] % 2) + ((arr_length - 1) * (2 + (temp_single_dice[rand_temp] / 4)))] = -8; //右跟上下的共通式
				break;
			case 2:
				cs_arr[GRID_RIGHT][0] = temp_double_dice[rand_temp][0] * arr_length + (rand() % (arr_length - 1));
				cs_arr[GRID_RIGHT][1] = temp_double_dice[rand_temp][1] * arr_length + (rand() % (arr_length - 1));
				arr[(temp_double_dice[rand_temp][0] / 3) * (cs_arr[GRID_RIGHT][0] % arr_length) + ((temp_double_dice[rand_temp][0] % 3) * (arr_length - 1)) + (temp_double_dice[rand_temp][0] / 4)][((1 - (temp_double_dice[rand_temp][0] / 3)) * cs_arr[GRID_RIGHT][0] % arr_length) + (temp_double_dice[rand_temp][0] % 2) + ((arr_length - 1) * (2 + (temp_double_dice[rand_temp][0] / 4)))] = -8; //右跟上下的共通式
				arr[(temp_double_dice[rand_temp][1] / 3) * (cs_arr[GRID_RIGHT][1] % arr_length) + ((temp_double_dice[rand_temp][1] % 3) * (arr_length - 1)) + (temp_double_dice[rand_temp][1] / 4)][((1 - (temp_double_dice[rand_temp][1] / 3)) * cs_arr[GRID_RIGHT][1] % arr_length) + (temp_double_dice[rand_temp][1] % 2) + ((arr_length - 1) * (2 + (temp_double_dice[rand_temp][1] / 4)))] = -8; //右跟上下的共通式
				break;
			case 3:
				printf("debug 11\n");
				//rand from up-down-right 1 + 2 + 4
				cs_arr[GRID_RIGHT][0] = UP * arr_length + (rand() % (arr_length - 1));
		printf("debug 12\n");
				cs_arr[GRID_RIGHT][1] = DOWN * arr_length + (rand() % (arr_length - 1));
		printf("debug 13\n");
				cs_arr[GRID_RIGHT][2] = RIGHT * arr_length + (rand() % (arr_length - 1));
		printf("debug 14\n");
				arr[UP * (arr_length - 1)][cs_arr[GRID_RIGHT][0] % arr_length + 1 - (UP / 2)] = -8;	//上面從寬度1開始
		printf("debug 15\n");
				arr[DOWN * (arr_length - 1)][cs_arr[GRID_RIGHT][1] % arr_length + 1 - (DOWN / 2)] = -8;	//下面從寬度0開始
		printf("debug 16\n");
				arr[arr_length - 1 + (cs_arr[GRID_RIGHT][2] % arr_length) + 1][3 * (arr_length - 1)] = -8;
		printf("debug 17\n");
				break;
			default:
				break;
		}
		printf("SET RIGHT GRID\n");
	}
	
}
void set_current_speed(int *Current_Speed){
	int const charging_speed = 10;
	int const spraying_speed = 2;
	
	if(*Current_Speed == spraying_speed){
		*Current_Speed = charging_speed;
	}else if(*Current_Speed == charging_speed){
		*Current_Speed = spraying_speed;
	}else{
		printf("Error: Current_Speed is out of range\n");
		exit(0);
	}
}
void find_nearest_cs(int *cs_arr, int CS_num, int arr_length, int arr_height,int point_cx, int point_cy, int *dx, int *dy){
	int temp_dx = 0;
	int temp_dy = 0;
	float cs_distance = distance( 0 , 0 , arr_length - 1 , arr_height - 1);
	float temp_distance = 0;
	for(int count = 0; count < CS_num; count++){
		if(cs_arr[count] / arr_length == UP){
			temp_distance = distance( point_cx , point_cy , 0 , cs_arr[count] % (arr_length - 1) );
			temp_dx = 0;
			temp_dy = cs_arr[count] % (arr_length - 1);
		}else if(cs_arr[count] / arr_length == DOWN){
			temp_distance = distance( point_cx , point_cy , arr_height - 1 , cs_arr[count] % (arr_length - 1) + 1 );
			temp_dx = arr_height - 1;
			temp_dy = cs_arr[count] % (arr_length - 1) + 1;
		}else if(cs_arr[count] / arr_length == LEFT){
			temp_distance = distance( point_cx , point_cy , cs_arr[count] % (arr_length - 1) + 1 , 0 );
			temp_dx = cs_arr[count] % (arr_length - 1) + 1;
			temp_dy = 0;
		}else{ //RIGHT
			temp_distance = distance( point_cx , point_cy , cs_arr[count] % (arr_length - 1) , arr_height - 1 );
			temp_dx = cs_arr[count] % (arr_length - 1);
			temp_dy = arr_length - 1;
		}

		if(temp_distance <= cs_distance){
			cs_distance = temp_distance;
			*dx = temp_dx;
			*dy = temp_dy;
		}
	}
}
void set_multi(double *time){
	printf("time = %f\n", *time);
	printf("UNIQUE_GRID_NUMBER = %d\n", UNIQUE_GRID_NUMBER);
	printf("skewed_random(BVN, BVM, UNIQUE_GRID_NUMBER) = %f\n", skewed_random(BVN, BVM, UNIQUE_GRID_NUMBER));
	*time *= skewed_random(BVN, BVM, UNIQUE_GRID_NUMBER);

	//*time *= Battery_Multi;
}

void fill_grid(int **arr, int square_l, int arr_length, int arr_height, bool boader_set) {
    for (int i = 0; i < square_l; i++) {
        for (int j = 0; j < square_l; j++) {
            // 邊界檢查
        	if (i == 0 || i == arr_length - 1 || i == 2 * arr_length - 2 ||
                i == 3 * arr_length - 3 || j == 0 || j == arr_height - 1 ||
                j == 2 * arr_height - 2 || j == 3 * arr_height - 3) {
			((boader_set == 'true') ? (arr[i][j] = -1) : (arr[i][j] = ((arr[i][j] == -1) ? -1 : -8)));
			arr[i][j] = -1;
            // 雙噴區域檢查
            	} else if ((i > 0 && i <= 2) || (i < arr_length - 1 && i >= arr_length - 3) ||
                       (i >= arr_length && i < arr_length + 2) || 
                       (i >= 2 * arr_length - 4 && i < 2 * arr_length - 2) ||
                       (i >= 2 * arr_length - 1 && i < 2 * arr_length + 1) ||
                       (i >= 3 * arr_length - 5 && i < 3 * arr_length - 3) ||
                       (j > 0 && j <= 2) || (j < arr_height - 1 && j >= arr_height - 3) ||
                       (j >= arr_height && j < arr_height + 2) ||
                       (j >= 2 * arr_height - 4 && j < 2 * arr_height - 2) ||
                       (j >= 2 * arr_height - 1 && j < 2 * arr_height + 1) ||
                       (j >= 3 * arr_height - 5 && j < 3 * arr_height - 3)) {
                	arr[i][j] = 2;
            // 單噴區域
            	} else {
                	arr[i][j] = 1;
            	}
        	}
	}
}

