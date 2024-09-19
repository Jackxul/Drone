//common.h
#ifndef COMMON_H
#define COMMON_H
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<time.h>
#include<stdarg.h>
#include<pthread.h>

extern FILE *fp;
extern FILE *sp_fp;


#ifdef TEST_MODE
	#define Grid_Length 10
	#define Grid_Height 10
#else
	#define Grid_Length 30
	#define Grid_Height 30
#endif

#define UNIQUE_GRID_NUMBER 1

#ifdef GRID_SIZE
	#undef Grid_Length
	#undef Grid_Height
	#undef UNIQUE_GRID_NUMBER
	#define Grid_Length GRID_SIZE
	#define Grid_Height GRID_SIZE
	#define UNIQUE_GRID_NUMBER GRID_SIZE //for setting random seed
#endif

#define PRIME1 31
#define PRIME2 37
#define Speed 2 /* (m/s) */		// = (1m/0.5s)
#define Droplet 330 /* (m^3/s) */
#define Height 5 /* (m) */
#define Spacing 1 /* (m) */
#define Battery_Capacity  116 /* (min) */
#define Battery_Voltage  52 /* (V) */
#define Battery_Weight  8 /* (kg) */
#define Battery_VM BVM //Battery Variable Max
#define Battery_VN BVN //Battery Variable Min
#define Pesticide 8 /* (L) */
#define N_F 0.61 /* (L/min) */
#define P_H_TCrop 47//Pesticide per Hectare for Test Crop
#define P_H_CCrop 1.5//Pesticide per Hectare for Current Crop
#define Battery_Ah 40 /* (Ah) */
#define Battery_Num 4 /* (number) */
#define Joules Battery_Voltage * Battery_Ah * 3600 * Battery_Num /* (J) */
#define Power_Watt 4292.7 /* (W) */

enum map_location{
	UP = 1,
	DOWN = 2,
	LEFT = 3,
	RIGHT = 4
};
enum cs_location{
	GRID_MIDDLE = 0,
	GRID_UP = 1,
	GRID_DOWN = 2,
	GRID_LEFT = 3,
	GRID_RIGHT = 4
};


// Declare the custom printf function
void JPrintf(const char *format, ...);
unsigned int combine_primes_with_time(unsigned int prime1, unsigned int prime2);
void set_random_seed();
double skewed_random(double min, double max, double skew_num);
int rand_time(int min, int max);
//sqrt
double distance(int x1, int y1, int x2, int y2);
//time calculate
void print_array(int **arr, int arr_length, int arr_height);
void set_charge_station(int **arr, int **cs_arr, int CS_num, int arr_length, int arr_height);
void set_current_speed(int *Current_Speed);
void find_nearest_cs(int *cs_arr, int CS_num, int arr_length, int arr_height, int point_cx, int point_cy, int *dx, int *dy);
void set_multi(double *time);
void fill_grid(int **arr, int square_l, int arr_length, int arr_height, bool boader_set);
#endif /* COMMON_H */
