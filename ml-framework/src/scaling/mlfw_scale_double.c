#include<mlfw_matrix.h>
#include<mlfw_scale.h>
#include<stdio.h>
#include<stdlib.h>
#include<mlfw_utils.h>
mlfw_mat_double *mlfw_scale_double_min_max(mlfw_mat_double *matrix,index_t start_row_index,index_t start_column_index,index_t end_row_index,index_t end_column_index,mlfw_mat_double **min_max_matrix,mlfw_mat_double *new_matrix)
{
double scaled_value;
double value;
dimension_t matrix_rows,matrix_columns;
dimension_t new_matrix_rows,new_matrix_columns;
dimension_t new_matrix_rows_known,new_matrix_columns_known;
double *max;
double *min;
index_t r,c;
index_t i;
index_t new_matrix_r,new_matrix_c;
if(matrix==NULL || min_max_matrix==NULL) return NULL;
mlfw_mat_double_get_dimension(matrix,&matrix_rows,&matrix_columns);

if(start_row_index<0 || end_row_index>=matrix_rows) return NULL;
if(start_column_index<0 || end_column_index>=matrix_columns) return NULL;
if(start_row_index>end_row_index || start_column_index>end_column_index) return NULL;
new_matrix_rows=end_row_index-start_row_index+1;
new_matrix_columns=end_column_index-start_column_index+1;
if(new_matrix==NULL)
{
new_matrix=mlfw_mat_double_create_new(new_matrix_rows,new_matrix_columns);
if(new_matrix==NULL) return NULL;
}
else
{
mlfw_mat_double_get_dimension(new_matrix,&new_matrix_rows_known,&new_matrix_columns_known);
if(new_matrix_rows_known!=new_matrix_rows || new_matrix_columns_known!=new_matrix_columns) return NULL;
}
*min_max_matrix=mlfw_mat_double_create_new(2,new_matrix_columns);
if(*min_max_matrix==NULL)
{
mlfw_mat_double_destroy(new_matrix);
return NULL;
}
max=(double *)malloc(sizeof(double)*new_matrix_columns);
if(max==NULL)
{
mlfw_mat_double_destroy(new_matrix);
mlfw_mat_double_destroy(*min_max_matrix);
*min_max_matrix=NULL;
return NULL;
}
min=(double *)malloc(sizeof(double)*new_matrix_columns);
if(min==NULL)
{
mlfw_mat_double_destroy(new_matrix);
mlfw_mat_double_destroy(*min_max_matrix);
*min_max_matrix=NULL;
free(max);
return NULL;
}
i=0;
for(c=start_column_index;c<=end_column_index;c++)
{
min[i]=mlfw_mat_double_get_minimum(matrix,start_row_index,end_row_index,c,c);
max[i]=mlfw_mat_double_get_maximum(matrix,start_row_index,end_row_index,c,c);	//As per column (c,c)
i++;
}
r=start_row_index;
for(new_matrix_r=0;new_matrix_r<new_matrix_rows;new_matrix_r++)
{
c=start_column_index;
for(new_matrix_c=0;new_matrix_c<new_matrix_columns;new_matrix_c++)
{
value=mlfw_mat_double_get(matrix,r,c);
scaled_value=(value-min[new_matrix_c])/(max[new_matrix_c]-min[new_matrix_c]);
mlfw_mat_double_set(new_matrix,new_matrix_r,new_matrix_c,scaled_value);
++c;
}
++r;
}

for(i=0;i<new_matrix_columns;i++)
{
mlfw_mat_double_set(*min_max_matrix,0,i,min[i]);
mlfw_mat_double_set(*min_max_matrix,1,i,max[i]);
}
free(min);
free(max);
return new_matrix;
}

