#include<mlfw_matrix.h>
#include<mlfw_vector.h>
#include<stdio.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
mlfw_mat_string *matrix,*shuffle_matrix,*minor_matrix,*major_matrix;
mlfw_row_vec_string *header;
dimension_t major_rows,minor_rows;
dimension_t shuffle_matrix_rows,shuffle_matrix_columns;
int minor_percentage;
char *dataset_file,*test_file,*train_file;
if(argc!=5)
{
printf("Usage: [create_test_train_dataset dataset_file test_file train_file minor_percentage]\n");
return 0;
}
dataset_file=argv[1];
test_file=argv[2];
train_file=argv[3];
minor_percentage=atoi(argv[4]);
if(minor_percentage<=0 || minor_percentage>=50)
{
printf("Invalid minor percentage %d\n",minor_percentage);
return 0;
}
matrix=mlfw_mat_string_from_csv(dataset_file,NULL,&header);
if(matrix==NULL)
{
printf("Unable to load %s\n",dataset_file);
return 0;
}
shuffle_matrix=mlfw_mat_string_shuffle(matrix,3,NULL);
if(shuffle_matrix==NULL)
{
printf("Unable to create test/train dataset files\n");
mlfw_mat_string_destroy(matrix);
mlfw_row_vec_string_destroy(header);
return 0;
}
mlfw_mat_string_get_dimension(shuffle_matrix,&shuffle_matrix_rows,&shuffle_matrix_columns);
minor_rows=(dimension_t)(minor_percentage*shuffle_matrix_rows)/100;
major_rows=shuffle_matrix_rows-minor_rows;

minor_matrix=mlfw_mat_string_create_new(minor_rows,shuffle_matrix_columns);
if(minor_matrix==NULL)
{
printf("Unable to create test/train dataset files\n");
mlfw_mat_string_destroy(matrix);
mlfw_row_vec_string_destroy(header);
mlfw_mat_string_destroy(shuffle_matrix);
return 0;
}
major_matrix=mlfw_mat_string_create_new(major_rows,shuffle_matrix_columns);
if(major_matrix==NULL)
{
printf("Unable to create test/train dataset files\n");
mlfw_mat_string_destroy(matrix);
mlfw_row_vec_string_destroy(header);
mlfw_mat_string_destroy(shuffle_matrix);
mlfw_mat_string_destroy(minor_matrix);
return 0;
}
mlfw_mat_string_copy(minor_matrix,shuffle_matrix,0,0,0,0,minor_rows-1,shuffle_matrix_columns-1);
mlfw_mat_string_copy(major_matrix,shuffle_matrix,0,0,minor_rows,0,shuffle_matrix_rows-1,shuffle_matrix_columns-1);
mlfw_mat_string_to_csv(minor_matrix,test_file,header);
mlfw_mat_string_to_csv(major_matrix,train_file,header);

mlfw_mat_string_destroy(matrix);
mlfw_row_vec_string_destroy(header);
mlfw_mat_string_destroy(shuffle_matrix);
mlfw_mat_string_destroy(minor_matrix);
mlfw_mat_string_destroy(major_matrix);
return 0;
}
