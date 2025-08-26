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
mlfw_mat_double *training_examples_matrix;
mlfw_mat_double *testing_examples_matrix;
mlfw_column_vec_double *training_examples_target_values_vector;
mlfw_column_vec_double *testing_examples_target_values_vector;
mlfw_column_vec_double *testing_examples_predicted_values_vector;
dimension_t training_examples_matrix_rows,training_examples_matrix_columns;
dimension_t testing_examples_matrix_rows,testing_examples_matrix_columns;
mlfw_row_vec_double *trained_parameters;
dimension_t trained_parameters_size;
index_t r;
double r2_score;
if(argc!=2)
{
printf("Pass Number of iteration required\n");
return 0;
}
mlfw_mat_double_get_training_testing_data("IceCreamSales.csv",&training_examples_matrix,&testing_examples_matrix,20);
if(training_examples_matrix==NULL || testing_examples_matrix==NULL)
{
printf("Unable to load IceCreamSales.csv file\n");
if(training_examples_matrix!=NULL)
{
mlfw_mat_double_destroy(training_examples_matrix);
}
if(testing_examples_matrix!=NULL)
{
mlfw_mat_double_destroy(testing_examples_matrix);
}
return 0;
}
mlfw_mat_double_get_dimension(training_examples_matrix,&training_examples_matrix_rows,&training_examples_matrix_columns);
mlfw_mat_double_get_dimension(testing_examples_matrix,&testing_examples_matrix_rows,&testing_examples_matrix_columns);
training_examples_target_values_vector=mlfw_mat_double_create_column_vec(training_examples_matrix,training_examples_matrix_columns-1,NULL);
if(training_examples_target_values_vector==NULL)
{
printf("Low on memory\n");
mlfw_mat_double_destroy(testing_examples_matrix);
mlfw_mat_double_destroy(training_examples_matrix);
return 0;
}
mlfw_mat_double_reshape(&training_examples_matrix,training_examples_matrix_rows,training_examples_matrix_columns-1);
if(training_examples_matrix==NULL)
{
printf("Low on memory\n");
mlfw_mat_double_destroy(testing_examples_matrix);
mlfw_column_vec_double_destroy(training_examples_target_values_vector);
return 0;
}

trained_parameters=mlfw_linear_regression_gradient_descent_fit_line(training_examples_matrix,training_examples_target_values_vector,0.0003,atoi(argv[1]),screen_logger);
if(trained_parameters==NULL)
{
printf("Low on memory\n");
mlfw_mat_double_destroy(training_examples_matrix);
mlfw_mat_double_destroy(testing_examples_matrix);
mlfw_column_vec_double_destroy(training_examples_target_values_vector);
return 0;
}
trained_parameters_size=mlfw_row_vec_double_get_size(trained_parameters);
printf("Trained parameters are as follows: \n");
for(r=0;r<trained_parameters_size;r++)
{
printf("%lf ,",mlfw_row_vec_double_get(trained_parameters,r));
}
printf("\n");
mlfw_mat_double_destroy(training_examples_matrix);
mlfw_column_vec_double_destroy(training_examples_target_values_vector);

testing_examples_target_values_vector=mlfw_mat_double_create_column_vec(testing_examples_matrix,testing_examples_matrix_columns-1,NULL);
if(testing_examples_target_values_vector==NULL)
{
printf("Low on memory\n");
mlfw_mat_double_destroy(testing_examples_matrix);
return 0;
}
mlfw_mat_double_reshape(&testing_examples_matrix,testing_examples_matrix_rows,testing_examples_matrix_columns-1);
if(training_examples_matrix==NULL)
{
printf("Low on memory\n");
mlfw_column_vec_double_destroy(testing_examples_target_values_vector);
mlfw_row_vec_double_destroy(trained_parameters);
return 0;
}
testing_examples_predicted_values_vector=mlfw_linear_regression_predict(testing_examples_matrix,trained_parameters);
if(testing_examples_predicted_values_vector==NULL)
{
printf("Low on memory for testing\n");
mlfw_mat_double_destroy(testing_examples_matrix);
mlfw_column_vec_double_destroy(testing_examples_target_values_vector);
mlfw_row_vec_double_destroy(trained_parameters);
return 0;
}
r2_score=mlfw_learning_get_r2_score(testing_examples_target_values_vector,testing_examples_predicted_values_vector);
printf("Score is: %lf\n",r2_score);

mlfw_row_vec_double_destroy(trained_parameters);
mlfw_column_vec_double_destroy(testing_examples_target_values_vector);
mlfw_column_vec_double_destroy(testing_examples_predicted_values_vector);
mlfw_mat_double_destroy(testing_examples_matrix);
return 0;
}
