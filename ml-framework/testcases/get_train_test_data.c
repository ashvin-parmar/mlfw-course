#include<mlfw_matrix.h>
#include<stdio.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
mlfw_mat_double *training_matrix,*testing_matrix;
mlfw_row_vec_string *header;
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
header=mlfw_row_vec_string_create_new(2);
if(header==NULL)
{
printf("Low on memory\n");
return 0;
}

mlfw_mat_double_get_training_testing_data(dataset_file,&training_matrix,&testing_matrix,minor_percentage);
if(training_matrix==NULL || testing_matrix==NULL)
{
printf("Unable to create training or testing matrix, Low on memory\n");
return 0;
}

mlfw_row_vec_string_set(header,0,"temperature");
mlfw_row_vec_string_set(header,1,"profit");

mlfw_mat_double_to_csv(training_matrix,train_file,header);
mlfw_mat_double_to_csv(testing_matrix,test_file,header);

mlfw_mat_double_destroy(training_matrix);
mlfw_mat_double_destroy(testing_matrix);
return 0;
}
