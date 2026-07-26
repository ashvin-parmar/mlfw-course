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
void mlfw_column_vec_string_set(mlfw_column_vec_string *vector,index_t index,const char *string)
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
void mlfw_column_vec_string_to_csv(mlfw_column_vec_string *vector,char *csv_file_name,mlfw_row_vec_string *header)
{
index_t i;
index_t index;
dimension_t header_size;
char *ptr;
FILE *file;
if(vector==NULL) return ;
if(csv_file_name==NULL || header==NULL) return;
header_size=mlfw_row_vec_string_get_size(header);
if(header_size!=vector->size) return ;
file=fopen(csv_file_name,"w");
if(file==NULL) return;
//code to write header
for(index=0;index<header_size;index++)
{
mlfw_row_vec_string_get(header,index,&ptr);
if(ptr!=NULL)
{
fputs(ptr,file);
free(ptr);	//very very important
}
if(index<header_size-1) fputc(',',file);
else fputc('\n',file);
}
//code to write data
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
mlfw_column_vec_string * mlfw_column_vec_string_from_csv(char *csv_file_name,mlfw_column_vec_string *vector,mlfw_row_vec_string **header)
{
char header_string[1025];
index_t header_index;
index_t index;
dimension_t columns;
FILE *file;
index_t size;
char m;
char string[500];
index_t i;
if(csv_file_name==NULL || header==NULL) return NULL;
file=fopen(csv_file_name,"r");
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
mlfw_row_vec_string_destroy(*header);
*header=NULL;
fclose(file);
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
index=0;
size=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\r') continue;
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
index=0;
i=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\r') continue;
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
void mlfw_row_vec_string_set(mlfw_row_vec_string *vector,index_t index,const char *string)
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
void mlfw_row_vec_string_to_csv(mlfw_row_vec_string *vector,char *csv_file_name,mlfw_row_vec_string *header)
{
index_t i;
index_t index;
dimension_t header_size;
char *ptr;
FILE *file;
if(vector==NULL) return ;
if(csv_file_name==NULL || header==NULL) return;
header_size=mlfw_row_vec_string_get_size(header);
if(header_size!=vector->size) return ;
file=fopen(csv_file_name,"w");
if(file==NULL) return;
//code to write header
for(index=0;index<header_size;index++)
{
mlfw_row_vec_string_get(header,index,&ptr);
if(ptr!=NULL)
{
fputs(ptr,file);
free(ptr);		//very very important
}
if(index<header_size-1) fputc(',',file);
else fputc('\n',file);
}
//code to write data
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
mlfw_row_vec_string * mlfw_row_vec_string_from_csv(char *csv_file_name,mlfw_row_vec_string *vector,mlfw_row_vec_string **header)
{
char header_string[1025];
index_t header_index;
dimension_t columns;
FILE *file;
index_t size;
char m;
char string[500];
index_t i;
int index;
if(csv_file_name==NULL || csv_file_name==NULL) return NULL;
file=fopen(csv_file_name,"r");
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
if(feof(file) || m=='\n') break;
if(m=='\r') continue;
if(m==',') 
{
size++;
}
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
vector=mlfw_row_vec_string_create_new(size);
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
index=0;
i=0;
while(1)
{
m=fgetc(file);
if(feof(file) || m=='\n') break;
if(m=='\r') continue;
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
