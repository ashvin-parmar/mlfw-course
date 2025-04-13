#include<mlfw_vector.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
mlfw_column_vec_string *vector;
index_t i;
char **data;
data=(char **)malloc(sizeof(char *));
vector=mlfw_column_vec_string_from_csv("vec_string.csv");
if(vector==NULL) 
{
printf("Low on memory\n");
return 0;
}
for(i=0;i<mlfw_column_vec_string_get_size(vector);i++)
{
mlfw_column_vec_string_get(vector,i,data);
printf("Data: %s\n",*data);
free(*data);
}
free(data);
mlfw_column_vec_string_destroy(vector);
return 0;
}
