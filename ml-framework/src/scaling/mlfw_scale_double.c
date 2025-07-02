#include<mlfw_matrix.h>
#include<mlfw_scale.h>
#include<stdio.h>
#include<stdlib.h>

mlfw_mat_double *mlfw_scale_double_min_max(mlfw_mat_double *matrix,index_t start_row_index,index_t start_column_index,index_t end_row_index,index_t end_column_index,char *min_max_file,mlfw_mat_double *new_matrix)
{
FILE *file;
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
if(matrix==NULL) return NULL;
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
max=(double *)malloc(sizeof(double)*new_matrix_columns);
if(max==NULL)
{
mlfw_mat_double_destroy(new_matrix);
return NULL;
}
min=(double *)malloc(sizeof(double)*new_matrix_columns);
if(min==NULL)
{
mlfw_mat_double_destroy(new_matrix);
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

file=fopen(min_max_file,"w");
if(file==NULL) 
{
free(min);
free(max);
mlfw_mat_double_destroy(new_matrix);
return NULL;
}
for(i=start_column_index;i<end_column_index;i++)
{
fprintf(file,"column_%d",i);
if(i==new_matrix_columns-1) fputc('\n',file);
else fputc(',',file);
}
for(i=0;i<new_matrix_columns;i++)
{
fprintf(file,"%lf",min[i]);
if(i==new_matrix_columns-1) fputc('\n',file);
else fputc(',',file);
}
for(i=0;i<new_matrix_columns;i++)
{
fprintf(file,"%lf",max[i]);
if(i==new_matrix_columns-1) fputc('\n',file);
else fputc(',',file);
}
fclose(file);
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

mlfw_mat_double *mlfw_scale_double_z_score(mlfw_mat_double *matrix,index_t start_row_index,index_t start_column_index,index_t end_row_index,index_t end_column_index,char *mean_standard_deviation,mlfw_mat_double *new_matrix)
{
FILE *file;
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
if(matrix==NULL) return NULL;
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
mean=(double *)malloc(sizeof(double)*new_matrix_columns);
if(mean==NULL)
{
mlfw_mat_double_destroy(new_matrix);
return NULL;
}
standard_deviation=(double *)malloc(sizeof(double)*new_matrix_columns);
if(standard_deviation==NULL)
{
mlfw_mat_double_destroy(new_matrix);
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

file=fopen(mean_standard_deviation,"w");
if(file==NULL) 
{
free(mean);
free(standard_deviation);
mlfw_mat_double_destroy(new_matrix);
return NULL;
}
for(i=start_column_index;i<end_column_index;i++)
{
fprintf(file,"column_%d",i);
if(i==new_matrix_columns-1) fputc('\n',file);
else fputc(',',file);
}
for(i=0;i<new_matrix_columns;i++)
{
fprintf(file,"%lf",mean[i]);
if(i==new_matrix_columns-1) fputc('\n',file);
else fputc(',',file);
}
for(i=0;i<new_matrix_columns;i++)
{
fprintf(file,"%lf",standard_deviation[i]);
if(i==new_matrix_columns-1) fputc('\n',file);
else fputc(',',file);
}
fclose(file);
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

