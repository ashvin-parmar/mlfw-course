#include<mlfw_scale.h>
#include<mlfw_matrix.h>
#include<mlfw_vector.h>
#include<stdio.h>
int main()
{
mlfw_mat_double *matrix;
mlfw_row_vec_string *header;
mlfw_row_vec_string *columns_to_scale;

columns_to_scale=mlfw_row_vec_string_create_new(2);
mlfw_row_vec_string_set(columns_to_scale,0,"salary");
mlfw_row_vec_string_set(columns_to_scale,1,"incentive");

//matrix=mlfw_scale_double("dummy.csv",columns_to_scale,"dummy_min-max_parameters.csv","min-max");
matrix=mlfw_scale_double("dummy.csv",columns_to_scale,"dummy_z-score_parameters.csv","z-score",NULL);

if(matrix==NULL)
{
printf("Unable to scale data\n");
mlfw_row_vec_string_destroy(columns_to_scale);
return 0;
}
header=mlfw_row_vec_string_create_new(4);
if(header==NULL)
{
mlfw_row_vec_string_destroy(columns_to_scale);
mlfw_mat_double_destroy(matrix);
return 0;
}
mlfw_row_vec_string_set(header,0,"age");
mlfw_row_vec_string_set(header,1,"height");
mlfw_row_vec_string_set(header,2,"salary");
mlfw_row_vec_string_set(header,3,"incentive");

//mlfw_mat_double_to_csv(matrix,"dummy_min-max_scaled.csv",header);
mlfw_mat_double_to_csv(matrix,"dummy_z-score_scaled.csv",header);

mlfw_row_vec_string_destroy(columns_to_scale);
mlfw_row_vec_string_destroy(header);
mlfw_mat_double_destroy(matrix);

return 0;
}
