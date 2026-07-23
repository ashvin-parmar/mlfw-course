#include<mlfw_matrix.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
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
mlfw_mat_double * mlfw_mat_double_from_csv(const char *csv_file_name,mlfw_mat_double *matrix,mlfw_row_vec_string **header)
{
index_t r,c;
dimension_t rows,columns;
double value;
int index;
char m;
char double_string[1025];
char header_string[1025];
FILE *file;
if(csv_file_name==NULL || header==NULL) return NULL;
file=fopen(csv_file_name,"r");
if(file==NULL)
{
return NULL;
}
//Reading first line starts here
columns=0;
c=0;
while(1)
{
m=fgetc(file);
if(feof(file) || m=='\n') break;
if(m=='\r') continue;
if(m==',') columns++; 
}
columns++;	//1 Columns=0 comma's       4 Columns = 3 Comma's
*header=mlfw_row_vec_string_create_new(columns);
if((*header)==NULL)
{
fclose(file);
return NULL;
}
rewind(file);
index=0;
c=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\r') continue;
if(m==',' || m=='\n')
{
header_string[index]='\0';
mlfw_row_vec_string_set(*header,c,header_string);
if(m=='\n') break;
index=0;
c++;
continue;
}
header_string[index]=m;
index++;
}
//Reading first line ends here
rows=0;
columns=0;
while(1)		//Continue reading from second line
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
matrix=(mlfw_mat_double *)mlfw_mat_double_create_new(rows,columns);
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
if(matrix->columns!=columns || matrix->rows!=rows)
{
fclose(file);
mlfw_row_vec_string_destroy(*header);
*header=NULL;
return NULL;
}
}
rewind(file);
while(fgetc(file)!='\n' && !feof(file));	// Skip first line(One-liner)
//while(1)			//Skip first line
//{
//m=fgetc(file);
//if(feof(file)) break;
//if(m=='\r') continue;
//if(m=='\n') break;
//}
r=0;
c=0;
index=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\r') continue;		//Skip/Ignore: '\r'
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
if(matrix==NULL) return;
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
mlfw_mat_double * mlfw_mat_double_create_copy(mlfw_mat_double *source,index_t from_source_row_index,index_t from_source_column_index,index_t to_source_row_index,index_t to_source_column_index,mlfw_mat_double *new_matrix)
{
	mlfw_mat_double *target_matrix;
	dimension_t source_matrix_rows,source_matrix_columns;
	dimension_t target_matrix_rows,target_matrix_columns;
	index_t source_r,source_c;
	index_t target_r,target_c;
	
	double value;
	if(source==NULL) return NULL;
	mlfw_mat_double_get_dimension(source,&source_matrix_rows,&source_matrix_columns);
	if(from_source_row_index<0 || from_source_row_index>=source_matrix_rows) return NULL;
	if(to_source_row_index<0 || to_source_row_index>=source_matrix_rows) return NULL;
	if(from_source_column_index<0 || from_source_column_index>=source_matrix_rows) return NULL;
	if(to_source_column_index<0 || to_source_column_index>=source_matrix_columns) return NULL;
	if(from_source_row_index>to_source_row_index) return NULL;
	if(from_source_column_index>to_source_column_index) return NULL;
	if(new_matrix==NULL)
	{
		target_matrix_rows=to_source_row_index-from_source_row_index+1;
		target_matrix_columns=to_source_column_index-from_source_column_index+1;
		target_matrix=mlfw_mat_double_create_new(target_matrix_rows,target_matrix_columns);
		if(target_matrix==NULL) return NULL;
	}
	else
	{
		mlfw_mat_double_get_dimension(new_matrix,&target_matrix_rows,&target_matrix_columns);
		if(target_matrix_rows!=(to_source_row_index-from_source_row_index+1) || target_matrix_columns!=(to_source_column_index-from_source_column_index+1)) return NULL;  
		target_matrix=new_matrix;
	}
	target_r=0;
	for(source_r=from_source_row_index;source_r<=to_source_row_index;++source_r)
	{
		target_c=0;
		for(source_c=from_source_column_index;source_c<=to_source_column_index;++source_c)
		{
			value=mlfw_mat_double_get(source,source_r,source_c);
			mlfw_mat_double_set(target_matrix,target_r,target_c,value);
			target_c++;
		}
		target_r++;
	}
	return target_matrix;
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
void mlfw_mat_double_to_csv(mlfw_mat_double *matrix,const char * csv_file_name,mlfw_row_vec_string *header)
{
index_t index;
dimension_t header_size;
char *ptr;
index_t r,c;
char seperator;
FILE *file;
if(matrix==NULL || csv_file_name==NULL || header==NULL) return;
header_size=mlfw_row_vec_string_get_size(header);
if(header_size!=matrix->columns) return ;
file=fopen(csv_file_name,"w");
if(file==NULL) return;
//code to store header
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
//code to store data
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
double mlfw_mat_double_get_mean(mlfw_mat_double *matrix,index_t start_row_index,index_t end_row_index,index_t start_column_index,index_t end_column_index)
{
double mean;
dimension_t elements_count;
double sum;
index_t r,c;
if(matrix==NULL) return 0.0;
if(start_row_index<0) start_row_index=0;
if(end_row_index>=matrix->rows) end_row_index=matrix->rows-1;
if(start_column_index<0) start_column_index=0;
if(end_column_index>=matrix->columns) end_column_index=matrix->columns-1;
if(start_row_index>end_row_index) return 0.0;
if(start_column_index>end_column_index) return 0.0;

sum=0.0;
elements_count=0;
for(r=start_row_index;r<=end_row_index;r++)
{
for(c=start_column_index;c<=end_column_index;c++)
{
sum=sum+matrix->data[r][c];
++elements_count;
}
}
mean=sum/elements_count;
return mean;
}

double mlfw_mat_double_get_standard_deviation(mlfw_mat_double *matrix,index_t start_row_index,index_t end_row_index,index_t start_column_index,index_t end_column_index)
{
double standard_deviation;
double sum;
double square;
double mean;
double diff;
dimension_t elements_count;
index_t r,c;
if(matrix==NULL) return 0.0;
if(start_row_index<0) start_row_index=0;
if(end_row_index>=matrix->rows) end_row_index=matrix->rows-1;
if(start_column_index<0) start_column_index=0;
if(end_column_index>=matrix->columns) end_column_index=matrix->columns-1;
if(start_row_index>end_row_index) return 0.0;
if(start_column_index>end_column_index) return 0.0;
mean=mlfw_mat_double_get_mean(matrix,start_row_index,end_row_index,start_column_index,end_column_index);
elements_count=0;
sum=0.0;
for(r=start_row_index;r<=end_row_index;r++)
{
for(c=start_column_index;c<=end_column_index;c++)
{
diff=matrix->data[r][c]-mean;
square=diff*diff;
sum=sum+square;
++elements_count;
}
}
mean=sum/elements_count;
standard_deviation=sqrt(mean);
return standard_deviation;
}

void mlfw_mat_double_get_training_testing_data(const char *csv_file_name,mlfw_mat_double **training_matrix,mlfw_mat_double **testing_matrix,uint8_t testing_data_percentage)
{
mlfw_mat_double *matrix;
mlfw_mat_double *shuffle_matrix;
mlfw_row_vec_string *header;

mlfw_mat_double *minor_matrix;
mlfw_mat_double *major_matrix;
dimension_t minor_rows,major_rows;
index_t i,j;

if(training_matrix==NULL || testing_matrix==NULL)
{
if(training_matrix!=NULL) *training_matrix=NULL;
if(testing_matrix!=NULL) *testing_matrix=NULL;
return ;
}
*training_matrix=NULL;
*testing_matrix=NULL;
if(csv_file_name==NULL) return ;
if(testing_data_percentage<=0 || testing_data_percentage>=100)
{
return ;
}

matrix=mlfw_mat_double_from_csv(csv_file_name,NULL,&header);
if(matrix==NULL) return ;
shuffle_matrix=mlfw_mat_double_shuffle(matrix,3,NULL);
if(shuffle_matrix==NULL)
{
mlfw_mat_double_destroy(matrix);
mlfw_row_vec_string_destroy(header);
return ;
}
mlfw_mat_double_destroy(matrix);
mlfw_row_vec_string_destroy(header);

minor_rows=(dimension_t)(shuffle_matrix->rows*testing_data_percentage/100);
major_rows=shuffle_matrix->rows-minor_rows;

//transfer allocated array of double to minor or major matrix instead of copied matrix rows
minor_matrix=(mlfw_mat_double *)malloc(sizeof(mlfw_mat_double));
if(minor_matrix==NULL)
{
mlfw_mat_double_destroy(shuffle_matrix);
return ;
}
minor_matrix->data=(double **)malloc(sizeof(double *)*minor_rows);
if(minor_matrix->data==NULL)
{
mlfw_mat_double_destroy(shuffle_matrix);
free(minor_matrix->data);
return ;
}
minor_matrix->rows=minor_rows;
minor_matrix->columns=shuffle_matrix->columns;
for(i=0,j=0;i<minor_rows;i++,j++)
{
minor_matrix->data[i]=shuffle_matrix->data[j];
}

major_matrix=(mlfw_mat_double *)malloc(sizeof(mlfw_mat_double));
if(major_matrix==NULL)
{
mlfw_mat_double_destroy(shuffle_matrix);
free(minor_matrix->data);
free(minor_matrix);
return ;
}
major_matrix->data=(double **)malloc(sizeof(double *)*major_rows);
if(major_matrix->data==NULL)
{
mlfw_mat_double_destroy(shuffle_matrix);
free(minor_matrix->data);
free(minor_matrix);
free(major_matrix);
return ;
}
major_matrix->rows=major_rows;
major_matrix->columns=shuffle_matrix->columns;
for(i=0;i<major_rows;i++,j++)
{
major_matrix->data[i]=shuffle_matrix->data[j];
}
//manually release shuffle matrix data
free(shuffle_matrix->data);
free(shuffle_matrix);
//My Idea
if(minor_rows>major_rows)
{
*training_matrix=minor_matrix;
*testing_matrix=major_matrix;
}
else
{
*training_matrix=major_matrix;
*testing_matrix=minor_matrix;
}
}
void mlfw_mat_double_reshape(mlfw_mat_double **matrix_to_reshape,dimension_t new_rows_count,dimension_t new_columns_count)
{
mlfw_mat_double *matrix;
double **new_data_array;
index_t i,r;
double *new_row;
if(matrix_to_reshape==NULL) return ;
if(new_rows_count<=0 || new_columns_count<=0)
{
mlfw_mat_double_destroy(*matrix_to_reshape);
*matrix_to_reshape=NULL;
return ;
}

matrix=*matrix_to_reshape;
if(matrix->rows==new_rows_count && matrix->columns==new_columns_count) return;
// increase number of rows
if(new_rows_count>matrix->rows)
{
new_data_array=(double **)realloc(matrix->data,sizeof(double *)*new_rows_count);
if(new_data_array==NULL)
{
mlfw_mat_double_destroy(*matrix_to_reshape);
*matrix_to_reshape=NULL;
return ;
}
matrix->data=new_data_array;
for(i=matrix->rows;i<new_rows_count;i++) matrix->data[i]=NULL;
matrix->rows=new_rows_count;
}
else if(new_rows_count<matrix->rows)	//Decrease number of rows
{
for(i=new_rows_count;i<matrix->rows;i++)
{
free(matrix->data[i]);
}
new_data_array=(double **)realloc(matrix->data,sizeof(double *)*(new_rows_count));
if(new_data_array==NULL)
{
for(i=0;i<new_rows_count;i++)
{
free(matrix->data[i]);
}
free(matrix->data);
free(*matrix_to_reshape);
*matrix_to_reshape=NULL;
return ;
}
matrix->data=new_data_array;
matrix->rows=new_rows_count;
}
//Now, reshape columns

//if(new_columns_count==matrix->columns) return ;
if(matrix->columns==new_columns_count)
{
for(i=0;i<new_rows_count;i++)
{
if(matrix->data[i]==NULL)
{
new_row=(double *)malloc(sizeof(double)*new_columns_count);
if(new_row==NULL)
{
for(r=0;r<i;r++)
{
free(matrix->data[r]);
}
free(matrix->data);
free(matrix);
*matrix_to_reshape=NULL;
return;
}
matrix->data[i]=new_row;
}
}
return ;
}
for(i=0;i<matrix->rows;i++)
{
new_row=(double *)realloc(matrix->data[i],sizeof(double)*new_columns_count);
if(new_row==NULL)
{
mlfw_mat_double_destroy(*matrix_to_reshape);
*matrix_to_reshape=NULL;
return ;
}
matrix->data[i]=new_row;
}
matrix->columns=new_columns_count;
}
void mlfw_mat_double_right_shift(mlfw_mat_double *matrix,dimension_t how_many_places_to_shift)
{
index_t r,c,new_c;
if(matrix==NULL) return ;
if(how_many_places_to_shift<=0) return ;
if(how_many_places_to_shift>matrix->columns) how_many_places_to_shift=matrix->columns;
for(r=0;r<matrix->rows;r++)
{
c=matrix->columns-1;
while(1)
{
new_c=c+how_many_places_to_shift;
if(new_c<matrix->columns)
{
matrix->data[r][new_c]=matrix->data[r][c];
}
matrix->data[r][c]=0.0;
if(c==0) break;
c--;
}
}
}
void mlfw_mat_double_left_shift(mlfw_mat_double *matrix,dimension_t how_many_places_to_shift)
{
index_t r,c;
int new_c;
if(matrix==NULL) return ;
if(how_many_places_to_shift<=0) return ;
if(how_many_places_to_shift>matrix->columns) how_many_places_to_shift=matrix->columns;
for(r=0;r<matrix->rows;r++)
{
for(c=0;c<matrix->columns;c++)
{
new_c=c-how_many_places_to_shift;
if(new_c>=0)
{
matrix->data[r][new_c]=matrix->data[r][c];
}
matrix->data[r][c]=0.0;
}
}
}

mlfw_mat_double * mlfw_mat_double_create_identity_matrix(dimension_t rows)
{
index_t r,c;
mlfw_mat_double *matrix;
if(rows<=0) return NULL;
matrix=mlfw_mat_double_create_new(rows,rows);
if(matrix==NULL) return NULL;
for(r=0;r<rows;r++)
{
for(c=0;c<rows;c++)
{
if(r==c)
{
matrix->data[r][c]=1.0;
}
else
{
matrix->data[r][c]=0.0;
}
}
}
return matrix;
}

mlfw_mat_double * mlfw_mat_double_clone(mlfw_mat_double *matrix_to_clone,mlfw_mat_double *new_matrix)
{
mlfw_mat_double *matrix;
if(new_matrix==NULL)
{
matrix=mlfw_mat_double_create_new(matrix_to_clone->rows,matrix_to_clone->columns);
if(matrix==NULL) return NULL;
}
else
{
	if(matrix_to_clone->rows!=new_matrix->rows || matrix_to_clone->columns!=new_matrix->columns) return NULL;
matrix=new_matrix;
}
mlfw_mat_double_copy(matrix,matrix_to_clone,0,0,0,0,matrix_to_clone->rows-1,matrix_to_clone->columns-1);
return matrix;
}
mlfw_mat_double * mlfw_mat_double_inverse(mlfw_mat_double *matrix_to_inverse,mlfw_mat_double *new_matrix)
{
mlfw_mat_double *matrix;
mlfw_mat_double *identity_matrix;
index_t pivot_column_index;
index_t pivot_row_index;
index_t r,c;
index_t i;
index_t row_index_of_largest;
double pivot_value;
double largest;
double value;
int created_memory=0;
if(matrix_to_inverse==NULL) return NULL;
if(matrix_to_inverse->rows!=matrix_to_inverse->columns) return NULL;
matrix=mlfw_mat_double_clone(matrix_to_inverse,NULL);
if(matrix==NULL) return NULL;

if(new_matrix==NULL)
{
identity_matrix=mlfw_mat_double_create_identity_matrix(matrix->rows);
if(identity_matrix==NULL)
{
mlfw_mat_double_destroy(matrix);
return NULL;
}
created_memory=1;
}
else
{
if(new_matrix->rows!=matrix->rows || new_matrix->columns!=matrix->columns)
{
mlfw_mat_double_destroy(matrix);
return NULL;
}
identity_matrix=new_matrix;
// Make the new matrix as identity matrix by filling 1 and 0's using nested loop
for(r=0;r<identity_matrix->rows;++r)
{
for(c=0;c<identity_matrix->columns;++c)
{
identity_matrix->data[r][c]=(r==c?1.0:0.0); 
}
}
created_memory=0;
}
//rest of the processing on the basis of matrix as left part and identity amatrix as right part of the augmented matrix
for(r=0;r<matrix->rows;++r)
{
pivot_column_index=r;
pivot_row_index=r;
pivot_value=matrix->data[pivot_row_index][pivot_column_index];

largest=pivot_value;
if(largest<0) largest=largest*(-1);
row_index_of_largest=r;
// loop to find the index of largest abs below r
// if (r!=index_of_largest) the swap rows of matrix as well as identity matrix make the pivot point values as 1 by dividing all elements of rth row by pivot point value
for(i=r+1;i<matrix->rows;i++)
{
value=matrix->data[i][pivot_column_index];
if(value<0) value=value*(-1);
if(value>largest)
{
largest=value;
row_index_of_largest=i;
}
}
if(largest==0)		//this is no solution or infinite many solution case
{
//	printf("this is no solution or infinite many solution case");
mlfw_mat_double_destroy(matrix);
if(created_memory) mlfw_mat_double_destroy(identity_matrix);
return NULL;
}

if(row_index_of_largest!=pivot_row_index)
{
for(c=0;c<matrix->columns;c++)
{
//swap for matrix
value=matrix->data[row_index_of_largest][c];
matrix->data[row_index_of_largest][c]=matrix->data[pivot_row_index][c];
matrix->data[pivot_row_index][c]=value;
//swap for identity matrix
value=identity_matrix->data[row_index_of_largest][c];
identity_matrix->data[row_index_of_largest][c]=identity_matrix->data[pivot_row_index][c];
identity_matrix->data[pivot_row_index][c]=value;
}
}

//make pivot point value equals to 1 and same operations are performed with identity matrix too.
value=matrix->data[pivot_row_index][pivot_column_index];
if(value!=1.0)
{
for(c=0;c<matrix->columns;++c)
{
matrix->data[r][c]=(matrix->data[r][c]/value);
identity_matrix->data[r][c]=(identity_matrix->data[r][c]/value);
}
}

//make all other points than pivot point equals to 0 (zero) for same pivot_column_index
for(i=0;i<matrix->rows;i++)
{
if(i==r) continue;
value=matrix->data[i][pivot_column_index];
if(value==0.0) continue;
for(c=0;c<matrix->columns;++c)
{
matrix->data[i][c]=matrix->data[i][c]-value*matrix->data[pivot_row_index][c];
identity_matrix->data[i][c]=identity_matrix->data[i][c]-value*identity_matrix->data[pivot_row_index][c];		//matrix->data[i][c]* -> this is constant here
}
}

// loop to eliminate all values above rth row in pivot_column_index column
//Note: That identity matrix should also be updated.

//loop to eliminate all values below rth row in pivot_column_index column
//Note: identity matrix should also be updated.
}

mlfw_mat_double_destroy(matrix);
return identity_matrix;		//identity matrix is now inverse ot matrix_to_inverse
}

