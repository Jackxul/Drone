//zamboni.h
#ifndef ZAMBONI_H
#define ZAMBONI_H

#include <common.h>
void set_lock(); // set mutex lock
int set_col(int col , int value); // set column value
int set_row(int row , int value); // set row value
void visit(int **arr, int point_x, int point_y); // visit a point
void zamboni_path(int **arr, int arr_length, int arr_height); // zamboni path


float zamboni(int **arr, int **cs_arr, int CS_num, int square_length, int x_base, int y_base);	//zamboni




#endif /* ZAMBONI_H */
