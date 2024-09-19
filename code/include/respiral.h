//spiral.h
#ifndef RESPIRAL_H
#define RESPIRAL_H

#include <common.h>


int R_is_valid(int **arr, int square_l, int dir, int *count, int *travle_l);  // for decision of when should turn the direction of respiral
								//
float R_spiral(int **arr, int **cs_arr, int CS_num, int square_l, int x_base, int y_base);	//respiral main function 
								//
#endif /* RESPIRAL_H */
