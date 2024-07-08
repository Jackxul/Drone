#include <common.h>

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
    return (prime1 * prime2) ^ current_time; // XOR
}
void set_random_seed() {
	unsigned int seed = combine_primes_with_time(PRIME1, PRIME2);
	//set random seed
	srand(seed);
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
	int index = 0;
	int rand_temp = 0;
	switch(CS_num){
		case 1://select a direction ramdomly from single_cs array
		       	rand_temp = rand() % 4;
			cs_arr[index] = single_cs[rand_temp] * arr_length + rand() % (arr_height - 1);
			break;
		case 2:
			rand_temp = rand() % 6;
			cs_arr[index++] = double_cs[rand_temp][0] * arr_length + rand() % (arr_height - 1);
			cs_arr[index] = double_cs[rand_temp][1] * arr_length + rand() % (arr_height - 1);
			break;
		case 3:
			rand_temp = rand() % 4;
			cs_arr[index++] = triple_cs[rand_temp][0] * arr_length + rand() % (arr_height - 1);
			cs_arr[index++] = triple_cs[rand_temp][1] * arr_length + rand() % (arr_height - 1);
			cs_arr[index] = triple_cs[rand_temp][2] * arr_length + rand() % (arr_height - 1);
			break;
		default:
			printf("Error: CS_num is out of range\n");
			break;
	}
	for(int count = 0; count < CS_num; count++){
		int cs_position = cs_arr[count];
		if(cs_position / arr_length == 1){ 	//UP
			arr[0][cs_position % (arr_length - 1)] = -7;	
		}else if(cs_position / arr_length == 2){ //DOWN
			arr[arr_height - 1][cs_position % (arr_length - 1)] = -7;
		}else if(cs_position / arr_length == 3){ //LEFT
			arr[cs_position % (arr_length - 1) + 1][0] = -7;
		}else if(cs_position / arr_length == 4){ //RIGHT
			arr[cs_position % (arr_length - 1)][arr_height - 1] = -7;
		}else{
			printf("Error: CS_position is out of range\n");
			exit(0);
		}
	}
	
}