mlfw_mat_double *mlfw_scale_double_with_given_min_max(mlfw_mat_double *matrix,index_t start_row_index,index_t start_column_index,index_t end_row_index,index_t end_column_index,mlfw_mat_double *min_max_matrix,mlfw_mat_double *new_matrix)
{
double scaled_value;
double value;
dimension_t matrix_rows,matrix_columns;
dimension_t min_max_rows,min_max_columns;
dimension_t new_matrix_rows,new_matrix_columns;
dimension_t new_matrix_rows_known,new_matrix_columns_known;
double max;
double min;
index_t r,c;
index_t new_matrix_r,new_matrix_c;
if(matrix==NULL || min_max_matrix==NULL) return NULL;
mlfw_mat_double_get_dimension(matrix,&matrix_rows,&matrix_columns);
mlfw_mat_double_get_dimension(min_max_matrix,&min_max_rows,&min_max_columns);
if(min_max_rows!=2) return NULL;
if(start_row_index<0 || end_row_index>=matrix_rows) return NULL;
if(start_column_index<0 || end_column_index>=matrix_columns) return NULL;
if(start_row_index>end_row_index || start_column_index>end_column_index) return NULL;
new_matrix_rows=end_row_index-start_row_index+1;
new_matrix_columns=end_column_index-start_column_index+1;
if(min_max_columns!=new_matrix_columns) return NULL;
if(new_matrix==NULL)
{
new_matrix=mlfw_mat_double_create_new(new_matrix_rows,new_matrix_columns);
if(new_matrix==NULL) return NULL;
}
else
{
mlfw_mat_double_get_dimension(new_matrix,&new_matrix_rows_known,&new_matrix_columns_known);
if(new_matrix_rows_known!=new_matrix_rows || new_matrix_columns_known!=new_matrix_columns) return NULL;
}
r=start_row_index;
for(new_matrix_r=0;new_matrix_r<new_matrix_rows;new_matrix_r++)
{
c=start_column_index;
for(new_matrix_c=0;new_matrix_c<new_matrix_columns;new_matrix_c++)
{
min=mlfw_mat_double_get(min_max_matrix,0,new_matrix_c);
max=mlfw_mat_double_get(min_max_matrix,1,new_matrix_c);
value=mlfw_mat_double_get(matrix,r,c);
scaled_value=(value-min)/(max-min);
mlfw_mat_double_set(new_matrix,new_matrix_r,new_matrix_c,scaled_value);
++c;
}
++r;
}
return new_matrix;
}

mlfw_mat_double *mlfw_scale_double_z_score(mlfw_mat_double *matrix,index_t start_row_index,index_t start_column_index,index_t end_row_index,index_t end_column_index,mlfw_mat_double **mean_standard_deviation_matrix,mlfw_mat_double *new_matrix)
{
double scaled_value;
double value;
dimension_t matrix_rows,matrix_columns;
dimension_t new_matrix_rows,new_matrix_columns;
dimension_t new_matrix_rows_known,new_matrix_columns_known;
double *mean;
double *standard_deviation;
index_t r,c;
index_t i;
index_t new_matrix_r,new_matrix_c;
if(matrix==NULL || mean_standard_deviation_matrix==NULL) return NULL;
mlfw_mat_double_get_dimension(matrix,&matrix_rows,&matrix_columns);

if(start_row_index<0 || end_row_index>=matrix_rows) return NULL;
if(start_column_index<0 || end_column_index>=matrix_columns) return NULL;
if(start_row_index>end_row_index || start_column_index>end_column_index) return NULL;
new_matrix_rows=end_row_index-start_row_index+1;
new_matrix_columns=end_column_index-start_column_index+1;
if(new_matrix==NULL)
{
new_matrix=mlfw_mat_double_create_new(new_matrix_rows,new_matrix_columns);
if(new_matrix==NULL) return NULL;
}
else
{
mlfw_mat_double_get_dimension(new_matrix,&new_matrix_rows_known,&new_matrix_columns_known);
if(new_matrix_rows_known!=new_matrix_rows || new_matrix_columns_known!=new_matrix_columns) return NULL;
}
*mean_standard_deviation_matrix=mlfw_mat_double_create_new(2,new_matrix_columns);
if(*mean_standard_deviation_matrix==NULL)
{
mlfw_mat_double_destroy(new_matrix);
return NULL;
}
mean=(double *)malloc(sizeof(double)*new_matrix_columns);
if(mean==NULL)
{
mlfw_mat_double_destroy(new_matrix);
mlfw_mat_double_destroy(*mean_standard_deviation_matrix);
*mean_standard_deviation_matrix=NULL;
return NULL;
}
standard_deviation=(double *)malloc(sizeof(double)*new_matrix_columns);
if(standard_deviation==NULL)
{
mlfw_mat_double_destroy(new_matrix);
mlfw_mat_double_destroy(*mean_standard_deviation_matrix);
*mean_standard_deviation_matrix=NULL;
free(mean);
return NULL;
}
i=0;
for(c=start_column_index;c<=end_column_index;c++)
{
mean[i]=mlfw_mat_double_get_mean(matrix,start_row_index,end_row_index,c,c);
standard_deviation[i]=mlfw_mat_double_get_standard_deviation(matrix,start_row_index,end_row_index,c,c);	//As per column (c,c)
i++;
}
r=start_row_index;
for(new_matrix_r=0;new_matrix_r<new_matrix_rows;new_matrix_r++)
{
c=start_column_index;
for(new_matrix_c=0;new_matrix_c<new_matrix_columns;new_matrix_c++)
{
value=mlfw_mat_double_get(matrix,r,c);
scaled_value=(value-mean[new_matrix_c])/(standard_deviation[new_matrix_c]);
mlfw_mat_double_set(new_matrix,new_matrix_r,new_matrix_c,scaled_value);
++c;
}
++r;
}

for(i=0;i<new_matrix_columns;i++)
{
mlfw_mat_double_set(*mean_standard_deviation_matrix,0,i,mean[i]);
mlfw_mat_double_set(*mean_standard_deviation_matrix,1,i,standard_deviation[i]);
}
free(mean);
free(standard_deviation);
return new_matrix;
}

