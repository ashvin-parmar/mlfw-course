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
dimension_t target_values_vector_size;

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
if(input_values_matrix==NULL || target_values_vector==NULL) return NULL;
if(number_of_iteration<=0 && on_each_iteration==NULL) return NULL;//not triggered in it
if(learning_rate>=1 || learning_rate<=0 ) return NULL; //error management in next module

I=input_values_matrix;
mlfw_mat_double_get_dimension(I,&I_rows,&I_columns);

target_values_vector_size=mlfw_column_vec_double_get_size(target_values_vector);
if(I_rows!=target_values_vector_size) return NULL;


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
while(1)		//loop starts
{
if(number_of_iteration>0 && k==(number_of_iteration+1)) break;
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
um=mlfw_subtract_double_column_vector(m,TMP,um);
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
if(on_each_iteration(k,final_error_value)==0)
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
mlfw_column_vec_double *mlfw_linear_regression_predict(mlfw_mat_double *input_features_matrix,mlfw_row_vec_double *trained_parameters)
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
if(trained_parameters_size!=I_columns+1) return NULL;
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

mlfw_row_vec_double *mlfw_linear_regression_normal_equation_fit_line(mlfw_mat_double *input_values_matrix,mlfw_column_vec_double *target_values_vector)
{
mlfw_mat_double *X;
mlfw_mat_double *XT;
mlfw_mat_double *XTX;
mlfw_mat_double *INV_XTX;

dimension_t X_rows,X_columns;
dimension_t input_values_matrix_rows,input_values_matrix_columns;
dimension_t target_values_vector_size;

mlfw_column_vec_double *Y;
mlfw_column_vec_double *XTY;

mlfw_column_vec_double *m;
mlfw_row_vec_double *parameter_row_vector;

if(input_values_matrix==NULL || target_values_vector==NULL) return NULL;
mlfw_mat_double_get_dimension(input_values_matrix,&input_values_matrix_rows,&input_values_matrix_columns);
target_values_vector_size=mlfw_column_vec_double_get_size(target_values_vector);
if(input_values_matrix_rows!=target_values_vector_size) return NULL;
X=mlfw_mat_double_clone(input_values_matrix,NULL);
if(X==NULL) return NULL;
mlfw_mat_double_get_dimension(X,&X_rows,&X_columns);

mlfw_mat_double_reshape(&X,X_rows,X_columns+1);
if(X==NULL) return NULL;
X_columns=X_columns+1;
mlfw_mat_double_right_shift(X,1);
mlfw_mat_double_fill(X,0,0,X_rows-1,0,1.0);	//bias filled
XT=mlfw_mat_double_transpose(X,NULL);
if(XT==NULL)
{
mlfw_mat_double_destroy(X);
return NULL;
}
XTX=mlfw_multiply_double_matrix_with_matrix(XT,X,NULL);
mlfw_mat_double_destroy(X);
if(XTX==NULL)
{
mlfw_mat_double_destroy(XT);
return NULL;
}
INV_XTX=mlfw_mat_double_inverse(XTX,NULL);
mlfw_mat_double_destroy(XTX);
if(INV_XTX==NULL)
{
mlfw_mat_double_destroy(XT);
return NULL;
}
Y=target_values_vector;
XTY=mlfw_multiply_double_matrix_with_column_vector(XT,Y,NULL);
mlfw_mat_double_destroy(XT);
if(XTY==NULL)
{
	mlfw_mat_double_destroy(INV_XTX);
	return NULL;
}
m=mlfw_multiply_double_matrix_with_column_vector(INV_XTX,XTY,NULL);
mlfw_mat_double_destroy(INV_XTX);
mlfw_column_vec_double_destroy(XTY);
if(m==NULL) return NULL;
parameter_row_vector=mlfw_column_vec_double_transpose(m,NULL);
mlfw_column_vec_double_destroy(m);
return parameter_row_vector;
}
