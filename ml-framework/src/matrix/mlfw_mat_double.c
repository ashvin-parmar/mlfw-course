#include<mlfw_matrix.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct __mlfw_mat_double
{
double **data;
dimension_t rows;
dimension_t columns; 
}mlfw_mat_double;
mlfw_mat_double * mlfw_mat_double_create_new(dimension_t rows,dimension_t columns)
{
mlfw_mat_double *matrix;
index_t r,c;
if(rows<=0 || columns<=0) return NULL;
matrix=(mlfw_mat_double *)malloc(sizeof(mlfw_mat_double));
if(matrix==NULL) return NULL;
matrix->data=(double **)malloc(sizeof(double *)*rows);
if(matrix->data==NULL)
{
free(matrix);
return NULL;
}
for(r=0;r<rows;r++)
{
matrix->data[r]=(double *)malloc(sizeof(double)*columns);
if(matrix->data[r]==NULL)
{
for(c=0;c<r;c++) free(matrix->data[c]);
free(matrix->data);
free(matrix);
return NULL;
}
}
matrix->rows=rows;
matrix->columns=columns;
return matrix;
}
void mlfw_mat_double_destroy(mlfw_mat_double *matrix)
{
index_t i;
if(matrix==NULL) return;
for(i=0;i<matrix->rows;i++) free(matrix->data[i]);
free(matrix->data);
free(matrix);
matrix=NULL;
}
mlfw_mat_double * mlfw_mat_double_from_csv(const char *csv_file_name)
{
index_t r,c;
dimension_t rows,columns;
mlfw_mat_double *matrix;
double value;
int index;
char m;
char double_string[1025];
FILE *file;

file=fopen(csv_file_name,"r");
if(file==NULL)
{
return NULL;
}
rows=0;
columns=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(rows==0 && m==',') columns++;
if(m=='\n') rows++;
}
columns++;
matrix=(mlfw_mat_double *)mlfw_mat_double_create_new(rows,columns);
if(matrix==NULL)
{
fclose(file);
return NULL;
}
rewind(file);
r=0;
c=0;
index=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m==',' || m=='\n')
{
double_string[index]='\0';
value=strtod(double_string,NULL);
index=0;
matrix->data[r][c]=value;
c++;
if(matrix->columns==c)
{
c=0;
r++;
}
}
else
{
double_string[index]=m;
index++;
}
}
fclose(file);
return matrix;
}
double mlfw_mat_double_get(mlfw_mat_double *matrix,index_t row,index_t column)
{
double value=0.0;
if(matrix==NULL) return value;
if(row<0 || row>=matrix->rows || column<0 || column>=matrix->columns) return value;
value=matrix->data[row][column];
return value;
}
void mlfw_mat_double_set(mlfw_mat_double *matrix,index_t row,index_t column,double value)
{
if(matrix==NULL) return ;
if(row<0 || row>=matrix->rows || column<0 || column>=matrix->columns) return;
matrix->data[row][column]=value;
}
void mlfw_mat_double_get_dimension(mlfw_mat_double *matrix,dimension_t *rows,dimension_t *columns)
{
*rows=0;
*columns=0;
if(matrix==NULL);
*rows=matrix->rows;
*columns=matrix->columns; 
}
void mlfw_mat_double_copy(mlfw_mat_double *target,mlfw_mat_double *source,index_t from_target_row_index,index_t from_target_column_index,index_t from_source_row_index,index_t from_source_column_index,index_t to_source_row_index,index_t to_source_column_index)
{
}
mlfw_column_vec_double * mlfw_mat_double_create_column_vec(mlfw_mat_double *matrix,index_t column_index)
{
return NULL;
}
void mlfw_mat_double_fill(mlfw_mat_double *matrix,index_t from_row_index,index_t from_column_index,index_t to_row_index,index_t to_column_index,double value)
{
}
