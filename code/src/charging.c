#include <charging.h>

float single_zigzag_charge(int point_x, int point_y , int Current_Speed){
	float time = 0;
	time = distance(point_x, point_y, 1, 1); //charging station postion at ( 1 , 1 )
	time /= Current_Speed * 2; 
	printf("debug single charge\n");
	return time;
}
float multi_zigzag_charge(int point_cx, int point_cy, int point_dx, int point_dy, int Current_Speed){

	float time = 0;
	time = distance(point_cx, point_cy, point_dx, point_dy); //charging station postion at ( point_dx , point_dy )
	time /= Current_Speed * 2;
	printf("debug multi charge\n");
	return time;
}
