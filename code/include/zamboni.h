//zamboni.h
#ifndef ZAMBONI_H
#define ZAMBONI_H

#include <common.h>
void set_lock();
int set_col(int col , int value);
int set_row(int row , int value);
void visit(int **arr, int point_x, int point_y);
void zamboni_path(int **arr, int arr_length, int arr_height);


float zamboni(int **arr, int arr_length, int arr_height);	//zamboni




#endif /* ZAMBONI_H */
