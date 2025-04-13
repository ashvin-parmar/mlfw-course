#include<mlfw_vector.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
mlfw_row_vec_string *vector;
index_t i;
char **data;
data=(char **)malloc(sizeof(char *));
vector=mlfw_row_vec_string_create_new(6);
if(vector==NULL)
{
printf("Low on memory\n");
return 0;
}
mlfw_row_vec_string_set(vector,0,"One");
mlfw_row_vec_string_set(vector,1,"Two");
mlfw_row_vec_string_set(vector,2,"Three");
mlfw_row_vec_string_set(vector,3,"Four");
mlfw_row_vec_string_set(vector,4,"Five");
mlfw_row_vec_string_set(vector,5,"Six");

for(i=0;i<6;i++)
{
mlfw_row_vec_string_get(vector,i,data);
printf("Data: %s\n",*data);
free(*data);
}
mlfw_row_vec_string_to_csv(vector,"row_vec_string.csv");

free(data);
mlfw_row_vec_string_destroy(vector);
return 0;
}
