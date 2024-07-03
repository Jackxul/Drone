//common.h
#ifndef COMMON_H
#define COMMON_H
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<time.h>

#ifdef TEST_MODE
#define Grid_Length 10
#define Grid_Height 10
#else
#define Grid_Length 30
#define Grid_Height 30
#endif
#ifdef GRID_SIZE
#define Grid_Length GRID_SIZE
#define Grid_Height GRID_SIZE
#endif
#define Speed 2 /* (m/s) */		// = (1m/0.5s)
#define Droplet 330 /* (m^3/s) */
#define Height 5 /* (m) */
#define Spacing 1 /* (m) */
#define Battery_Capacity  116 /* (min) */
#define Battery_Voltage  52 /* (V) */
#define Battery_Weight  8 /* (kg) */
#define Battery_V BV //Battery Variable
#define UAV_Postion_up 1
#define UAV_Postion_down 2
#define UAV_Postion_left 3
#define UAV_Postion_right 4
#define Pesticide 8 /* (L) */
#define N_F 0.66 /* (L/min) */


int rand_time(int min, int max);
//sqrt
double distance(int x1, int y1, int x2, int y2);
//time calculate
float route_time(double route, int speed);
void print_array(int **arr, int arr_length, int arr_height);

#endif /* COMMON_H */
