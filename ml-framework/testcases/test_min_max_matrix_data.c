#include<mlfw_matrix.h>
#include<stdio.h>
int main()
{
mlfw_mat_double *matrix;
double minimum,maximum;
dimension_t matrix_rows,matrix_columns;
matrix=mlfw_mat_double_from_csv("one_hot_encoded_insurance.csv");
if(matrix==NULL) return 0;
mlfw_mat_double_get_dimension(matrix,&matrix_rows,&matrix_columns);
minimum=mlfw_mat_double_get_minimum(matrix,1,matrix_rows-1,0,0);
maximum=mlfw_mat_double_get_maximum(matrix,1,matrix_rows-1,0,0);
printf("Minimum data: %lf\n",minimum);
printf("Maximum data: %lf\n",maximum);

mlfw_mat_double_destroy(matrix);
return 0;
}
