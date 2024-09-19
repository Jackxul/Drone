//zamboni.h
#ifndef ZAMBONI_H
#define ZAMBONI_H

#include <common.h>
void set_lock();
int set_col(int col , int value);
int set_row(int row , int value);
void visit(int **arr, int point_x, int point_y);
void zamboni_path(int **arr, int arr_length, int arr_height);


float zamboni(int **arr, int **cs_arr, int CS_num, int square_length, int x_base, int y_base);	//zamboni




#endif /* ZAMBONI_H */