mlfw_mat_double *mlfw_scale_double_z_score_with_given_mean_standard_deviation(mlfw_mat_double *matrix,index_t start_row_index,index_t start_column_index,index_t end_row_index,index_t end_column_index,mlfw_mat_double *mean_standard_deviation,mlfw_mat_double *new_matrix)
{
double scaled_value;
double value;
dimension_t matrix_rows,matrix_columns;
dimension_t mean_standard_deviation_rows,mean_standard_deviation_columns;
dimension_t new_matrix_rows,new_matrix_columns;
dimension_t new_matrix_rows_known,new_matrix_columns_known;
double mean;
double standard_deviation;
index_t r,c;
index_t new_matrix_r,new_matrix_c;
if(matrix==NULL || mean_standard_deviation==NULL) return NULL;
mlfw_mat_double_get_dimension(matrix,&matrix_rows,&matrix_columns);
mlfw_mat_double_get_dimension(mean_standard_deviation,&mean_standard_deviation_rows,&mean_standard_deviation_columns);
if(mean_standard_deviation_rows!=2) return NULL;
if(start_row_index<0 || end_row_index>=matrix_rows) return NULL;
if(start_column_index<0 || end_column_index>=matrix_columns) return NULL;
if(start_row_index>end_row_index || start_column_index>end_column_index) return NULL;
new_matrix_rows=end_row_index-start_row_index+1;
new_matrix_columns=end_column_index-start_column_index+1;
if(mean_standard_deviation_columns!=new_matrix_columns) return NULL;
if(new_matrix==NULL)
{
new_matrix=mlfw_mat_double_create_new(new_matrix_rows,new_matrix_columns);
if(new_matrix==NULL) return NULL;
}
else
{
mlfw_mat_double_get_dimension(new_matrix,&new_matrix_rows_known,&new_matrix_columns_known);
if(new_matrix_rows_known!=new_matrix_rows || new_matrix_columns_known!=new_matrix_columns) return NULL;
}
r=start_row_index;
for(new_matrix_r=0;new_matrix_r<new_matrix_rows;new_matrix_r++)
{
c=start_column_index;
for(new_matrix_c=0;new_matrix_c<new_matrix_columns;new_matrix_c++)
{
mean=mlfw_mat_double_get(mean_standard_deviation,0,new_matrix_c);
standard_deviation=mlfw_mat_double_get(mean_standard_deviation,1,new_matrix_c);
value=mlfw_mat_double_get(matrix,r,c);
scaled_value=(value-mean)/(standard_deviation);
mlfw_mat_double_set(new_matrix,new_matrix_r,new_matrix_c,scaled_value);
++c;
}
++r;
}
return new_matrix;
}

