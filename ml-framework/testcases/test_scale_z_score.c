#include<mlfw_matrix.h>
#include<mlfw_vector.h>
#include<mlfw_scale.h>
#include<stdio.h>
int main()
{
mlfw_mat_double *matrix;
mlfw_mat_double *scaled_matrix;
mlfw_row_vec_string *header;
dimension_t rows,cols;

matrix=mlfw_mat_double_from_csv("dummy.csv",NULL,&header);
if(matrix==NULL)
{
printf("Unable to load dummy.csv file\n");
return 0;
}
mlfw_mat_double_get_dimension(matrix,&rows,&cols);

scaled_matrix=mlfw_scale_double_z_score(matrix,0,0,rows-1,cols-1,"dummy_mean_standard_deviation.csv",NULL);
mlfw_mat_double_to_csv(scaled_matrix,"dummy_scaled.csv",header);
printf("Data scaled with Z-score normalization method\n");
printf("dummy_scaled.csv and dummy_mean_standard_deviation.csv file created\n");
mlfw_mat_double_destroy(matrix);
mlfw_mat_double_destroy(scaled_matrix);
mlfw_row_vec_string_destroy(header);
return 0;
}
