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
mlfw_column_vec_double *mlfw_column_vec_double_create_new_filled(dimension_t size,double value,mlfw_column_vec_double *vector)
{
index_t i;
if(size<=0) return NULL;
if(vector==NULL)
{
vector=mlfw_column_vec_double_create_new(size);
if(vector==NULL) return NULL;
}
else
{
if(vector->size!=size) return NULL;
}
for(i=0;i<size;i++) vector->data[i]=value;
return vector;
}
mlfw_row_vec_double * mlfw_column_vec_double_transpose(mlfw_column_vec_double *column_vector,mlfw_row_vec_double *row_vector)
{
index_t i;
dimension_t size;
if(column_vector==NULL) return NULL;
size=mlfw_column_vec_double_get_size(column_vector);
if(size<=0) return NULL;
if(row_vector==NULL)
{
row_vector=mlfw_row_vec_double_create_new(size);
if(row_vector==NULL) return NULL;
}
else
{
if(row_vector->size!=size) return NULL;
}
for(i=0;i<size;i++) mlfw_row_vec_double_set(row_vector,i,mlfw_column_vec_double_get(column_vector,i));
return row_vector;
}
dimension_t mlfw_column_vec_double_get_size(mlfw_column_vec_double *vector)
{
if(vector==NULL) return 0;
return vector->size;
}
double mlfw_column_vec_double_get_mean(mlfw_column_vec_double *vector)
{
double mean,sum;
index_t i;
for(i=0,sum=0.0;i<vector->size;i++)
{
sum+=(vector->data[i]);
}
mean=sum/vector->size;
return mean;
}
void mlfw_column_vec_double_to_csv(mlfw_column_vec_double *vector,char *csv_filename,mlfw_row_vec_string *header)
{
dimension_t header_size;
index_t index;
char *ptr;
index_t r;
FILE *file;
if(vector==NULL || csv_filename==NULL || header==NULL) return ;
header_size=mlfw_row_vec_string_get_size(header);
if(header_size!=vector->size) return ;
file=fopen(csv_filename,"w");
if(file==NULL) return ;
//code to write header
for(index=0;index<header_size;index++)
{
mlfw_row_vec_string_get(header,index,&ptr);
if(ptr!=NULL)
{
fputs(ptr,file);
free(ptr);	//very very very important
}
if(index<header_size-1) fputc(',',file);
else fputc('\n',file);
}
//code to write data
for(r=0;r<vector->size;r++)
{
fprintf(file,"%lf",vector->data[r]);
if(r==vector->size-1) fputc('\n',file);
else fputc(',',file);
}
fclose(file);
}
mlfw_column_vec_double * mlfw_column_vec_double_from_csv(char *csv_filename,mlfw_column_vec_double *vector,mlfw_row_vec_string **header)
{
char header_string[1025];
index_t header_index;
index_t index;
dimension_t columns;
dimension_t size;
FILE *file;
char m;
char double_string[1025];
double value;
index_t i;
index_t j;
if(csv_filename==NULL || header==NULL) return NULL;
file=fopen(csv_filename,"r");
if(file==NULL) return NULL;
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
if(columns!=1)
{
fclose(file);
*header=NULL;
return NULL;
}
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
size=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\r') continue;
if(m==',') size++;
}
size++;
if(vector==NULL)
{
vector=mlfw_column_vec_double_create_new(size);
if(vector==NULL) 
{
fclose(file);
mlfw_row_vec_string_destroy(*header);
*header=NULL;
return NULL;
}
}
else
{
if(vector->size!=size)
{
fclose(file);
mlfw_row_vec_string_destroy(*header);
*header=NULL;
return NULL;
}
}
rewind(file);
while(1)		//Skip first line
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\r') continue;
if(m=='\n') break;
}
i=0;
j=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\r') continue;
if(m==',' || m=='\n') 
{
double_string[i]='\0';
value=strtod(double_string,NULL);
mlfw_column_vec_double_set(vector,j,value);
j++;
i=0;
}
else
{
double_string[i]=m;
i++;
}
}
fclose(file);
return vector;
}
void mlfw_column_vec_double_copy(mlfw_column_vec_double *target,mlfw_column_vec_double *source,index_t target_start_index,index_t source_start_index,index_t source_end_index)
{
dimension_t source_size;
dimension_t target_size;
index_t source_i,target_i;
double value;
if(source==NULL || target==NULL) return ;
source_size=mlfw_column_vec_double_get_size(source);
target_size=mlfw_column_vec_double_get_size(target);

if(source_start_index<0 || source_start_index>=source_size) return ;
if(source_end_index<0 || source_end_index>=source_size) return ;
if(source_start_index>source_end_index) return ;

if(target_start_index<0 || target_start_index>=target_size) return ;
if(target_start_index+(source_end_index-source_start_index)>=target_size) return ;

target_i=target_start_index;
for(source_i=source_start_index;source_i<=source_end_index;source_i++)
{
	value=mlfw_column_vec_double_get(source,source_i);
	mlfw_column_vec_double_set(target,target_i,value);
	target_i++;
}
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
mlfw_row_vec_double *mlfw_row_vec_double_create_new_filled(dimension_t size,double value,mlfw_row_vec_double *vector)
{
index_t i;
if(size<=0) return NULL;
if(vector==NULL)
{
vector=mlfw_row_vec_double_create_new(size);
if(vector==NULL) return NULL;
}
else
{
if(vector->size!=size) return NULL;
}
for(i=0;i<vector->size;i++) vector->data[i]=value;
return vector;
}
mlfw_column_vec_double * mlfw_row_vec_double_transpose(mlfw_row_vec_double *row_vector,mlfw_column_vec_double *column_vector)
{
index_t i;
if(row_vector==NULL) return NULL;
if(column_vector==NULL)
{
column_vector=mlfw_column_vec_double_create_new(row_vector->size);
if(column_vector==NULL) return NULL;
}
else
{
if(column_vector->size!=row_vector->size) return NULL;
}
for(i=0;i<column_vector->size;i++) column_vector->data[i]=row_vector->data[i]; 
return column_vector;
}
dimension_t mlfw_row_vec_double_get_size(mlfw_row_vec_double *vector)
{
if(vector==NULL) return 0;
return vector->size;
}
double mlfw_row_vec_double_get_mean(mlfw_row_vec_double *vector)
{
index_t i;
double mean,sum;
for(i=0,sum=0.0;i<vector->size;i++,sum+=(vector->data[i]));
return mean=sum/vector->size; 
}
void mlfw_row_vec_double_to_csv(mlfw_row_vec_double *vector,char *csv_filename,mlfw_row_vec_string *header)
{
index_t index;
dimension_t header_size;
char *ptr;
index_t r;
FILE *file;
if(vector==NULL || csv_filename==NULL || header==NULL) return ;
header_size=mlfw_row_vec_string_get_size(header);
if(header_size!=vector->size) return;
file=fopen(csv_filename,"w");
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
for(r=0;r<vector->size;r++)
{
fprintf(file,"%lf",vector->data[r]);
if(r==vector->size-1) fputc('\n',file);
else fputc(',',file);
}
fclose(file);
}
mlfw_row_vec_double * mlfw_row_vec_double_from_csv(char *csv_filename,mlfw_row_vec_double *vector,mlfw_row_vec_string **header)
{
char header_string[1025];
index_t header_index;
index_t index;
dimension_t columns;
dimension_t size;
FILE *file;
char m;
char double_string[1025];
double value;
index_t i;
index_t j;
if(csv_filename==NULL || header==NULL) return NULL;
file=fopen(csv_filename,"r");
if(file==NULL) return NULL;
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
size=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\r') continue;
if(m==',') size++;
}
size++;
if(size!=mlfw_row_vec_string_get_size(*header))
{
mlfw_row_vec_string_destroy(*header);
*header=NULL;
fclose(file);
return NULL;
}
if(vector==NULL)
{
vector=mlfw_row_vec_double_create_new(size);
if(vector==NULL) 
{
fclose(file);
mlfw_row_vec_string_destroy(*header);
*header=NULL;
return NULL;
}
}
else
{
if(vector->size!=size) 
{
fclose(file);
mlfw_row_vec_string_destroy(*header);
*header=NULL;
return NULL;
}
}
rewind(file);
while(1)		//Skip first line
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\r') continue;
if(m=='\n') break;
}
i=0;
j=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\r') continue;
if(m==',' || m=='\n') 
{
double_string[i]='\0';
value=strtod(double_string,NULL);
mlfw_row_vec_double_set(vector,j,value);
j++;
i=0;
}
else
{
double_string[i]=m;
i++;
}
}
fclose(file);
return vector;
}
void mlfw_row_vec_double_copy(mlfw_row_vec_double *target,mlfw_row_vec_double *source,index_t target_start_index,index_t source_start_index,index_t source_end_index)
{
dimension_t source_size;
dimension_t target_size;
index_t source_i,target_i;
double value;
if(source==NULL || target==NULL) return ;
source_size=mlfw_row_vec_double_get_size(source);
target_size=mlfw_row_vec_double_get_size(target);

if(source_start_index<0 || source_start_index>=source_size) return ;
if(source_end_index<0 || source_end_index>=source_size) return ;
if(source_start_index>source_end_index) return ;

if(target_start_index<0 || target_start_index>=target_size) return ;
if(target_start_index+(source_end_index-source_start_index)>=target_size) return ;

target_i=target_start_index;
for(source_i=source_start_index;source_i<=source_end_index;source_i++)
{
	value=mlfw_row_vec_double_get(source,source_i);
	mlfw_row_vec_double_set(target,target_i,value);
	target_i++;
}
}
