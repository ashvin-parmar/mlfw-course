#include<mlfw_matrix.h>
#include<mlfw_vector.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
mlfw_mat_double *matrix;
mlfw_row_vec_string *header;
index_t index,r,c;
dimension_t size,rows,columns;
char *ptr;
double value;
matrix=mlfw_mat_double_from_csv("IceCreamSales.csv",NULL,&header);
if(matrix==NULL)
{
printf("Unable to create matrix");
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

mlfw_mat_double_get_dimension(matrix,&rows,&columns);
for(r=0;r<rows;++r)
{
for(c=0;c<columns;++c)
{
value=mlfw_mat_double_get(matrix,r,c);
printf("%10.4lf ",value);
}
printf("\n");
}

mlfw_row_vec_string_destroy(header);
mlfw_mat_double_destroy(matrix);
return 0;
}
