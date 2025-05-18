#include<mlfw_matrix.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
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
mlfw_mat_double * mlfw_mat_double_create_new_filled(dimension_t rows,dimension_t columns,double value,mlfw_mat_double *matrix)
{
index_t r,c;
if(rows<=0 || columns<=0) return NULL;
if(matrix==NULL)
{
matrix=mlfw_mat_double_create_new(rows,columns);
if(matrix==NULL) return NULL;
}
else
{
if(matrix->rows!=rows || matrix->columns!=columns) return NULL;
}
for(r=0;r<rows;r++)
{
for(c=0;c<columns;c++)
{
matrix->data[r][c]=value;
}
}
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
mlfw_mat_double * mlfw_mat_double_from_csv(const char *csv_file_name,mlfw_mat_double *matrix)
{
index_t r,c;
dimension_t rows,columns;
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
if(matrix==NULL)
{
matrix=(mlfw_mat_double *)mlfw_mat_double_create_new(rows,columns);
if(matrix==NULL)
{
fclose(file);
return NULL;
}
}
else
{
if(matrix->columns!=columns || matrix->rows!=rows)
{
fclose(file);
return NULL;
}
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
if(matrix==NULL);
if(rows!=NULL) *rows=matrix->rows;
if(columns!=NULL) *columns=matrix->columns; 
}
void mlfw_mat_double_copy(mlfw_mat_double *target,mlfw_mat_double *source,index_t from_target_row_index,index_t from_target_column_index,index_t from_source_row_index,index_t from_source_column_index,index_t to_source_row_index,index_t to_source_column_index)
{
dimension_t target_rows;
dimension_t target_columns;
dimension_t source_rows;
dimension_t source_columns;
index_t target_r,target_c;
index_t source_r,source_c;
if(target==NULL || source==NULL) return;
mlfw_mat_double_get_dimension(target,&target_rows,&target_columns);
mlfw_mat_double_get_dimension(source,&source_rows,&source_columns);

if(from_target_row_index<0 || from_target_row_index>=target_rows) return;
if(from_target_column_index<0 || from_target_column_index>=target_columns) return;

if(from_source_row_index<0 || from_source_row_index>=source_rows) return;
if(from_source_column_index<0 || from_source_column_index>=source_columns) return;   
if(to_source_row_index<0 || to_source_row_index>=source_rows) return;
if(to_source_column_index<0 || to_source_column_index>=source_columns) return;   
if(from_source_row_index>to_source_row_index) return ;
if(from_source_column_index>to_source_column_index) return;

for(target_r=from_target_row_index,source_r=from_source_row_index;source_r<=to_source_row_index;target_r++,source_r++)
{
for(target_c=from_target_column_index,source_c=from_source_column_index;source_c<=to_source_column_index;target_c++,source_c++)
{
if(target_c>=0 && target_r>=0 && target_r<target_rows && target_c<target_columns)
{
mlfw_mat_double_set(target,target_r,target_c,mlfw_mat_double_get(source,source_r,source_c));
}
}
}
}
mlfw_column_vec_double * mlfw_mat_double_create_column_vec(mlfw_mat_double *matrix,index_t column_index,mlfw_column_vec_double *vector)
{
dimension_t matrix_columns;
dimension_t matrix_rows;
index_t r,c;
if(matrix==NULL) return NULL;
mlfw_mat_double_get_dimension(matrix,&matrix_rows,&matrix_columns);
if(column_index>=matrix_columns || column_index<0) return NULL;
if(vector==NULL)
{
vector=mlfw_column_vec_double_create_new(matrix_rows);
if(vector==NULL) return NULL;
}
else
{
if(mlfw_column_vec_double_get_size(vector)!=matrix_rows) return NULL;
}
c=column_index;
for(r=0;r<matrix_rows;r++)
{
mlfw_column_vec_double_set(vector,r,mlfw_mat_double_get(matrix,r,c));
}
return vector;
}
void mlfw_mat_double_fill(mlfw_mat_double *matrix,index_t from_row_index,index_t from_column_index,index_t to_row_index,index_t to_column_index,double value)
{
dimension_t matrix_rows;
dimension_t matrix_columns;
index_t r,c;
if(matrix==NULL) return;
mlfw_mat_double_get_dimension(matrix,&matrix_rows,&matrix_columns);
if(from_row_index<0 || from_row_index>=matrix_rows) return;
if(from_column_index<0 || from_column_index>=matrix_columns) return;
if(to_row_index<0 || to_row_index>=matrix_rows) return;
if(to_column_index<0 || to_column_index>=matrix_columns) return;

if(from_row_index>to_row_index) return;
if(from_column_index>to_column_index) return; 

for(r=from_row_index;r<=to_row_index;r++)
{
for(c=from_column_index;c<=to_column_index;c++)
{
mlfw_mat_double_set(matrix,r,c,value);
}
}
}
void mlfw_mat_double_to_csv(mlfw_mat_double *matrix,const char * csv_file_name)
{
index_t r,c;
char seperator;
FILE *file;
if(matrix==NULL || csv_file_name==NULL) return;
file=fopen(csv_file_name,"w");
if(file==NULL) return;
for(r=0;r<matrix->rows;r++)
{
for(c=0;c<matrix->columns;c++)
{
fprintf(file,"%lf",matrix->data[r][c]);
if(c==matrix->columns-1)
{
seperator='\n';
}
else
{
seperator=',';
}
fputc(seperator,file);
}
}
fclose(file);
}
mlfw_mat_double * mlfw_mat_double_shuffle(mlfw_mat_double *matrix, uint8_t how_many_times_to_shuffle,mlfw_mat_double *shuffle_matrix)
{
int random;
index_t a,b;
index_t c,r,idx,end_at_index;
uint8_t j;
double tmp_var;
if(matrix==NULL) return NULL;
if(how_many_times_to_shuffle<=0) return NULL;
if(shuffle_matrix==NULL)
{
shuffle_matrix=mlfw_mat_double_create_new(matrix->rows,matrix->columns);
if(shuffle_matrix==NULL) return NULL;
}
else
{
if(shuffle_matrix->rows!=matrix->rows || shuffle_matrix->columns!=matrix->columns) return NULL;
}
mlfw_mat_double_copy(shuffle_matrix,matrix,0,0,0,0,matrix->rows-1,matrix->columns-1);
b=shuffle_matrix->rows-1;
end_at_index=shuffle_matrix->rows-3;
srand(time(NULL));
for(j=0;j<how_many_times_to_shuffle;j++)
{
for(r=0;r<=end_at_index;r++)
{
a=r+1;
random=rand();
idx=random%(b-a+1)+a;
for(c=0;c<shuffle_matrix->columns;++c)
{
tmp_var=shuffle_matrix->data[r][c];
shuffle_matrix->data[r][c]=shuffle_matrix->data[idx][c];
shuffle_matrix->data[idx][c]=tmp_var;
}
}
}
return shuffle_matrix;
}
mlfw_mat_double * mlfw_mat_double_transpose(mlfw_mat_double *matrix,mlfw_mat_double *transpose_matrix)
{
index_t r,c;
if(matrix==NULL) return NULL;
if(transpose_matrix==NULL)
{
transpose_matrix=mlfw_mat_double_create_new(matrix->columns,matrix->rows);
if(transpose_matrix==NULL) return NULL;
}
else
{
if(transpose_matrix->columns!=matrix->rows || transpose_matrix->rows!=matrix->columns) return NULL;
}
for(r=0;r<matrix->rows;r++)
{
for(c=0;c<matrix->columns;c++)
{
transpose_matrix->data[c][r]=matrix->data[r][c];
}
}
return transpose_matrix;
}

double mlfw_mat_double_get_minimum(mlfw_mat_double *matrix,index_t start_row_index,index_t end_row_index,index_t start_column_index,index_t end_column_index)
{
double minimum;
index_t r,c;
if(matrix==NULL) return 0.0;
if(start_row_index<0) start_row_index=0;
if(end_row_index>=matrix->rows) end_row_index=matrix->rows-1;
if(start_column_index<0) start_column_index=0;
if(end_column_index>=matrix->columns) end_column_index=matrix->columns-1;
if(start_row_index>end_row_index) return 0.0;
if(start_column_index>end_column_index) return 0.0;

minimum=matrix->data[start_row_index][start_column_index];
for(r=start_row_index;r<=end_row_index;r++)
{
for(c=start_column_index;c<=end_column_index;c++)
{
if(matrix->data[r][c]<minimum)
{
minimum=matrix->data[r][c];
}
}
}
return minimum;
}

double mlfw_mat_double_get_maximum(mlfw_mat_double *matrix,index_t start_row_index,index_t end_row_index,index_t start_column_index,index_t end_column_index)
{
double maximum;
index_t r,c;
if(matrix==NULL) return 0.0;
if(start_row_index<0) start_row_index=0;
if(end_row_index>=matrix->rows) end_row_index=matrix->rows-1;
if(start_column_index<0) start_column_index=0;
if(end_column_index>=matrix->columns) end_column_index=matrix->columns-1;
if(start_row_index>end_row_index) return 0.0;
if(start_column_index>end_column_index) return 0.0;

maximum=matrix->data[start_row_index][start_column_index];
for(r=start_row_index;r<=end_row_index;r++)
{
for(c=start_column_index;c<=end_column_index;c++)
{
if(matrix->data[r][c]>maximum)
{
maximum=matrix->data[r][c];
}
}
}
return maximum;
}
