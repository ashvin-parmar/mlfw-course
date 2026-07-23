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


mlfw_mat_double * mlfw_multiply_double_matrix_with_matrix(mlfw_mat_double *left_matrix,mlfw_mat_double *right_matrix,mlfw_mat_double *new_matrix)
{
mlfw_mat_double *m1,*m2,*m3;
dimension_t m1_rows,m1_columns;
dimension_t m2_rows,m2_columns;
dimension_t m3_rows,m3_columns;

double value1,value2,value3;

index_t r3,c3,c1;

if(left_matrix==NULL || right_matrix==NULL) return NULL;
m1=left_matrix;
m2=right_matrix;

mlfw_mat_double_get_dimension(m1,&m1_rows,&m1_columns);
mlfw_mat_double_get_dimension(m2,&m2_rows,&m2_columns);

if(m1_columns!=m2_rows) return NULL;
if(new_matrix==NULL)
{
m3_rows=m1_rows;
m3_columns=m2_columns;
m3=mlfw_mat_double_create_new(m3_rows,m3_columns);
if(m3==NULL) return NULL;
}
else
{
mlfw_mat_double_get_dimension(new_matrix,&m3_rows,&m3_columns);
if(m1_rows!=m3_rows || m2_columns!=m3_columns) return NULL;
m3=new_matrix;
}

for(r3=0;r3<m3_rows;r3++)
{
for(c3=0;c3<m3_columns;c3++)
{
value3=0.0;
for(c1=0;c1<m1_columns;c1++)
{
value1=mlfw_mat_double_get(m1,r3,c1);
value2=mlfw_mat_double_get(m2,c1,c3);
value3=value3+(value1*value2);
}
value3+=0.0;
mlfw_mat_double_set(m3,r3,c3,value3);
}
}
return m3;
}

mlfw_mat_double * mlfw_add_double_matrix_with_matrix(mlfw_mat_double *left_matrix,mlfw_mat_double *right_matrix,mlfw_mat_double *new_matrix)
{
mlfw_mat_double *result_matrix;
index_t r,c;
dimension_t left_matrix_rows,left_matrix_columns;
dimension_t right_matrix_rows,right_matrix_columns;
dimension_t result_matrix_rows,result_matrix_columns;
double left_value,right_value,result_value;

if(left_matrix==NULL || right_matrix==NULL) return NULL;
mlfw_mat_double_get_dimension(left_matrix,&left_matrix_rows,&left_matrix_columns);
mlfw_mat_double_get_dimension(right_matrix,&right_matrix_rows,&right_matrix_columns);

if(left_matrix_rows!=right_matrix_rows || left_matrix_columns!=right_matrix_columns) return NULL;

if(new_matrix==NULL)
{
result_matrix_rows=left_matrix_rows;
result_matrix_columns=left_matrix_columns;
result_matrix=mlfw_mat_double_create_new(result_matrix_rows,result_matrix_columns);
if(result_matrix==NULL) return NULL;
}
else
{
mlfw_mat_double_get_dimension(new_matrix,&result_matrix_rows,&result_matrix_columns);
if(result_matrix_rows!=left_matrix_rows || result_matrix_columns!=right_matrix_columns) return NULL;
result_matrix=new_matrix;
}
for(r=0;r<left_matrix_rows;++r)
{
for(c=0;c<left_matrix_columns;++c)
{
left_value=mlfw_mat_double_get(left_matrix,r,c);
right_value=mlfw_mat_double_get(right_matrix,r,c);
result_value=left_value+right_value;
mlfw_mat_double_set(result_matrix,r,c,result_value);
}
}
return result_matrix;
}
mlfw_mat_double * mlfw_subtract_double_matrix_with_matrix(mlfw_mat_double *left_matrix,mlfw_mat_double *right_matrix,mlfw_mat_double *new_matrix)
{
mlfw_mat_double *result_matrix;
index_t r,c;
dimension_t left_matrix_rows,left_matrix_columns;
dimension_t right_matrix_rows,right_matrix_columns;
dimension_t result_matrix_rows,result_matrix_columns;
double left_value,right_value,result_value;

if(left_matrix==NULL || right_matrix==NULL) return NULL;
mlfw_mat_double_get_dimension(left_matrix,&left_matrix_rows,&left_matrix_columns);
mlfw_mat_double_get_dimension(right_matrix,&right_matrix_rows,&right_matrix_columns);

if(left_matrix_rows!=right_matrix_rows || left_matrix_columns!=right_matrix_columns) return NULL;

if(new_matrix==NULL)
{
result_matrix_rows=left_matrix_rows;
result_matrix_columns=left_matrix_columns;
result_matrix=mlfw_mat_double_create_new(result_matrix_rows,result_matrix_columns);
if(result_matrix==NULL) return NULL;
}
else
{
mlfw_mat_double_get_dimension(new_matrix,&result_matrix_rows,&result_matrix_columns);
if(result_matrix_rows!=left_matrix_rows || result_matrix_columns!=right_matrix_columns) return NULL;
result_matrix=new_matrix;
}
for(r=0;r<left_matrix_rows;++r)
{
for(c=0;c<left_matrix_columns;++c)
{
left_value=mlfw_mat_double_get(left_matrix,r,c);
right_value=mlfw_mat_double_get(right_matrix,r,c);
result_value=left_value-right_value;
mlfw_mat_double_set(result_matrix,r,c,result_value);
}
}
return result_matrix;
}

