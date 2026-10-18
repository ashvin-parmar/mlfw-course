#include <stdio.h>
#include <math.h>
#include <mlfw_math.h>

mlfw_column_vec_double * mlfw_column_vec_double_sigmoid(mlfw_column_vec_double *vector,mlfw_column_vec_double *new_vector)
{
	dimension_t vector_size;
	dimension_t new_vector_size;
	index_t i;
	double value, sigmoid, e;
	mlfw_column_vec_double *v;
	if(vector==NULL) return NULL;
	vector_size=mlfw_column_vec_double_get_size(vector);
	if(new_vector==NULL)
	{
		v=mlfw_column_vec_double_create_new(vector_size);
		if(v==NULL) return NULL;
	}
	else
	{
		new_vector_size=mlfw_column_vec_double_get_size(new_vector);
		if(new_vector_size!=vector_size)
		{
			return NULL;
		}
		v=new_vector;
	}
	e=2.718281;
	for(i=0;i<vector_size;i++)
	{
		value=mlfw_column_vec_double_get(vector,i);
		sigmoid=1/(1+pow(e,-value));
		mlfw_column_vec_double_set(v,i,sigmoid);
	}
	return v;
}

mlfw_column_vec_double * mlfw_column_vec_double_log(mlfw_column_vec_double *vector,mlfw_column_vec_double *new_vector)
{
	dimension_t vector_size;
	dimension_t new_vector_size;
	index_t i;
	double value, log_value;
	mlfw_column_vec_double *v;
	if(vector==NULL) return NULL;
	vector_size=mlfw_column_vec_double_get_size(vector);
	if(new_vector==NULL)
	{
		v=mlfw_column_vec_double_create_new(vector_size);
		if(v==NULL) return NULL;
	}
	else
	{
		new_vector_size=mlfw_column_vec_double_get_size(new_vector);
		if(new_vector_size!=vector_size)
		{
			return NULL;
		}
		v=new_vector;
	}
	for(i=0;i<vector_size;i++)
	{
		value=mlfw_column_vec_double_get(vector,i);
		log_value=log(value);
		mlfw_column_vec_double_set(v,i,log_value);
	}
	return v;
}

double mlfw_column_vec_double_sum(mlfw_column_vec_double *vector)
{
	index_t i;
	dimension_t vector_size;
	double sum,value;
	sum=0.0;
	if(vector==NULL) return sum;
	vector_size=mlfw_column_vec_double_get_size(vector);
	for(i=0;i<vector_size;i++)
	{	
		value=mlfw_column_vec_double_get(vector,i);
		sum+=value;
	}
	return sum;
}

