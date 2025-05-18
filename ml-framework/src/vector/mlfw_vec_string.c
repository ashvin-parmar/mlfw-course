#include<mlfw_vector.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct __mlfw_column_vec_string
{
char **data;
dimension_t size;
}mlfw_column_vec_string;
typedef struct __mlfw_row_vec_string
{
char **data;
dimension_t size;
}mlfw_row_vec_string;

//For Column Vector
mlfw_column_vec_string *mlfw_column_vec_string_create_new(dimension_t rows)
{
mlfw_column_vec_string *vector;
index_t i;
if(rows<=0) return NULL;
vector=(mlfw_column_vec_string *)malloc(sizeof(mlfw_column_vec_string));
if(vector==NULL) return NULL;
vector->data=(char **)malloc(sizeof(char *)*rows);
if(vector->data==NULL)
{
mlfw_column_vec_string_destroy(vector);
return NULL;
}
for(i=0;i<rows;i++) vector->data[i]=NULL;
vector->size=rows;
return vector;
}
void mlfw_column_vec_string_destroy(mlfw_column_vec_string *vector)
{
index_t i;
if(vector==NULL) return;
if(vector->data!=NULL)
{
for(i=0;i<vector->size;i++)
{
if(vector->data[i]) free(vector->data[i]);
}
free(vector->data);
}
free(vector);
}
void mlfw_column_vec_string_get(mlfw_column_vec_string *vector,index_t index,char **string)
{
if(string==NULL) return;
*string=NULL;
if(vector==NULL) return ;
if(index<0 || index>=vector->size) return;
if(vector->data[index]==NULL) return;
*string=(char *)malloc(sizeof(char)*(strlen(vector->data[index])+1));
if(*string==NULL) return;
//memcpy(string,(const void *)vector->data+(i*sizeof(char)),strlen(vector->data[index]));
strcpy(*string,vector->data[index]);
}
void mlfw_column_vec_string_set(mlfw_column_vec_string *vector,index_t index,char *string)
{
if(vector==NULL) return ;
if(string==NULL) return ;
if(index<0 || index>=vector->size) return;
if(vector->data[index]!=NULL)
{
free(vector->data[index]);
}
vector->data[index]=(char *)malloc(sizeof(char)*(strlen(string)+1));
if(vector->data[index]==NULL) return;
strcpy(vector->data[index],string);
}
mlfw_row_vec_string * mlfw_column_vec_string_transpose(mlfw_column_vec_string *column_vector,mlfw_row_vec_string *row_vector)
{
index_t i;
if(column_vector==NULL) return NULL;
if(row_vector==NULL)
{
row_vector=mlfw_row_vec_string_create_new(column_vector->size);
if(row_vector==NULL) return NULL;
}
else
{
if(row_vector->size!=column_vector->size) return NULL;
}
for(i=0;i<column_vector->size;i++)
{
if(column_vector->data[i])
{
row_vector->data[i]=(char *)malloc(sizeof(char)*(strlen(column_vector->data[i])+1));
if(row_vector->data[i]) 
{
strcpy(row_vector->data[i],column_vector->data[i]);
}
}
}
return row_vector;
}
dimension_t mlfw_column_vec_string_get_size(mlfw_column_vec_string *vector)
{
if(vector==NULL) return 0;
return vector->size;
}
void mlfw_column_vec_string_to_csv(mlfw_column_vec_string *vector,char *csv_file_name)
{
index_t i;
FILE *file;
if(vector==NULL) return ;
if(csv_file_name==NULL) return;
file=fopen(csv_file_name,"w");
if(file==NULL) return;
for(i=0;i<vector->size;i++)
{
if(vector->data[i])
{
fputs(vector->data[i],file);
}
fputc('\n',file);
}
fclose(file);
}
mlfw_column_vec_string * mlfw_column_vec_string_from_csv(char *csv_file_name,mlfw_column_vec_string *vector)
{
FILE *file;
index_t size;
char m;
char string[500];
index_t i;
int index;
if(csv_file_name==NULL) return NULL;
file=fopen(csv_file_name,"r");
if(file==NULL) return NULL;
index=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\n') 
{
index=0;
size++;
}
else
{
index++;
}
}
if(index) size++;
if(vector==NULL)
{
vector=mlfw_column_vec_string_create_new(size);
if(vector==NULL) 
{
fclose(file);
return NULL;
}
}
else
{
if(vector->size!=size)
{
fclose(file);
return NULL;
}
}
index=0;
i=0;
rewind(file);
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\n') 
{
string[index]='\0';
vector->data[i]=(char *)malloc(sizeof(char)*(strlen(string)+1));
if(vector->data[i]) strcpy(vector->data[i],string);
index=0;
i++;
}
else
{
string[index]=m;
index++;
}
}
if(index)
{
string[index]='\0';
vector->data[i]=(char *)malloc(sizeof(char)*(strlen(string)+1));
strcpy(vector->data[i],string);
}
fclose(file);
return vector;
}

