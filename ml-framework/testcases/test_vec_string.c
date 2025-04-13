#include<mlfw_vector.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
mlfw_column_vec_string *vector;
index_t i;
char **data;
data=(char **)malloc(sizeof(char *));
vector=mlfw_column_vec_string_create_new(6);
if(vector==NULL)
{
printf("Low on memory\n");
return 0;
}
mlfw_column_vec_string_set(vector,0,"One");
mlfw_column_vec_string_set(vector,1,"Two");
mlfw_column_vec_string_set(vector,2,"Three");
mlfw_column_vec_string_set(vector,3,"Four");
mlfw_column_vec_string_set(vector,4,"Five");
mlfw_column_vec_string_set(vector,5,"Six");

for(i=0;i<6;i++)
{
mlfw_column_vec_string_get(vector,i,data);
printf("Data: %s\n",*data);
free(*data);
}
mlfw_column_vec_string_to_csv(vector,"vec_string.csv");



return 0;
}
