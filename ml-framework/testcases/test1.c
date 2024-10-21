#include<mlfw_matrix.h>
#include<stdio.h>
int main()
{
index_t r,c;
double  value=0.0;
mlfw_mat_double *matrix;
matrix=mlfw_mat_double_create_new(5,5);
if(matrix==NULL) return 0;
for(r=0;r<5;r++)
{
for(c=0;c<5;c++)
{
mlfw_mat_double_set(matrix,r,c,value);
value=value+1.120;
}
}

for(r=0;r<5;r++)
{
for(c=0;c<5;c++)
{
printf(" %15.5lf ", mlfw_mat_double_get(matrix,r,c));
}
printf("\n");
}
mlfw_mat_double_destroy(matrix);
return 0;
}