//For Row Vector
mlfw_row_vec_string * mlfw_row_vec_string_create_new(dimension_t columns)
{
mlfw_row_vec_string *vector;
index_t i;
if(columns<=0) return NULL;
vector=(mlfw_row_vec_string *)malloc(sizeof(mlfw_row_vec_string));
if(vector==NULL) return NULL;
vector->data=(char **)malloc(sizeof(char *)*columns);
if(vector->data==NULL)
{
free(vector);
return NULL;
}
for(i=0;i<columns;i++) vector->data[i]=NULL;
vector->size=columns;
return vector;
}
void mlfw_row_vec_string_destroy(mlfw_row_vec_string *vector)
{
index_t i;
if(vector==NULL) return;
if(vector->data!=NULL)
{
for(i=0;i<vector->size;i++)
{
if(vector->data[i]) free(vector->data[i]);
}
free(vector->data);
}
free(vector);
}
void mlfw_row_vec_string_get(mlfw_row_vec_string *vector,index_t index,char **string)
{
if(string==NULL) return;
*string=NULL;
if(vector==NULL) return ;
if(index<0 || index>=vector->size) return;
if(vector->data[index]==NULL) return;
*string=(char *)malloc(sizeof(char)*(strlen(vector->data[index])+1));
if(*string==NULL) return;
//memcpy(string,(const void *)vector->data+(i*sizeof(char)),strlen(vector->data[index]));
strcpy(*string,vector->data[index]);
}
void mlfw_row_vec_string_set(mlfw_row_vec_string *vector,index_t index,char *string)
{
if(vector==NULL) return ;
if(string==NULL) return ;
if(index<0 || index>=vector->size) return;
if(vector->data[index]!=NULL)
{
free(vector->data[index]);
}
vector->data[index]=(char *)malloc(sizeof(char)*(strlen(string)+1));
if(vector->data[index]==NULL) return;
strcpy(vector->data[index],string);
}
mlfw_column_vec_string * mlfw_row_vec_string_transpose(mlfw_row_vec_string *row_vector,mlfw_column_vec_string *column_vector)
{
index_t i;
char *ptr;
if(row_vector==NULL) return NULL;
if(column_vector==NULL)
{
column_vector=mlfw_column_vec_string_create_new(row_vector->size);
if(column_vector==NULL) return NULL;
}
else
{
if(column_vector->size!=row_vector->size) return NULL;
}
for(i=0;i<row_vector->size;i++)
{
mlfw_row_vec_string_get(row_vector,i,&ptr);
mlfw_column_vec_string_set(column_vector,i,ptr);
free(ptr);
}
return column_vector;
}
dimension_t mlfw_row_vec_string_get_size(mlfw_row_vec_string *vector)
{
if(vector==NULL) return 0;
return vector->size;
}
void mlfw_row_vec_string_to_csv(mlfw_row_vec_string *vector,char *csv_file_name)
{
index_t i;
FILE *file;
if(vector==NULL) return ;
if(csv_file_name==NULL) return;
file=fopen(csv_file_name,"w");
if(file==NULL) return;
for(i=0;i<vector->size;i++)
{
if(vector->data[i])
{
fputs(vector->data[i],file);
}
if(i<vector->size-1) fputc(',',file);
else fputc('\n',file);
}
fclose(file);
}
mlfw_row_vec_string * mlfw_row_vec_string_from_csv(char *csv_file_name,mlfw_row_vec_string *vector)
{
FILE *file;
index_t size;
char m;
char string[500];
index_t i;
int index;
if(csv_file_name==NULL) return NULL;
file=fopen(csv_file_name,"r");
if(file==NULL) return NULL;
while(1)
{
m=fgetc(file);
if(feof(file) || m=='\n') break;
if(m==',') 
{
size++;
}
}
size++;
if(vector==NULL)
{
vector=mlfw_row_vec_string_create_new(size);
if(vector==NULL) 
{
fclose(file);
return NULL;
}
}
else
{
if(vector->size!=size) 
{
fclose(file);
return NULL;
}
}
index=0;
i=0;
rewind(file);
while(1)
{
m=fgetc(file);
if(feof(file) || m=='\n') break;
if(m==',') 
{
string[index]='\0';
vector->data[i]=(char *)malloc(sizeof(char)*(strlen(string)+1));
if(vector->data[i]) strcpy(vector->data[i],string);
index=0;
i++;
}
else
{
string[index]=m;
index++;
}
}
if(index)
{
string[index]='\0';
vector->data[i]=(char *)malloc(sizeof(char)*(strlen(string)+1));
strcpy(vector->data[i],string);
}
fclose(file);
return vector;
}
