#include<mlfw_matrix.h>
#include<mlfw_vector.h>
#include<mlfw_learning.h>
#include<stdio.h>
#include<stdlib.h>
uint8_t screen_logger(uint64_t iteration_number,double error_value)
{
printf("Iteration number: %" PRIu64 ", Error: %40.12lf\n",iteration_number,error_value);
return 1; // continue running
}

int main(int argc,char *argv[])
{
mlfw_mat_double *matrix;
mlfw_row_vec_string *header;
mlfw_column_vec_double *target_values_vector;
dimension_t matrix_rows,matrix_columns;
mlfw_row_vec_double *trained_parameter;
dimension_t trained_parameter_size;
index_t r;

if(argc!=2)
{
printf("Pass Number of iteration required\n");
return 0;
}

matrix=mlfw_mat_double_from_csv("IceCreamSales.csv",NULL,&header);
if(matrix==NULL)
{
printf("Unable to load IceCreamSales.csv, Low on memory\n");
return 0;
}
mlfw_mat_double_get_dimension(matrix,&matrix_rows,&matrix_columns);
target_values_vector=mlfw_mat_double_create_column_vec(matrix,matrix_columns-1,NULL);
if(target_values_vector==NULL)
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
mlfw_column_vec_double_destroy(target_values_vector);
return 0;
}


mlfw_row_vec_double *mlfw_regression_gradient_fit_line(mlfw_mat_double *input_values_matrix,mlfw_column_vec_double *target_values_vector,double learning_rate,uint64_t number_of_iteration,uint8_t (*on_each_iteration)(uint64_t iteration_number,double error_value));
trained_parameter=mlfw_regression_gradient_fit_line(matrix,target_values_vector,0.0001,atoi(argv[1]),screen_logger);
if(trained_parameter==NULL)
{
printf("Low on memory\n");
mlfw_mat_double_destroy(matrix);
mlfw_row_vec_string_destroy(header);
mlfw_column_vec_double_destroy(target_values_vector);
return 0;
}
trained_parameter_size=mlfw_row_vec_double_get_size(trained_parameter);
for(r=0;r<trained_parameter_size;r++)
{
printf("%lf\n",mlfw_row_vec_double_get(trained_parameter,r));
}

//More for testing and r2score [pending]


mlfw_mat_double_destroy(matrix);
mlfw_row_vec_string_destroy(header);
mlfw_column_vec_double_destroy(target_values_vector);
mlfw_row_vec_double_destroy(trained_parameter);

return 0;
}
