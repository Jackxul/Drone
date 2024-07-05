//zamboni.h
#ifndef ZAMBONI_H
#define ZAMBONI_H

#include <common.h>
int lock_col(bool ,int col);
int lock_row(bool ,int row);
void visit(int **arr, int point_x, int point_y);
float zamboni(int **arr, int arr_length, int arr_height);	//zamboni




#endif /* ZAMBONI_H */
