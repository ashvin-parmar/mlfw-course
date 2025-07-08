#include<mlfw_matrix.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
typedef struct __mlfw_mat_string
{
char ***data;
dimension_t rows;
dimension_t columns; 
}mlfw_mat_string;
mlfw_mat_string * mlfw_mat_string_create_new(dimension_t rows,dimension_t columns)
{
mlfw_mat_string *matrix;
index_t r,c;
if(rows<=0 || columns<=0) return NULL;
matrix=(mlfw_mat_string *)malloc(sizeof(mlfw_mat_string));
if(matrix==NULL) return NULL;
matrix->data=(char ***)malloc(sizeof(char **)*rows);
if(matrix->data==NULL)
{
free(matrix);
return NULL;
}
for(r=0;r<rows;r++)
{
matrix->data[r]=(char **)malloc(sizeof(char *)*columns);
if(matrix->data[r]==NULL)
{
for(c=0;c<r;c++) free(matrix->data[c]);
free(matrix->data);
free(matrix);
return NULL;
}
else
{
for(c=0;c<columns;c++) matrix->data[r][c]=NULL;	//very very important
}
}
matrix->rows=rows;
matrix->columns=columns;
return matrix;
}
void mlfw_mat_string_destroy(mlfw_mat_string *matrix)
{
index_t r,c;
if(matrix==NULL) return;
for(r=0;r<matrix->rows;r++) 
{
for(c=0;c<matrix->columns;c++)
{
if(matrix->data[r][c]!=NULL) free(matrix->data[r][c]);
}
free(matrix->data[r]);
}
free(matrix->data);
free(matrix);
matrix=NULL;
}
mlfw_mat_string * mlfw_mat_string_from_csv(const char *csv_file_name,mlfw_mat_string *matrix,mlfw_row_vec_string **header)
{
char header_string[1025];
index_t header_index;
index_t r,c;
dimension_t rows,columns;
char string[5001]; 
int index;
char m;
FILE *file;
if(csv_file_name==NULL || header==NULL) return NULL;
file=fopen(csv_file_name,"r");
if(file==NULL)
{
return NULL;
}
//Read first line start here
columns=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\r') continue;
if(m==',') columns++;
if(m=='\n') break;
}
columns++;	//0 comma's -> 1 Columns, 4 Comma's Means 5 Columns
*header=mlfw_row_vec_string_create_new(columns);
if(*header==NULL)
{
fclose(file);
return NULL;
}
rewind(file);
index=0;
header_index=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\r') continue;
if(m==',')
{
header_string[index]='\0';
mlfw_row_vec_string_set(*header,header_index,header_string);
header_index++;
index=0;
continue;
}
if(m=='\n')
{
header_string[index]='\0';
mlfw_row_vec_string_set(*header,header_index,header_string);
break;
}
header_string[index]=m;
index++;
}
//Read first line ends here
rows=0;
columns=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\r') continue;
if(rows==0 && m==',') columns++;
if(m=='\n') rows++;
}
columns++;
if(columns!=mlfw_row_vec_string_get_size(*header))
{
mlfw_row_vec_string_destroy(*header);
*header=NULL;
fclose(file);
return NULL;
}
if(matrix==NULL)
{
matrix=(mlfw_mat_string *)mlfw_mat_string_create_new(rows,columns);
if(matrix==NULL)
{
fclose(file);
mlfw_row_vec_string_destroy(*header);
*header=NULL;
return NULL;
}
}
else
{
if(matrix->rows!=rows || matrix->columns!=columns)
{
fclose(file);
mlfw_row_vec_string_destroy(*header);		//Destroy header before returning NULL
*header=NULL;
return NULL;
}
}
rewind(file);
r=0;
c=0;
index=0;
while(1)		//Skip first line
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\r') continue;
if(m=='\n') break;
}
//while(fgetc(file)!='\n' && !feof(file));
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\r') continue;
if(m==',' || m=='\n')
{
string[index]='\0';
matrix->data[r][c]=(char *)malloc(sizeof(char)*strlen(string)+1);
if(matrix->data[r][c]!=NULL)
{
strcpy(matrix->data[r][c],string);
}
index=0;
c++;
if(matrix->columns==c)
{
c=0;
r++;
}
}
else
{
string[index]=m;
index++;
}
}
fclose(file);
return matrix;
}
void mlfw_mat_string_to_csv(mlfw_mat_string *matrix,const char *csv_file_name,mlfw_row_vec_string *header)
{
index_t index;
dimension_t header_size;
char *ptr;
FILE *file;
index_t r,c;
if(matrix==NULL) return ;
if(csv_file_name==NULL || header==NULL) return;
header_size=mlfw_row_vec_string_get_size(header);
if(header_size!=matrix->columns) return;
file=fopen(csv_file_name,"w");
if(file==NULL) return ;
//code to write header
for(index=0;index<header_size;index++)
{
mlfw_row_vec_string_get(header,index,&ptr);
if(ptr!=NULL)
{
fputs(ptr,file);
free(ptr);
}
if(index<header_size-1) fputc(',',file);
else fputc('\n',file);
}
//code to write data
for(r=0;r<matrix->rows;r++)
{
for(c=0;c<matrix->columns;c++)
{
if(matrix->data[r][c]) fputs(matrix->data[r][c],file);
if(c<matrix->columns-1) fputc(',',file);
else fputc('\n',file);
}
}
fclose(file);
}
void mlfw_mat_string_get(mlfw_mat_string *matrix,index_t row,index_t column,char **string)
{
if(string==NULL) return ;
if(matrix==NULL) 
{
*string=NULL;
return ;
}
if(row<0 || row>=matrix->rows || column<0 || column>=matrix->columns)
{
*string=NULL;
return ;
}
if(matrix->data[row][column]==NULL) 
{
*string=NULL;
return;
}
*string=(char *)malloc(sizeof(char)*strlen(matrix->data[row][column])+1);
if(*string==NULL) return;
strcpy(*string,matrix->data[row][column]);
}
void mlfw_mat_string_set(mlfw_mat_string *matrix,index_t row,index_t column,char *string)
{
if(matrix==NULL || string==NULL) return ;
if(row<0 || row>=matrix->rows || column<0 || column>=matrix->columns) return;
if(matrix->data[row][column]!=NULL) free(matrix->data[row][column]);
matrix->data[row][column]=(char *)malloc(sizeof(char)*(strlen(string)+1));
if(matrix->data[row][column]!=NULL)
{
strcpy(matrix->data[row][column],string);
}
}
void mlfw_mat_string_get_dimension(mlfw_mat_string *matrix,dimension_t *rows,dimension_t *columns)
{
if(matrix==NULL);
if(rows!=NULL) *rows=matrix->rows;
if(columns!=NULL) *columns=matrix->columns; 
}