mlfw_mat_double * mlfw_strassens_multiply_double_matrix_with_matrix(mlfw_mat_double *left_matrix,mlfw_mat_double *right_matrix,mlfw_mat_double *new_matrix)
{
mlfw_mat_double *m1,*m2,*m3;
dimension_t m1_rows,m1_columns;
dimension_t m2_rows,m2_columns;
dimension_t m3_rows,m3_columns;

dimension_t split_matrix_rows;
dimension_t split_matrix_columns;

mlfw_mat_double *am,*bm,*cm,*dm,*em,*fm,*gm,*hm;
mlfw_mat_double *em1,*em2,*em3,*em4,*em5,*em6,*em7;
mlfw_mat_double *value1,*value2,*value3,*value4;
mlfw_mat_double *tmp1,*tmp2;

double A,B,C,D,E,F,G,H;
double e1,e2,e3,e4,e5,e6,e7;

if(left_matrix==NULL || right_matrix==NULL) return NULL;
m1=left_matrix;
m2=right_matrix;

mlfw_mat_double_get_dimension(m1,&m1_rows,&m1_columns);
mlfw_mat_double_get_dimension(m2,&m2_rows,&m2_columns);
if(m1_rows!=2 || m1_columns!=2 || m2_rows!=2 || m2_columns!=2) 
{
	if(m1_rows!=m1_columns || m2_rows!=m2_columns) return NULL;	//n*n matrix required
	if(m1_rows!=m2_rows || m1_columns!=m2_columns) return NULL;	//same dimension matrix multiplication required
	if(m1_rows%2!=0) return NULL;	// rows and columns dimension must multiple of 2 (2,4,8,16,...)
	if(new_matrix==NULL)
	{
		m3_rows=m1_rows;
		m3_columns=m2_columns;
		m3=mlfw_mat_double_create_new(m3_rows,m3_columns);
		if(m3==NULL) return NULL;
	}
	else
	{
		mlfw_mat_double_get_dimension(new_matrix,&m3_rows,&m3_columns);
		if(m1_rows!=m3_rows || m2_columns!=m3_columns) return NULL;
		m3=new_matrix;
	}
	split_matrix_rows=m1_rows/2;
	split_matrix_columns=m2_rows/2;

	am=mlfw_mat_double_create_copy(m1,0,0,split_matrix_rows-1,split_matrix_columns-1,NULL);
	bm=mlfw_mat_double_create_copy(m1,0,split_matrix_columns,split_matrix_rows-1,m1_columns-1,NULL);
	cm=mlfw_mat_double_create_copy(m1,split_matrix_rows,0,m1_rows-1,split_matrix_columns-1,NULL);
	dm=mlfw_mat_double_create_copy(m1,split_matrix_rows,split_matrix_columns,m1_rows-1,m1_columns-1,NULL);

	em=mlfw_mat_double_create_copy(m2,0,0,split_matrix_rows-1,split_matrix_columns-1,NULL);
	fm=mlfw_mat_double_create_copy(m2,0,split_matrix_columns,split_matrix_rows-1,m2_columns-1,NULL);
	gm=mlfw_mat_double_create_copy(m2,split_matrix_rows,0,m2_rows-1,split_matrix_columns-1,NULL);
	hm=mlfw_mat_double_create_copy(m2,split_matrix_rows,split_matrix_columns,m2_rows-1,m2_columns-1,NULL);

	tmp1=mlfw_mat_double_create_new(split_matrix_rows,split_matrix_columns);
	tmp2=mlfw_mat_double_create_new(split_matrix_rows,split_matrix_columns);

	em1=mlfw_strassens_multiply_double_matrix_with_matrix(am,mlfw_subtract_double_matrix_with_matrix(fm,hm,tmp1),NULL);
	em2=mlfw_strassens_multiply_double_matrix_with_matrix(mlfw_add_double_matrix_with_matrix(am,bm,tmp1),hm,NULL);
	em3=mlfw_strassens_multiply_double_matrix_with_matrix(mlfw_add_double_matrix_with_matrix(cm,dm,tmp1),em,NULL);
	em4=mlfw_strassens_multiply_double_matrix_with_matrix(dm,mlfw_subtract_double_matrix_with_matrix(gm,em,tmp1),NULL);
	em5=mlfw_strassens_multiply_double_matrix_with_matrix(mlfw_add_double_matrix_with_matrix(am,dm,tmp1),mlfw_add_double_matrix_with_matrix(em,hm,tmp2),NULL);
	em6=mlfw_strassens_multiply_double_matrix_with_matrix(mlfw_subtract_double_matrix_with_matrix(bm,dm,tmp1),mlfw_add_double_matrix_with_matrix(gm,hm,tmp2),NULL);
	em7=mlfw_strassens_multiply_double_matrix_with_matrix(mlfw_subtract_double_matrix_with_matrix(am,cm,tmp1),mlfw_add_double_matrix_with_matrix(em,fm,tmp2),NULL);
	mlfw_mat_double_destroy(am);
	mlfw_mat_double_destroy(bm);
	mlfw_mat_double_destroy(cm);
	mlfw_mat_double_destroy(dm);
	mlfw_mat_double_destroy(em);
	mlfw_mat_double_destroy(fm);
	mlfw_mat_double_destroy(gm);
	mlfw_mat_double_destroy(hm);

	value1=mlfw_add_double_matrix_with_matrix(mlfw_add_double_matrix_with_matrix(em5,em4,tmp1),mlfw_subtract_double_matrix_with_matrix(em6,em2,tmp2),NULL);
	value2=mlfw_add_double_matrix_with_matrix(em1,em2,NULL);
	value3=mlfw_add_double_matrix_with_matrix(em3,em4,NULL);
	value4=mlfw_add_double_matrix_with_matrix(mlfw_subtract_double_matrix_with_matrix(em1,em3,tmp1),mlfw_subtract_double_matrix_with_matrix(em5,em7,tmp2),NULL);

	mlfw_mat_double_destroy(tmp1);
	mlfw_mat_double_destroy(tmp2);

	mlfw_mat_double_destroy(em1);
	mlfw_mat_double_destroy(em2);
	mlfw_mat_double_destroy(em3);
	mlfw_mat_double_destroy(em4);
	mlfw_mat_double_destroy(em5);
	mlfw_mat_double_destroy(em6);
	mlfw_mat_double_destroy(em7);

	mlfw_mat_double_copy(m3,value1,0,0,0,0,split_matrix_rows-1,split_matrix_columns-1);
	mlfw_mat_double_copy(m3,value2,0,split_matrix_columns,0,0,split_matrix_rows-1,split_matrix_columns-1);
	mlfw_mat_double_copy(m3,value3,split_matrix_rows,0,0,0,split_matrix_rows-1,split_matrix_columns-1);
	mlfw_mat_double_copy(m3,value4,split_matrix_rows,split_matrix_columns,0,0,split_matrix_rows-1,split_matrix_columns-1);
	
	mlfw_mat_double_destroy(value1);
	mlfw_mat_double_destroy(value2);
	mlfw_mat_double_destroy(value3);
	mlfw_mat_double_destroy(value4);
}
else
{
if(new_matrix==NULL)
{
m3_rows=m1_rows;
m3_columns=m2_columns;
m3=mlfw_mat_double_create_new(m3_rows,m3_columns);
if(m3==NULL) return NULL;
}
else
{
mlfw_mat_double_get_dimension(new_matrix,&m3_rows,&m3_columns);
if(m1_rows!=m3_rows || m2_columns!=m3_columns) return NULL;
m3=new_matrix;
}

A=mlfw_mat_double_get(m1,0,0);
B=mlfw_mat_double_get(m1,0,1);
C=mlfw_mat_double_get(m1,1,0);
D=mlfw_mat_double_get(m1,1,1);

E=mlfw_mat_double_get(m2,0,0);
F=mlfw_mat_double_get(m2,0,1);
G=mlfw_mat_double_get(m2,1,0);
H=mlfw_mat_double_get(m2,1,1);

e1=A*(F-H);
e2=(A+B)*H;
e3=(C+D)*E;
e4=D*(G-E);
e5=(A+D)*(E+H);
e6=(B-D)*(G+H);
e7=(A-C)*(E+F);

mlfw_mat_double_set(m3,0,0,e5+e4-e2+e6);
mlfw_mat_double_set(m3,0,1,e1+e2);
mlfw_mat_double_set(m3,1,0,e3+e4);
mlfw_mat_double_set(m3,1,1,e1+e5-e3-e7);
}
return m3;
}

