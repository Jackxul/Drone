//spiral.h
#ifndef SPIRAL_H
#define SPIRAL_H

#include <common.h>
int is_valid(int **arr, int square_l, int cx, int cy, int dir, float *energy_consume, float *time_consume);	//check if the next position is valid(-1 or 0)
float spiral(int **arr, int **cs_arr, int CS_num, int square_length, int x_base, int y_base);	//spiral
								//
								//
#endif /* SPIRAL_H */
