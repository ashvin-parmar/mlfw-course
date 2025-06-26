#include<mlfw_matrix.h>
#include<mlfw_vector.h>
#include<mlfw_scale.h>
#include<stdio.h>
int main()
{
mlfw_mat_double *matrix;
mlfw_mat_double *scaled_matrix;
mlfw_mat_double *mean_standard_deviation_matrix;
mlfw_row_vec_string *header;
mlfw_row_vec_string *msd_header;
dimension_t rows,cols;

matrix=mlfw_mat_double_from_csv("dummy.csv",NULL,&header);
if(matrix==NULL)
{
printf("Unable to load dummy.csv file\n");
return 0;
}
mean_standard_deviation_matrix=mlfw_mat_double_from_csv("dummy_mean_standard_deviation.csv",NULL,&msd_header);
if(mean_standard_deviation_matrix==NULL)
{
printf("Unable to load dummy_mean_standard_deviation.csv file\n");
mlfw_mat_double_destroy(matrix);
mlfw_row_vec_string_destroy(header);
return 0;
}
mlfw_mat_double_get_dimension(matrix,&rows,&cols);

scaled_matrix=mlfw_scale_double_z_score_with_given_mean_standard_deviation(matrix,0,0,rows-1,cols-1,mean_standard_deviation_matrix,NULL);
if(scaled_matrix==NULL)
{
printf("Unable to scale data\n");
mlfw_mat_double_destroy(matrix);
mlfw_mat_double_destroy(mean_standard_deviation_matrix);
mlfw_row_vec_string_destroy(header);
mlfw_row_vec_string_destroy(msd_header);
return 0;
}
mlfw_mat_double_to_csv(scaled_matrix,"dummy_scaled_with_given.csv",msd_header);
printf("dummy_scaled_with_given.csv file created\n");
mlfw_mat_double_destroy(matrix);
mlfw_mat_double_destroy(scaled_matrix);
mlfw_mat_double_destroy(mean_standard_deviation_matrix);
mlfw_row_vec_string_destroy(header);
mlfw_row_vec_string_destroy(msd_header);
return 0;
}
