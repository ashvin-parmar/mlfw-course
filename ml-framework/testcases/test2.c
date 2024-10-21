#include<mlfw_matrix.h>
#include<stdio.h>
int main()
{
dimension_t rows,columns;
index_t r,c;
mlfw_mat_double *matrix;
matrix=mlfw_mat_double_from_csv("xyz.d");
if(matrix==NULL) return 0;
mlfw_mat_double_get_dimension(matrix,&rows,&columns);
for(r=0;r<rows;r++)
{
for(c=0;c<columns;c++)
{
printf(" %15.5lf ",mlfw_mat_double_get(matrix,r,c));
}
printf("\n");
}
mlfw_mat_double_destroy(matrix);
return 0;
}
