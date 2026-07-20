#include <stdio.h>
#include <mlfw_matrix.h>
/**
 * Author: Ashvin
 * Date: 2026-07-18
 * Description: 
 */
int main() {
mlfw_mat_double *matrix;
mlfw_mat_double *clone;
dimension_t rows,columns;
index_t r,c;

matrix=mlfw_mat_double_create_identity_matrix(5);
mlfw_mat_double_get_dimension(matrix,&rows,&columns);
for(r=0;r<rows;r++)
{
for(c=0;c<columns;c++)
{
printf("%lf ",mlfw_mat_double_get(matrix,r,c));
}
printf("\n");
}

printf("\n\n");

/*  WAY 1
clone=mlfw_mat_double_clone(matrix,NULL);
mlfw_mat_double_get_dimension(clone,&rows,&columns);

for(r=0;r<rows;r++)
{
for(c=0;c<columns;c++)
{
printf("%lf ",mlfw_mat_double_get(clone,r,c));
}
printf("\n");
}
*/

//WAY 2

clone=mlfw_mat_double_create_new(rows,columns);
clone=mlfw_mat_double_clone(matrix,clone);
mlfw_mat_double_get_dimension(clone,&rows,&columns);
for(r=0;r<rows;r++)
{
for(c=0;c<columns;c++)
{
printf("%lf ",mlfw_mat_double_get(clone,r,c));
}
printf("\n");
}

mlfw_mat_double_destroy(matrix);
mlfw_mat_double_destroy(clone);
    return 0;
}

