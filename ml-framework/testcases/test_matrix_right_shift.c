#include<mlfw_matrix.h>
#include<stdio.h>

int main()
{
mlfw_mat_double *matrix;
dimension_t rows,columns;
index_t i,j;

matrix=mlfw_mat_double_create_new(2,3);
if(matrix==NULL)
{
printf("Low on memory\n");
return 0;
}
mlfw_mat_double_set(matrix,0,0,324.23);
mlfw_mat_double_set(matrix,0,1,123.42);
mlfw_mat_double_set(matrix,0,2,23.23);
mlfw_mat_double_set(matrix,1,0,53.53);
mlfw_mat_double_set(matrix,1,1,63.34);
mlfw_mat_double_set(matrix,1,2,124.52);

mlfw_mat_double_get_dimension(matrix,&rows,&columns);

printf("Matrix before Right-Shift: \n");
for(i=0;i<rows;i++)
{
printf("| ");
for(j=0;j<columns;j++)
{
printf("%6.4lf ",mlfw_mat_double_get(matrix,i,j));
}
printf("| \n");
}

mlfw_mat_double_right_shift(matrix,2);

printf("Matrix After Shifting: \n");
for(i=0;i<rows;i++)
{
printf("| ");
for(j=0;j<columns;j++)
{
printf("%6.4lf ",mlfw_mat_double_get(matrix,i,j));
}
printf("| \n");
}


mlfw_mat_double_destroy(matrix);
return 0;
}
