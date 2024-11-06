#include<stdio.h>
#include<stdlib.h>
#include<mlfw_vector.h>
typedef struct __mlfw_column_vec_double
{
double *data;
dimension_t size;
}mlfw_column_vec_double;
typedef struct __mlfw_row_vec_double
{
double *data;
dimension_t size;
}mlfw_row_vec_double;

//For Column Vector
mlfw_column_vec_double * mlfw_column_vec_double_create_new(dimension_t size)
{
mlfw_column_vec_double *vector;
if(size<=0) return NULL;
vector=(mlfw_column_vec_double *)malloc(sizeof(mlfw_column_vec_double));
if(vector==NULL) return NULL;
vector->data=(double *)malloc(sizeof(double)*size);
if(vector->data==NULL)
{
free(vector);
return NULL;
}
vector->size=size;
return vector;
}
void mlfw_column_vec_double_destroy(mlfw_column_vec_double *vector)
{
if(vector==NULL) return ;
free(vector->data);
free(vector);
}
double mlfw_column_vec_double_get(mlfw_column_vec_double *vector,index_t index)
{
double value=0.0;
if(vector==NULL) return value;
if(index<0 || index>=vector->size) return value;
return vector->data[index];
}
void mlfw_column_vec_double_set(mlfw_column_vec_double *vector,index_t index,double value)
{
if(vector==NULL) return;
if(index<0 || index>=vector->size) return;
vector->data[index]=value;
}
mlfw_column_vec_double *mlfw_column_vec_double_create_new_filled(dimension_t size,double value)
{
mlfw_column_vec_double *vector;
index_t i;
if(size<=0) return NULL;
vector=mlfw_column_vec_double_create_new(size);
if(vector==NULL) return NULL;
for(i=0;i<size;i++) vector->data[i]=value;
return vector;
}
mlfw_row_vec_double * mlfw_column_vec_double_transpose(mlfw_column_vec_double *column_vector)
{
mlfw_row_vec_double *row_vector;
index_t i;
dimension_t size;
if(column_vector==NULL) return NULL;
size=mlfw_column_vec_double_get_size(column_vector);
if(size<=0) return NULL;
row_vector=mlfw_row_vec_double_create_new(size);
if(row_vector==NULL) return NULL;

for(i=0;i<size;i++) mlfw_row_vec_double_set(row_vector,i,mlfw_column_vec_double_get(column_vector,i));
return row_vector;
}
dimension_t mlfw_column_vec_double_get_size(mlfw_column_vec_double *vector)
{
if(vector==NULL) return 0;
return vector->size;
}

//For Rows Vector
mlfw_row_vec_double * mlfw_row_vec_double_create_new(dimension_t size)
{
mlfw_row_vec_double *vector;
if(size<=0) return NULL;
vector=(mlfw_row_vec_double *)malloc(sizeof(mlfw_row_vec_double));
if(vector==NULL) return NULL;
vector->data=(double *)malloc(sizeof(double)*size);
if(vector->data==NULL) 
{
free(vector);
return NULL;
}
vector->size=size;
return vector;
}
void mlfw_row_vec_double_destroy(mlfw_row_vec_double *vector)
{
if(vector==NULL) return ;
free(vector->data);
free(vector);
}
double mlfw_row_vec_double_get(mlfw_row_vec_double *vector,index_t index)
{
if(vector==NULL) return 0.0;
if(index<0 || index>=vector->size) return 0.0;
return vector->data[index];
}
void mlfw_row_vec_double_set(mlfw_row_vec_double *vector,index_t index,double value)
{
if(vector==NULL) return;
if(index<0 || index>=vector->size) return;
vector->data[index]=value;
}
mlfw_row_vec_double *mlfw_row_vec_double_create_new_filled(dimension_t size,double value)
{
mlfw_row_vec_double *vector;
index_t i;
if(size<=0) return NULL;
vector=mlfw_row_vec_double_create_new(size);
if(vector==NULL) return NULL;
for(i=0;i<vector->size;i++) vector->data[i]=value;
return vector;
}
mlfw_column_vec_double * mlfw_row_vec_double_transpose(mlfw_row_vec_double *row_vector)
{
mlfw_column_vec_double *column_vector;
index_t i;
if(row_vector==NULL) return NULL;
column_vector=mlfw_column_vec_double_create_new(row_vector->size);
if(column_vector==NULL) return NULL;
for(i=0;i<column_vector->size;i++) column_vector->data[i]=row_vector->data[i]; 
return column_vector;
}
dimension_t mlfw_row_vec_double_get_size(mlfw_row_vec_double *vector)
{
if(vector==NULL) return 0;
return vector->size;
}
