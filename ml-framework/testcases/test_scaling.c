#include<mlfw_matrix.h>
#include<mlfw_scale.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
mlfw_mat_double *matrix;
mlfw_mat_double *scale_matrix;
dimension_t matrix_rows,matrix_columns;
				//We have removed first line 'header' of one_hot_encoded_insurance.csv for making it double type matrix
matrix=mlfw_mat_double_from_csv("one_hot_encoded_insurance.csv");
if(matrix==NULL) return 0;
mlfw_mat_double_get_dimension(matrix,&matrix_rows,&matrix_columns);

scale_matrix=mlfw_scale_double_min_max(matrix,0,matrix_rows-1,0,matrix_columns-1);
mlfw_mat_double_to_csv(scale_matrix,"scale_min_max.csv");

mlfw_mat_double_destroy(scale_matrix);
mlfw_mat_double_destroy(matrix);
return 0;
}
