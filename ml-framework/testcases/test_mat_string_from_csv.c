#include<mlfw_matrix.h>
#include<mlfw_vector.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
mlfw_mat_string *matrix;
mlfw_row_vec_string *header;
index_t index,r,c;
dimension_t size,rows,columns;
char *ptr;
char *value;

matrix=mlfw_mat_string_from_csv("IceCreamSales.csv",NULL,NULL);
if(matrix==NULL)
{
printf("Unable to create matrix\n");
return 0;
}
size=mlfw_row_vec_string_get_size(header);
printf("%d\n",size);
for(index=0;index<size;index++)
{
mlfw_row_vec_string_get(header,index,&ptr);
if(ptr!=NULL)
{
printf("%s ",ptr);
free(ptr);
}
}
printf("\n");

mlfw_mat_string_get_dimension(matrix,&rows,&columns);
for(r=0;r<rows;++r)
{
for(c=0;c<columns;++c)
{
mlfw_mat_string_get(matrix,r,c,&value);
printf("%s ",value);
}
printf("\n");
}

mlfw_row_vec_string_destroy(header);
mlfw_mat_string_destroy(matrix);
return 0;
}