void mlfw_mat_string_copy(mlfw_mat_string *target,mlfw_mat_string *source,index_t from_target_row_index,index_t from_target_column_index,index_t from_source_row_index,index_t from_source_column_index,index_t to_source_row_index,index_t to_source_column_index)
{
char *ptr;
dimension_t target_rows;
dimension_t target_columns;
dimension_t source_rows;
dimension_t source_columns;
index_t target_r,target_c;
index_t source_r,source_c;
if(target==NULL || source==NULL) return;
mlfw_mat_string_get_dimension(target,&target_rows,&target_columns);
mlfw_mat_string_get_dimension(source,&source_rows,&source_columns);

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
if(target->data[target_r][target_c]!=NULL)
{
free(target->data[target_r][target_c]);
target->data[target_r][target_c]=NULL;
}
mlfw_mat_string_get(source,target_r,target_c,&ptr);
if(ptr!=NULL)	mlfw_mat_string_set(target,target_r,target_c,ptr);
}
}
}
}
/*
mlfw_column_vec_string * mlfw_mat_string_create_column_vec(mlfw_mat_string *matrix,index_t column_index,mlfw_column_vec_string *vector)
{
char *ptr;
dimension_t matrix_columns;
dimension_t matrix_rows;
index_t r,c;
if(matrix==NULL) return NULL;
mlfw_mat_string_get_dimension(matrix,&matrix_rows,&matrix_columns);
if(column_index>=matrix_columns || column_index<0) return NULL;

if(vector==NULL)
{
vector=mlfw_column_vec_string_create_new(matrix_rows);
if(vector==NULL) return NULL;
}
else
{
if(mlfw_column_vec_string_get_size()!=matrix_rows) return NULL;
}
c=column_index;
for(r=0;r<matrix_rows;r++)
{
if(matrix[r][c]!=NULL)
{
mlfw_mat_string_get(matrix,r,c,&ptr);
mlfw_column_vec_string_set(vector,r,ptr);
free(ptr);
}
}
return vector;
}
void mlfw_mat_string_fill(mlfw_mat_string *matrix,index_t from_row_index,index_t from_column_index,index_t to_row_index,index_t to_column_index,string value)
{
dimension_t matrix_rows;
dimension_t matrix_columns;
index_t r,c;
if(matrix==NULL) return;
mlfw_mat_string_get_dimension(matrix,&matrix_rows,&matrix_columns);
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
mlfw_mat_string_set(matrix,r,c,value);
}
}
}
void mlfw_mat_string_to_csv(mlfw_mat_string *matrix,const char * csv_file_name)
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
*/
mlfw_mat_string * mlfw_mat_string_shuffle(mlfw_mat_string *matrix, uint8_t how_many_times_to_shuffle,mlfw_mat_string *shuffle_matrix)
{
int random;
index_t a,b;
index_t c,r,idx,end_at_index;
uint8_t j;
char *tmp_var;
if(matrix==NULL) return NULL;
if(how_many_times_to_shuffle<=0) return NULL;
if(shuffle_matrix==NULL)
{
shuffle_matrix=mlfw_mat_string_create_new(matrix->rows,matrix->columns);
if(shuffle_matrix==NULL) return NULL;
}
else
{
if(shuffle_matrix->rows!=matrix->rows || shuffle_matrix->columns!=matrix->columns)
{
return NULL;
}
}
mlfw_mat_string_copy(shuffle_matrix,matrix,0,0,0,0,matrix->rows-1,matrix->columns-1);
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

mlfw_mat_string * mlfw_mat_string_transpose(mlfw_mat_string *matrix,mlfw_mat_string *transposed_matrix)
{
char *ptr;
index_t r,c;
if(matrix==NULL) return NULL;
if(transposed_matrix==NULL)
{
transposed_matrix=mlfw_mat_string_create_new(matrix->columns,matrix->rows);
if(transposed_matrix==NULL) return NULL;
}
else
{
if(transposed_matrix->rows!=matrix->columns || transposed_matrix->columns!=matrix->rows) return NULL;
}
for(r=0;r<=matrix->rows;r++)
{
for(c=0;c<=matrix->columns;c++)
{
mlfw_mat_string_get(matrix,r,c,&ptr);
mlfw_mat_string_set(transposed_matrix,c,r,ptr);
free(ptr);
}
}
return transposed_matrix;
}
