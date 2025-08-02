#include<mlfw_matrix.h>
#include<mlfw_vector.h>
#include<mlfw_learning.h>
#include<mlfw_operations.h>
#include<inttypes.h>
#include<stdio.h>

mlfw_row_vec_double *mlfw_linear_regression_gradient_descent_fit_line(mlfw_mat_double *input_values_matrix,mlfw_column_vec_double *target_values_vector,double learning_rate,uint64_t number_of_iteration,uint8_t (*on_each_iteration)(uint64_t iteration_number,double error_value))
{
mlfw_row_vec_double *parameter_row_vector;
mlfw_mat_double *I;
dimension_t I_rows;
dimension_t I_columns;

mlfw_column_vec_double *A;
mlfw_column_vec_double *m;
mlfw_column_vec_double *P;
mlfw_column_vec_double *E;
mlfw_row_vec_double *ET; 
mlfw_column_vec_double *ETE; 
mlfw_mat_double *IT;
mlfw_column_vec_double *ITE;
mlfw_column_vec_double *TMP;
mlfw_column_vec_double *um;
uint64_t k;
double sum_of_squared_error_values; 
double final_error_value; 
int error_number=0;
index_t r; 
if(input_values_matrix==NULL || target_values_vector==NULL || on_each_iteration==NULL) return NULL;
if(number_of_iteration<=0) return NULL;
if(learning_rate>=1 || learning_rate<=0 ) return NULL; //error management in next module

I=input_values_matrix;
mlfw_mat_double_get_dimension(I,&I_rows,&I_columns);
mlfw_mat_double_reshape(&I,I_rows,I_columns+1);
if(I==NULL) return NULL;
I_columns=I_columns+1;
mlfw_mat_double_right_shift(I,1);
mlfw_mat_double_fill(I,0,0,I_rows-1,0,1.0);	//Fill bias

IT=mlfw_mat_double_transpose(I,NULL);
if(IT==NULL)
{
mlfw_mat_double_left_shift(I,1);
mlfw_mat_double_reshape(&I,I_rows,I_columns-1);
return NULL;
}

A=target_values_vector;

m=mlfw_column_vec_double_create_new_filled(I_columns,0.0,NULL);
if(m==NULL)
{
mlfw_mat_double_left_shift(I,1);
mlfw_mat_double_reshape(&I,I_rows,I_columns-1);
mlfw_mat_double_destroy(IT);
return NULL;
}

P=mlfw_column_vec_double_create_new(I_rows);
if(P==NULL)
{
mlfw_mat_double_left_shift(I,1);
mlfw_mat_double_reshape(&I,I_rows,I_columns-1);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(m);
return NULL;
}
E=mlfw_column_vec_double_create_new(I_rows);
if(E==NULL)
{
mlfw_mat_double_left_shift(I,1);
mlfw_mat_double_reshape(&I,I_rows,I_columns-1);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(m);
mlfw_column_vec_double_destroy(P);
return NULL;
}
ET=mlfw_row_vec_double_create_new(I_rows);
if(ET==NULL)
{
mlfw_mat_double_left_shift(I,1);
mlfw_mat_double_reshape(&I,I_rows,I_columns-1);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(m);
mlfw_column_vec_double_destroy(P);
mlfw_column_vec_double_destroy(E);
return NULL;
}
ETE=mlfw_column_vec_double_create_new(1);
if(ETE==NULL)
{
mlfw_mat_double_left_shift(I,1);
mlfw_mat_double_reshape(&I,I_rows,I_columns-1);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(m);
mlfw_column_vec_double_destroy(P);
mlfw_column_vec_double_destroy(E);
mlfw_row_vec_double_destroy(ET);
return NULL;
}
ITE=mlfw_column_vec_double_create_new(I_columns);
if(ITE==NULL)
{
mlfw_mat_double_left_shift(I,1);
mlfw_mat_double_reshape(&I,I_rows,I_columns-1);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(m);
mlfw_column_vec_double_destroy(P);
mlfw_column_vec_double_destroy(E);
mlfw_row_vec_double_destroy(ET);
mlfw_column_vec_double_destroy(ETE);
return NULL;
}
TMP=mlfw_column_vec_double_create_new(I_columns);
if(TMP==NULL)
{
mlfw_mat_double_left_shift(I,1);
mlfw_mat_double_reshape(&I,I_rows,I_columns-1);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(m);
mlfw_column_vec_double_destroy(P);
mlfw_column_vec_double_destroy(E);
mlfw_row_vec_double_destroy(ET);
mlfw_column_vec_double_destroy(ETE);
mlfw_column_vec_double_destroy(ITE);
return NULL;
}
um=mlfw_column_vec_double_create_new(I_columns);
if(um==NULL)
{
mlfw_mat_double_left_shift(I,1);
mlfw_mat_double_reshape(&I,I_rows,I_columns-1);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(m);
mlfw_column_vec_double_destroy(P);
mlfw_column_vec_double_destroy(E);
mlfw_row_vec_double_destroy(ET);
mlfw_column_vec_double_destroy(ETE);
mlfw_column_vec_double_destroy(ITE);
mlfw_column_vec_double_destroy(TMP);
return NULL;
}
error_number=0;
k=1;
while(k<=number_of_iteration)		//loop starts
{
P=mlfw_multiply_double_matrix_with_column_vector(I,m,P);
if(P==NULL)
{
error_number=1;
break;
}
E=mlfw_subtract_double_column_vector(P,A,E);
if(E==NULL)
{
error_number=1;
break;
}
ET=mlfw_column_vec_double_transpose(E,ET);
if(ET==NULL)
{
error_number=1;
break;
}
ETE=mlfw_multiply_double_row_vector_with_column_vector(ET,E,ETE);
if(ETE==NULL)
{
error_number=1;
break;
}
sum_of_squared_error_values=mlfw_column_vec_double_get(ETE,0);
final_error_value=sum_of_squared_error_values/(2*I_rows);	//change

//printf("Iteration Number: %" PRIu64 ", Error: %20.15lf\n",k+1,final_error_value);

ITE=mlfw_multiply_double_matrix_with_column_vector(IT,E,ITE);
if(ITE==NULL)
{
error_number=1;
break;
}						//Learning rate
TMP=mlfw_multiply_double_scalar_with_column_vector((learning_rate)*(1.0/I_rows),ITE,TMP);
if(TMP==NULL)
{
error_number=1;
break;
}
um=mlfw_subtract_double_column_vector(m,TMP,NULL);
if(um==NULL)
{
error_number=1;
break;
}
for(r=0;r<I_columns;r++)
{
mlfw_column_vec_double_set(m,r,mlfw_column_vec_double_get(um,r));
}
if(on_each_iteration!=NULL)
{
if(!on_each_iteration(k,final_error_value))
{
break;
}
}
++k;
}
if(error_number==1)
{
//printf("Dimension of container is incorrect\n");
mlfw_mat_double_left_shift(I,1);
mlfw_mat_double_reshape(&I,I_rows,I_columns-1);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(P);
mlfw_column_vec_double_destroy(E);
mlfw_row_vec_double_destroy(ET);
mlfw_column_vec_double_destroy(ETE);
mlfw_column_vec_double_destroy(ITE);
mlfw_column_vec_double_destroy(TMP);
mlfw_column_vec_double_destroy(um);
mlfw_column_vec_double_destroy(m);
return NULL;
}

//Releases memory
mlfw_mat_double_left_shift(I,1);
mlfw_mat_double_reshape(&I,I_rows,I_columns-1);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(P);
mlfw_column_vec_double_destroy(E);
mlfw_row_vec_double_destroy(ET);
mlfw_column_vec_double_destroy(ETE);
mlfw_column_vec_double_destroy(ITE);
mlfw_column_vec_double_destroy(TMP);
mlfw_column_vec_double_destroy(um);

parameter_row_vector=mlfw_column_vec_double_transpose(m,NULL);
mlfw_column_vec_double_destroy(m);

return parameter_row_vector;
}
mlfw_column_vec_double *mlfw_regression_predict(mlfw_mat_double *input_features_matrix,mlfw_row_vec_double *trained_parameters)
{
mlfw_mat_double *I; 
dimension_t I_rows;
dimension_t I_columns;
dimension_t trained_parameters_size;
mlfw_column_vec_double *m; 
mlfw_column_vec_double *P;

if(input_features_matrix==NULL || trained_parameters==NULL) return NULL;
I=input_features_matrix;
trained_parameters_size=mlfw_row_vec_double_get_size(trained_parameters);
mlfw_mat_double_get_dimension(I,&I_rows,&I_columns);
if(trained_parameters_size!=I_columns) return NULL;
mlfw_mat_double_reshape(&I,I_rows,I_columns+1);
if(I==NULL) return NULL;
I_columns=I_columns+1;
mlfw_mat_double_right_shift(I,1);
mlfw_mat_double_fill(I,0,0,I_rows-1,0,1.0);	//not necessary, but still
m=mlfw_row_vec_double_transpose(trained_parameters,NULL);
if(m==NULL)
{
mlfw_mat_double_left_shift(I,1);
mlfw_mat_double_reshape(&I,I_rows,I_columns-1);
return NULL;
}
P=mlfw_multiply_double_matrix_with_column_vector(I,m,NULL);
if(P==NULL)
{
mlfw_mat_double_left_shift(I,1);
mlfw_mat_double_reshape(&I,I_rows,I_columns-1);
mlfw_column_vec_double_destroy(m);
return NULL;
}
mlfw_mat_double_left_shift(I,1);
mlfw_mat_double_reshape(&I,I_rows,I_columns-1);
mlfw_column_vec_double_destroy(m);
return P;
}
