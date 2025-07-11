#ifndef __MLFW__LINEAR__REGRESSION__
#define __MLFW__LINEAR__REGRESSION__
#include<mlfw_matrix.h>
#include<mlfw_vector.h>
#include<mlfw_learning.h>
mlfw_row_vec_double *mlfw_regression_gradient_fit_line(mlfw_mat_double *input_values_matrix,mlfw_column_vec_double *target_values_vector,double learning_rate,uint64_t number_of_iteration,uint8_t (*on_each_iteration)(uint64_t iteration_number,double error_value));
#endif