mlfw_mat_double *mlfw_scale_double(const char *dataset_file_name,mlfw_row_vec_string *columns_to_scale,const char *parameter_file_name,const char *algorithm_name)
{
mlfw_mat_double *matrix;
dimension_t matrix_rows,matrix_columns;
mlfw_row_vec_string *matrix_header;
dimension_t matrix_header_size;
dimension_t columns_to_scale_size;

mlfw_mat_double *parameters_matrix;
mlfw_mat_double *scaled_matrix;
mlfw_mat_double *tmp_matrix;

uint8_t algorithm_code=0;
uint8_t MIN_MAX_ALGORITHM=1;
uint8_t Z_SCORE_ALGORITHM=2;

char *header_column_name,*column_name;
dimension_t i,j;
if(dataset_file_name==NULL || columns_to_scale==NULL || parameter_file_name==NULL || algorithm_name==NULL) return NULL;

if(mlfw_strcmp_case_insensitive(algorithm_name,"min-max")==0)
{
algorithm_code=MIN_MAX_ALGORITHM;
}
else if(mlfw_strcmp_case_insensitive(algorithm_name,"z-score")==0)
{
algorithm_code=Z_SCORE_ALGORITHM;
}
else
{
return NULL;
}

columns_to_scale_size=mlfw_row_vec_string_get_size(columns_to_scale);
if(columns_to_scale_size==0) return NULL; 
if(algorithm_code==MIN_MAX_ALGORITHM)
{
parameters_matrix=mlfw_mat_double_create_new(2,columns_to_scale_size);
if(parameters_matrix==NULL) return NULL;
}
else if(algorithm_code==Z_SCORE_ALGORITHM)
{
parameters_matrix=mlfw_mat_double_create_new(2,columns_to_scale_size);
if(parameters_matrix==NULL) return NULL;
}
//MORE TO ADD HERE (later on)

matrix=mlfw_mat_double_from_csv(dataset_file_name,NULL,&matrix_header);
if(matrix==NULL)
{
mlfw_mat_double_destroy(parameters_matrix);
return NULL;
}
mlfw_mat_double_get_dimension(matrix,&matrix_rows,&matrix_columns);
matrix_header_size=mlfw_row_vec_string_get_size(matrix_header);

scaled_matrix=mlfw_mat_double_create_new(matrix_rows,1);
if(scaled_matrix==NULL)
{
mlfw_mat_double_destroy(parameters_matrix);
mlfw_mat_double_destroy(matrix);
mlfw_row_vec_string_destroy(matrix_header);
return NULL;
}

for(i=0;i<columns_to_scale_size;++i)
{
mlfw_row_vec_string_get(columns_to_scale,i,&column_name);
if(column_name==NULL)
{
// if fails releease and return 
mlfw_mat_double_destroy(parameters_matrix);
mlfw_mat_double_destroy(matrix);
mlfw_mat_double_destroy(scaled_matrix);
mlfw_row_vec_string_destroy(matrix_header);
return NULL;
}
for(j=0;j<matrix_header_size;j++)
{
mlfw_row_vec_string_get(matrix_header,j,&header_column_name);
if(header_column_name==NULL)
{
//if header_column_name==null release and return 
mlfw_mat_double_destroy(parameters_matrix);
mlfw_mat_double_destroy(matrix);
mlfw_mat_double_destroy(scaled_matrix);
mlfw_row_vec_string_destroy(matrix_header);
free(column_name);
return NULL;
}
if(mlfw_strcmp_case_insensitive(header_column_name,column_name)==0)
{
//sacle j-th column
if(algorithm_code==MIN_MAX_ALGORITHM)
{
if(mlfw_scale_double_min_max(matrix,0,j,matrix_rows-1,j,&tmp_matrix,scaled_matrix)!=NULL)
{
//scale min-max matrix created 
mlfw_mat_double_copy(matrix,scaled_matrix,0,j,0,0,matrix_rows-1,0);
mlfw_mat_double_set(parameters_matrix,0,i,mlfw_mat_double_get(tmp_matrix,0,0));
mlfw_mat_double_set(parameters_matrix,1,i,mlfw_mat_double_get(tmp_matrix,1,0));
mlfw_mat_double_destroy(tmp_matrix);
}
else
{
//release all resources and return NULL
mlfw_mat_double_destroy(parameters_matrix);
mlfw_mat_double_destroy(matrix);
mlfw_mat_double_destroy(scaled_matrix);
mlfw_row_vec_string_destroy(matrix_header);
free(column_name);
free(header_column_name);
return NULL;
}
}
else if(algorithm_code==Z_SCORE_ALGORITHM)
{
if(mlfw_scale_double_z_score(matrix,0,j,matrix_rows-1,j,&tmp_matrix,scaled_matrix)!=NULL)
{
//scale z-score matrix
mlfw_mat_double_copy(matrix,scaled_matrix,0,j,0,0,matrix_rows-1,0);
mlfw_mat_double_set(parameters_matrix,0,i,mlfw_mat_double_get(tmp_matrix,0,0));
mlfw_mat_double_set(parameters_matrix,1,i,mlfw_mat_double_get(tmp_matrix,1,0));
mlfw_mat_double_destroy(tmp_matrix);
}
else
{
//release all resources and return NULL
mlfw_mat_double_destroy(parameters_matrix);
mlfw_mat_double_destroy(matrix);
mlfw_mat_double_destroy(scaled_matrix);
mlfw_row_vec_string_destroy(matrix_header);
free(column_name);
free(header_column_name);
return NULL;
}
}
free(header_column_name);
break; 
}
free(header_column_name);
} //inner loop ends
free(column_name);
if(j==matrix_header_size)
{
//release and return [Column not found]
mlfw_mat_double_destroy(parameters_matrix);
mlfw_mat_double_destroy(matrix);
mlfw_mat_double_destroy(scaled_matrix);
mlfw_row_vec_string_destroy(matrix_header);
return NULL;
}
}//outer loop ends
mlfw_mat_double_to_csv(parameters_matrix,parameter_file_name,columns_to_scale);

mlfw_mat_double_destroy(scaled_matrix);
mlfw_mat_double_destroy(parameters_matrix);
mlfw_row_vec_string_destroy(matrix_header);
return matrix;
}
mlfw_mat_double *mlfw_scale_double_with_given_parameters(const char *dataset_file_name,const char *parameter_file_name,const char *algorithm_name)
{
mlfw_mat_double *matrix;
mlfw_row_vec_string *columns_to_scale;
dimension_t matrix_rows,matrix_columns;
mlfw_row_vec_string *matrix_header;
dimension_t matrix_header_size;
dimension_t columns_to_scale_size;

mlfw_mat_double *parameters_matrix;
dimension_t parameters_matrix_rows,parameters_matrix_columns;
mlfw_mat_double *scaled_matrix;
mlfw_mat_double *tmp_matrix;

uint8_t algorithm_code=0;
uint8_t MIN_MAX_ALGORITHM=1;
uint8_t Z_SCORE_ALGORITHM=2;

char *header_column_name,*column_name;
dimension_t i,j;
if(dataset_file_name==NULL || columns_to_scale==NULL || parameter_file_name==NULL || algorithm_name==NULL) return NULL;

if(mlfw_strcmp_case_insensitive(algorithm_name,"min-max")==0)
{
algorithm_code=MIN_MAX_ALGORITHM;
}
else if(mlfw_strcmp_case_insensitive(algorithm_name,"z-score")==0)
{
algorithm_code=Z_SCORE_ALGORITHM;
}
else
{
return NULL;
}
parameters_matrix=mlfw_mat_double_from_csv(parameter_file_name,NULL,&columns_to_scale);
if(parameters_matrix==NULL) return NULL;

columns_to_scale_size=mlfw_row_vec_string_get_size(columns_to_scale);
if(columns_to_scale_size==0) return NULL; 

matrix=mlfw_mat_double_from_csv(dataset_file_name,NULL,&matrix_header);
if(matrix==NULL)
{
mlfw_mat_double_destroy(parameters_matrix);
mlfw_row_vec_string_destroy(columns_to_scale);
return NULL;
}
mlfw_mat_double_get_dimension(matrix,&matrix_rows,&matrix_columns);
matrix_header_size=mlfw_row_vec_string_get_size(matrix_header);

scaled_matrix=mlfw_mat_double_create_new(matrix_rows,1);
if(scaled_matrix==NULL)
{
mlfw_mat_double_destroy(parameters_matrix);
mlfw_mat_double_destroy(matrix);
mlfw_row_vec_string_destroy(matrix_header);
mlfw_row_vec_string_destroy(columns_to_scale);
return NULL;
}
mlfw_mat_double_get_dimension(parameters_matrix,&parameters_matrix_rows,&parameters_matrix_columns);
tmp_matrix=mlfw_mat_double_create_new(parameters_matrix_rows,1);
if(tmp_matrix==NULL)
{
mlfw_mat_double_destroy(parameters_matrix);
mlfw_mat_double_destroy(matrix);
mlfw_row_vec_string_destroy(matrix_header);
mlfw_row_vec_string_destroy(columns_to_scale);
mlfw_mat_double_destroy(scaled_matrix);
return NULL;
}
for(i=0;i<columns_to_scale_size;++i)
{
mlfw_row_vec_string_get(columns_to_scale,i,&column_name);
if(column_name==NULL)
{
// if fails releease and return 
mlfw_mat_double_destroy(parameters_matrix);
mlfw_mat_double_destroy(matrix);
mlfw_mat_double_destroy(scaled_matrix);
mlfw_row_vec_string_destroy(matrix_header);
mlfw_row_vec_string_destroy(columns_to_scale);
mlfw_mat_double_destroy(tmp_matrix);
return NULL;
}
for(j=0;j<matrix_header_size;j++)
{
mlfw_row_vec_string_get(matrix_header,j,&header_column_name);
if(header_column_name==NULL)
{
//if header_column_name==null release and return 
mlfw_mat_double_destroy(parameters_matrix);
mlfw_mat_double_destroy(matrix);
mlfw_mat_double_destroy(scaled_matrix);
mlfw_row_vec_string_destroy(matrix_header);
mlfw_row_vec_string_destroy(columns_to_scale);
mlfw_mat_double_destroy(tmp_matrix);
free(column_name);
return NULL;
}
if(mlfw_strcmp_case_insensitive(header_column_name,column_name)==0)
{
//sacle j-th column
if(algorithm_code==MIN_MAX_ALGORITHM)
{
mlfw_mat_double_set(tmp_matrix,0,0,mlfw_mat_double_get(parameters_matrix,0,i));
mlfw_mat_double_set(tmp_matrix,1,0,mlfw_mat_double_get(parameters_matrix,1,i));
if(mlfw_scale_double_with_given_min_max(matrix,0,j,matrix_rows-1,j,tmp_matrix,scaled_matrix)!=NULL)
{
//scale min-max matrix created 
mlfw_mat_double_copy(matrix,scaled_matrix,0,j,0,0,matrix_rows-1,0);
}
else
{
//release all resources and return NULL
mlfw_mat_double_destroy(parameters_matrix);
mlfw_mat_double_destroy(matrix);
mlfw_mat_double_destroy(scaled_matrix);
mlfw_row_vec_string_destroy(matrix_header);
mlfw_row_vec_string_destroy(columns_to_scale);
mlfw_mat_double_destroy(tmp_matrix);
free(column_name);
free(header_column_name);
return NULL;
}
}
else if(algorithm_code==Z_SCORE_ALGORITHM)
{
mlfw_mat_double_set(tmp_matrix,0,0,mlfw_mat_double_get(parameters_matrix,0,i));
mlfw_mat_double_set(tmp_matrix,1,0,mlfw_mat_double_get(parameters_matrix,1,i));
if(mlfw_scale_double_z_score_with_given_mean_standard_deviation(matrix,0,j,matrix_rows-1,j,tmp_matrix,scaled_matrix)!=NULL)
{
//scale z-score matrix
mlfw_mat_double_copy(matrix,scaled_matrix,0,j,0,0,matrix_rows-1,0);
}
else
{
//release all resources and return NULL
mlfw_mat_double_destroy(parameters_matrix);
mlfw_mat_double_destroy(matrix);
mlfw_mat_double_destroy(scaled_matrix);
mlfw_row_vec_string_destroy(matrix_header);
mlfw_row_vec_string_destroy(columns_to_scale);
mlfw_mat_double_destroy(tmp_matrix);
free(column_name);
free(header_column_name);
return NULL;
}
}
free(header_column_name);
break; 
}
free(header_column_name);
} //inner loop ends
free(column_name);
if(j==matrix_header_size)
{
//release and return [Column not found]
mlfw_mat_double_destroy(parameters_matrix);
mlfw_mat_double_destroy(matrix);
mlfw_mat_double_destroy(scaled_matrix);
mlfw_row_vec_string_destroy(matrix_header);
mlfw_row_vec_string_destroy(columns_to_scale);
mlfw_mat_double_destroy(tmp_matrix);
return NULL;
}
}//outer loop ends

mlfw_mat_double_destroy(scaled_matrix);
mlfw_mat_double_destroy(parameters_matrix);
mlfw_row_vec_string_destroy(matrix_header);
mlfw_row_vec_string_destroy(columns_to_scale);
mlfw_mat_double_destroy(tmp_matrix);
return matrix;
}
