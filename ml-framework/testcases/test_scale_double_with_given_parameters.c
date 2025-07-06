#include<mlfw_scale.h>
#include<mlfw_matrix.h>
#include<mlfw_vector.h>
#include<stdio.h>
int main()
{
mlfw_mat_double *matrix;
mlfw_row_vec_string *header;

//matrix=mlfw_scale_double_with_given_parameters("dummy.csv","dummy_min-max_parameters.csv","min-max");
matrix=mlfw_scale_double_with_given_parameters("dummy.csv","dummy_z-score_parameters.csv","z-score");

if(matrix==NULL)
{
printf("Unable to scale data\n");
return 0;
}
header=mlfw_row_vec_string_create_new(4);
if(header==NULL)
{
mlfw_mat_double_destroy(matrix);
return 0;
}
mlfw_row_vec_string_set(header,0,"age");
mlfw_row_vec_string_set(header,1,"height");
mlfw_row_vec_string_set(header,2,"salary");
mlfw_row_vec_string_set(header,3,"incentive");

mlfw_mat_double_to_csv(matrix,"dummy_z-score_scaled_with_given_parameters.csv",header);

mlfw_row_vec_string_destroy(header);
mlfw_mat_double_destroy(matrix);

return 0;
}
