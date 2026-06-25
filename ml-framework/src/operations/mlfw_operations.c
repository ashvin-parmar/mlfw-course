#include<stdio.h>
#include<stdlib.h>
#include<mlfw_matrix.h>
#include<mlfw_vector.h>
#include<mlfw_operations.h>

//Vector X Matrix
mlfw_column_vec_double * mlfw_multiply_double_matrix_with_column_vector(mlfw_mat_double *left_matrix,mlfw_column_vec_double *right_vector,mlfw_column_vec_double *vector)
{
index_t r,c;
dimension_t left_matrix_row;
dimension_t left_matrix_column;
dimension_t right_vector_size;
double value;
if(left_matrix==NULL) return NULL;
if(right_vector==NULL) return NULL;

mlfw_mat_double_get_dimension(left_matrix,&left_matrix_row,&left_matrix_column);
right_vector_size=mlfw_column_vec_double_get_size(right_vector);
if(left_matrix_column!=right_vector_size) return NULL;
if(vector==NULL)
{
vector=mlfw_column_vec_double_create_new(left_matrix_row);
if(vector==NULL) return NULL;
}
else
{
if(mlfw_column_vec_double_get_size(vector)!=left_matrix_row) return NULL;
}
for(r=0;r<left_matrix_row;r++)
{
value=0.0;
for(c=0;c<left_matrix_column;c++)
{
value=value+(mlfw_mat_double_get(left_matrix,r,c)*mlfw_column_vec_double_get(right_vector,c));
}
mlfw_column_vec_double_set(vector,r,value);
}
return vector;
}
//Vector X Vector
mlfw_column_vec_double * mlfw_subtract_double_column_vector(mlfw_column_vec_double *left_vector,mlfw_column_vec_double *right_vector,mlfw_column_vec_double *new_vector)
{
dimension_t left_vector_size;
dimension_t right_vector_size;
index_t i;
double value;
if(left_vector==NULL) return NULL;
if(right_vector==NULL) return NULL;
left_vector_size=mlfw_column_vec_double_get_size(left_vector);
right_vector_size=mlfw_column_vec_double_get_size(right_vector);
if(left_vector_size!=right_vector_size) return NULL;
if(new_vector==NULL)
{
new_vector=mlfw_column_vec_double_create_new(left_vector_size);
if(new_vector==NULL) return NULL;
}
else
{
if(mlfw_column_vec_double_get_size(new_vector)!=left_vector_size) return NULL;
}
for(i=0;i<left_vector_size;i++)
{
value=mlfw_column_vec_double_get(left_vector,i)-mlfw_column_vec_double_get(right_vector,i);
mlfw_column_vec_double_set(new_vector,i,value);
}
return new_vector;
}
mlfw_column_vec_double * mlfw_multiply_double_row_vector_with_column_vector(mlfw_row_vec_double *left_vector,mlfw_column_vec_double *right_vector,mlfw_column_vec_double *vector)
{
index_t i;
double value;
dimension_t left_vector_size;
dimension_t right_vector_size;

left_vector_size=mlfw_row_vec_double_get_size(left_vector);
right_vector_size=mlfw_column_vec_double_get_size(right_vector);
if(left_vector_size!=right_vector_size) return NULL;
if(vector==NULL)
{
vector=mlfw_column_vec_double_create_new(1);
if(vector==NULL) return NULL;
}
else
{
if(mlfw_column_vec_double_get_size(vector)!=1) return NULL;
}
value=0.0;
for(i=0;i<left_vector_size;i++)
{
value=value+(mlfw_row_vec_double_get(left_vector,i)*mlfw_column_vec_double_get(right_vector,i));
}
mlfw_column_vec_double_set(vector,0,value);
return vector;
}

mlfw_column_vec_double * mlfw_multiply_double_scalar_with_column_vector(double scalar_value,mlfw_column_vec_double *vector,mlfw_column_vec_double *product_vector)
{
dimension_t size;
index_t i;
double value;
double product;
if(vector==NULL) return NULL;
size=mlfw_column_vec_double_get_size(vector);
if(product_vector==NULL)
{
product_vector=mlfw_column_vec_double_create_new(size);
if(product_vector==NULL) return NULL;
}
else
{
if(mlfw_column_vec_double_get_size(product_vector)!=size) return NULL;
}
for(i=0;i<size;i++)
{
value=mlfw_column_vec_double_get(vector,i);
product=value*scalar_value;
mlfw_column_vec_double_set(product_vector,i,product);
}
return product_vector;
}

