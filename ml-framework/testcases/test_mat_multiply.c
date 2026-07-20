#include <stdio.h>
#include <mlfw_matrix.h>
#include <mlfw_vector.h>
#include <mlfw_operations.h>
/**
 * Author: Ashvin
 * Date: 2026-07-18
 * Description: 
 */
int main() {
mlfw_mat_double *matrix;
mlfw_mat_double *inverse_matrix;
mlfw_mat_double *identity_matrix;
mlfw_row_vec_string *header=NULL;
char *filename="test_mat_inv_mul.csv";
dimension_t rows,columns;
index_t r,c;

// matrix=mlfw_mat_double_create_new(3,3);
// mlfw_mat_double_set(matrix,0,0,2.0);
// mlfw_mat_double_set(matrix,0,1,1.0);
// mlfw_mat_double_set(matrix,0,2,3.0);
// 
// mlfw_mat_double_set(matrix,1,0,0.0);
// mlfw_mat_double_set(matrix,1,1,2.0);
// mlfw_mat_double_set(matrix,1,2,4.0);
// 
// mlfw_mat_double_set(matrix,2,0,1.0);
// mlfw_mat_double_set(matrix,2,1,1.0);
// mlfw_mat_double_set(matrix,2,2,2.0);

// matrix=mlfw_mat_double_create_new(2,2);	
// mlfw_mat_double_set(matrix,0,0,5.0);
// mlfw_mat_double_set(matrix,0,1,25.0);
// mlfw_mat_double_set(matrix,1,0,2.0);
// mlfw_mat_double_set(matrix,1,1,8.0);

matrix=mlfw_mat_double_from_csv(filename,NULL,&header);
if(matrix==NULL)
{
printf("Unable to load csv file\n");
return 0;
}
mlfw_mat_double_get_dimension(matrix,&rows,&columns);

printf("ORIGINAL MATRIX : \n");
for(r=0;r<rows;r++)
{
for(c=0;c<columns;c++)
{
printf("%lf ",mlfw_mat_double_get(matrix,r,c));
}
printf("\n");
}

printf("\n\n");

inverse_matrix=mlfw_mat_double_inverse(matrix,NULL);
if(inverse_matrix==NULL)
{
printf("Unable to create inverse of given matrix\n");
mlfw_mat_double_destroy(matrix);
return 0;
}
mlfw_mat_double_get_dimension(inverse_matrix,&rows,&columns);
printf("Inverse Matrix\n");
for(r=0;r<rows;r++)
{
for(c=0;c<columns;c++)
{
printf("%lf ",mlfw_mat_double_get(inverse_matrix,r,c));
}
printf("\n");
}
printf("\n\n");

identity_matrix=mlfw_multiply_double_matrix_with_matrix(matrix,inverse_matrix,NULL);
if(identity_matrix==NULL)
{
mlfw_mat_double_destroy(matrix);
mlfw_mat_double_destroy(inverse_matrix);
printf("Unable to multiply matrix\n");
return 0;
}

mlfw_mat_double_get_dimension(identity_matrix,&rows,&columns);
printf("Identity Matrix\n");
for(r=0;r<rows;r++)
{
for(c=0;c<columns;c++)
{
printf("%.16lf ",mlfw_mat_double_get(identity_matrix,r,c));
}
printf("\n");
}
printf("\n\n");


mlfw_mat_double_destroy(matrix);
mlfw_mat_double_destroy(inverse_matrix);
mlfw_mat_double_destroy(identity_matrix);
    return 0;
}

