#include<mlfw_matrix.h>
#include<mlfw_vector.h>
#include<mlfw_learning.h>
#include<stdio.h>
#include<inttypes.h>
#include<pthread.h>		//For threading implementation in c programming
#include<stdlib.h>
uint8_t STOP_FLAG=1;

uint8_t on_each_iteration(uint64_t iteration_number,double error_value)
{
printf("Iteration number: %ld , Error Value: %20.15lf\n",iteration_number,error_value);
return STOP_FLAG;
}

void * thread_function(void *p)
{
mlfw_row_vec_double *parameters;
mlfw_mat_double *matrix;
mlfw_row_vec_string *header;
mlfw_column_vec_double *m;
uint64_t number_of_iteration;
double learning_rate;
dimension_t matrix_rows,matrix_columns;
number_of_iteration=1000000;
learning_rate=0.0001;
matrix=mlfw_mat_double_from_csv("IceCreamSales.csv",NULL,&header);
if(matrix==NULL)
{
printf("Low on memory\n");
return 0;
}
mlfw_mat_double_get_dimension(matrix,&matrix_rows,&matrix_columns);

m=mlfw_column_vec_double_create_new_filled(matrix_columns,0.0,NULL);
if(m==NULL)
{
printf("Low on memory\n");
mlfw_mat_double_destroy(matrix);
mlfw_row_vec_string_destroy(header);
return 0;
}
parameters=mlfw_regression_gradient_fit_line(matrix,m,learning_rate,number_of_iteration,on_each_iteration);
if(parameters==NULL)
{
printf("Low on memory\n");
mlfw_mat_double_destroy(matrix);
mlfw_row_vec_string_destroy(header);
mlfw_column_vec_double_destroy(m);
return 0;
}
printf("parameter.csv file created\n");
mlfw_row_vec_double_to_csv(parameters,"parameter.csv",header);
mlfw_mat_double_destroy(matrix);
mlfw_row_vec_string_destroy(header);
mlfw_column_vec_double_destroy(m);
mlfw_row_vec_double_destroy(parameters);
return NULL;
}

int main()
{
pthread_t thread_id;
int result;

result=pthread_create(&thread_id,NULL,thread_function,NULL);
if(result!=0)
{
printf("Unable to create thread\n");
return 0;
}
while(1)
{
if(getchar()=='\n')
{
STOP_FLAG=0;
break;
}
}

pthread_join(thread_id,NULL);	//wait for the thread to end thread_function
return 0;
}
