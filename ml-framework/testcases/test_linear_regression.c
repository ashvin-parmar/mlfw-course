#include<mlfw_matrix.h>
#include<mlfw_vector.h>
#include<mlfw_learning.h>
#include<stdio.h>
#include<inttypes.h>
uint64_t number_of_iteration;


uint8_t on_each_iteration(uint64_t iteration_number,double error_value)
{
printf("%" PRIu64 " , %20.15lf\n",iteration_number,error_value);

if(number_of_iteration==iteration_number) return 0;
}

int main()
{
mlfw_mat_double *matrix;
mlfw_row_vec_string *header;
mlfw_column_vec_double *target_vector;
double learning_rate;
mlfw_row_vec_double *parameters;
dimension_t matrix_rows,matrix_columns;
number_of_iteration=100000;
learning_rate=0.0001;
matrix=mlfw_mat_double_from_csv("IceCreamSales.csv",NULL,&header);
if(matrix==NULL)
{
printf("Low on memory\n");
return 0;
}
mlfw_mat_double_get_dimension(matrix,&matrix_rows,&matrix_columns);

target_vector=mlfw_mat_double_create_column_vec(matrix,matrix_columns-1,NULL);
if(target_vector==NULL)
{
printf("Low on memory\n");
mlfw_mat_double_destroy(matrix);
mlfw_row_vec_string_destroy(header);
return 0;
}

mlfw_mat_double_reshape(&matrix,matrix_rows,matrix_columns-1);
if(matrix==NULL)
{
printf("Low on memory\n");
mlfw_mat_double_destroy(matrix);
mlfw_row_vec_string_destroy(header);
mlfw_column_vec_double_destroy(target_vector);
return 0;
}


parameters=mlfw_linear_regression_gradient_descent_fit_line(matrix,target_vector,learning_rate,number_of_iteration,on_each_iteration);
if(parameters==NULL)
{
printf("Low on memory\n");
mlfw_mat_double_destroy(matrix);
mlfw_row_vec_string_destroy(header);
mlfw_column_vec_double_destroy(target_vector);
return 0;
}

mlfw_row_vec_double_to_csv(parameters,"parameter.csv",header);


mlfw_mat_double_destroy(matrix);
mlfw_row_vec_string_destroy(header);
mlfw_column_vec_double_destroy(target_vector);
mlfw_row_vec_double_destroy(parameters);
return 0;
}
