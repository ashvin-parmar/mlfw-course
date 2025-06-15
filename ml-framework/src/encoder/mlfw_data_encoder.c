#include<mlfw_matrix.h>
#include<mlfw_vector.h>
#include<mlfw_set.h>
#include<mlfw_encoder.h>
#include<mlfw_utils.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void mlfw_encoder_encode_one_hot(const char *source,const char *target,mlfw_row_vec_string *encode_cols)
{
int *encode_columns;
int size=0;
char *ptr1,*ptr2;
uint8_t found;

FILE *target_file;
mlfw_mat_string *matrix=NULL;
mlfw_set_string **sets;
mlfw_row_vec_string *header;
char *string;
char *set_string;
dimension_t set_size;
index_t i,j,r,c,data_start_row_index;
dimension_t matrix_rows,matrix_columns,header_size;
if(source==NULL || target==NULL || encode_cols==NULL) return ;
matrix=mlfw_mat_string_from_csv(source,matrix,&header);
if(matrix==NULL) return ;
size=mlfw_row_vec_string_get_size(encode_cols);
encode_columns=(int *)malloc(sizeof(int)*size);
if(encode_columns==NULL)
{
mlfw_mat_string_destroy(matrix);
mlfw_row_vec_string_destroy(header);
return;
}
header_size=mlfw_row_vec_string_get_size(header);
for(i=0;i<size;i++)
{
mlfw_row_vec_string_get(encode_cols,i,&ptr1);
if(ptr1==NULL)
{
mlfw_mat_string_destroy(matrix);
mlfw_row_vec_string_destroy(header);
free(encode_columns);
return ;
}
found=0;
for(j=0;j<header_size;j++)
{
mlfw_row_vec_string_get(header,j,&ptr2);
if(ptr2==NULL)
{
mlfw_mat_string_destroy(matrix);
mlfw_row_vec_string_destroy(header);
free(encode_columns);
return;
}
if(strcmp_case_insensitive(ptr1,ptr2)==0)
{
found=1;
}
free(ptr2);
if(found==1) break;
}
free(ptr1);
if(found==0) 
{
mlfw_mat_string_destroy(matrix);
mlfw_row_vec_string_destroy(header);
free(encode_columns);
return;
}
encode_columns[i]=j;
}
mlfw_mat_string_get_dimension(matrix,&matrix_rows,&matrix_columns);
for(i=0;i<size;i++)
{
c=encode_columns[i];
if(c<0 || c>=matrix_columns)
{
mlfw_mat_string_destroy(matrix);
mlfw_row_vec_string_destroy(header);
free(encode_columns);
return;
}
}
sets=(mlfw_set_string **)malloc(sizeof(mlfw_set_string *)*size);
if(sets==NULL)
{
mlfw_mat_string_destroy(matrix);
mlfw_row_vec_string_destroy(header);
free(encode_columns);
return;
}
for(i=0;i<size;i++) 
{
sets[i]=mlfw_set_string_create_new();
if(sets[i]==NULL)
{
for(j=0;j<i;j++) mlfw_set_string_destroy(sets[j]);
free(sets);
mlfw_mat_string_destroy(matrix);
mlfw_row_vec_string_destroy(header);
free(encode_columns);
return;
}
}

data_start_row_index=0;
for(r=data_start_row_index;r<matrix_rows;r++)
{
for(i=0;i<size;i++)
{
c=encode_columns[i];
mlfw_mat_string_get(matrix,r,c,&string);
if(string==NULL)
{
for(j=0;j<size;j++) mlfw_set_string_destroy(sets[j]);
free(sets);
mlfw_mat_string_destroy(matrix);
mlfw_row_vec_string_destroy(header);
free(encode_columns);
return;
}
else
{
if(mlfw_set_string_add(sets[i],string)==-1)
{
free(string);
for(j=0;j<size;j++) mlfw_set_string_destroy(sets[i]);
free(sets);
mlfw_mat_string_destroy(matrix);
mlfw_row_vec_string_destroy(header);
free(encode_columns);
return;
}
free(string);
}
}
}
//Logic to create target file starts here
target_file=fopen(target,"w");
if(target_file==NULL)
{
for(i=0;i<size;i++) mlfw_set_string_destroy(sets[i]);
free(sets);
mlfw_mat_string_destroy(matrix);
mlfw_row_vec_string_destroy(header);
free(encode_columns);
return;
}
for(c=0;c<header_size;c++)
{
mlfw_row_vec_string_get(header,c,&string);
if(string==NULL)
{
for(i=0;i<size;i++) mlfw_set_string_destroy(sets[i]);
free(sets);
mlfw_mat_string_destroy(matrix);
mlfw_row_vec_string_destroy(header);
free(encode_columns);
fclose(target_file);
target_file=fopen(target,"w");
fclose(target_file);
return ;
}
for(i=0;i<size;i++)
{
if(c==encode_columns[i]) break;
}
if(i<size) 	//found, cth columns is to be hot coded
{
//header changed
set_size=mlfw_set_string_get_size(sets[i]);
for(j=0;j<set_size;j++)
{
mlfw_set_string_get(sets[i],j,&set_string);
if(set_string==NULL)
{
free(string);
for(i=0;i<size;i++) mlfw_set_string_destroy(sets[i]);
free(sets);
mlfw_mat_string_destroy(matrix);
mlfw_row_vec_string_destroy(header);
free(encode_columns);
fclose(target_file);
target_file=fopen(target,"w");
fclose(target_file);
return ;
}
fputs(string,target_file);
fputc('_',target_file);
fputs(set_string,target_file);
free(set_string);
if(j<set_size-1) fputc(',',target_file);
}
}
else		//not found, cth columns is not to be hot coded
{
fputs(string,target_file);	//same header written
}
free(string);
if(c==matrix_columns-1) fputc('\n',target_file);
else fputc(',',target_file);
}
//new header create
//encode data

for(r=data_start_row_index;r<matrix_rows;r++)
{
for(c=0;c<matrix_columns;c++)
{
mlfw_mat_string_get(matrix,r,c,&string);
if(string==NULL)
{
for(i=0;i<size;i++) mlfw_set_string_destroy(sets[i]);
free(sets);
mlfw_mat_string_destroy(matrix);
mlfw_row_vec_string_destroy(header);
free(encode_columns);
fclose(target_file);
target_file=fopen(target,"w");
fclose(target_file);
return ;
}
for(i=0;i<size;i++)
{
if(c==encode_columns[i]) break;
}
if(i<size) 	//found, cth columns is to be hot coded
{
//header changed
set_size=mlfw_set_string_get_size(sets[i]);
for(j=0;j<set_size;j++)
{
mlfw_set_string_get(sets[i],j,&set_string);
if(set_string==NULL)
{
free(string);
for(i=0;i<size;i++) mlfw_set_string_destroy(sets[i]);
free(sets);
mlfw_mat_string_destroy(matrix);
mlfw_row_vec_string_destroy(header);
free(encode_columns);
fclose(target_file);
target_file=fopen(target,"w");
fclose(target_file);
return ;
}
if(strcmp(string,set_string)==0)
{
fputc('1',target_file);
}
else
{
fputc('0',target_file);
}
free(set_string);
if(j<set_size-1) fputc(',',target_file);
}
}
else		//not found, cth columns is not to be hot coded
{
fputs(string,target_file);	//same header written
}
free(string);
if(c==matrix_columns-1) fputc('\n',target_file);
else fputc(',',target_file);
}
}

fclose(target_file);
for(i=0;i<size;i++) mlfw_set_string_destroy(sets[i]);
free(sets);
mlfw_mat_string_destroy(matrix);
mlfw_row_vec_string_destroy(header);
free(encode_columns);
}
