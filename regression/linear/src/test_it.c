//Testing history.csv data and predict values.

#include<mlfw_matrix.h>
#include<mlfw_vector.h>
#include<mlfw_operations.h>
#include<stdio.h>
#include<stdlib.h>

char *DATASET_FILE_NAME=NULL;
char *RESULTS_FILE_NAME=NULL;
char *PARAMETER_FILE_NAME=NULL;

void test_it()
{
FILE *result_file;
index_t r,c;
mlfw_mat_double *dataset; //For CSV File to Dataset matrix conversion
mlfw_row_vec_string *dataset_header;
dimension_t dataset_rows;
dimension_t dataset_columns;
mlfw_mat_double *I; //For Dataset to conversion of 'Xn' elements Matrix + One columns for Unity
dimension_t I_rows;
dimension_t I_columns;

mlfw_column_vec_double *m; //For Slope of matrix 'Mn' Values
mlfw_row_vec_string *parameter_header;

mlfw_column_vec_double *P; // For Predicated Matrix data values (That one column which can be generated based on I*m Matrix)
dataset=mlfw_mat_double_from_csv(DATASET_FILE_NAME,NULL,&dataset_header);
if(dataset==NULL)
{
printf("Unable to load dataset from %s File\n",DATASET_FILE_NAME);
return ;
}
mlfw_mat_double_get_dimension(dataset,&dataset_rows,&dataset_columns);
I_rows=dataset_rows;
I_columns=dataset_columns-1+1;		//+1 Columns for Unity | -1 Columns of Yn Data
I=mlfw_mat_double_create_new(I_rows,I_columns);
if(I==NULL)
{
printf("Unable to Test, Low on memory\n");
mlfw_mat_double_destroy(dataset);
mlfw_row_vec_string_destroy(dataset_header);
return ;
}
mlfw_mat_double_copy(I,dataset,0,1,0,0,dataset_rows-1,dataset_columns-2);

mlfw_mat_double_fill(I,0,0,dataset_rows-1,0,1.0);

m=mlfw_column_vec_double_from_csv(PARAMETER_FILE_NAME,NULL,&parameter_header);
if(m==NULL)
{
printf("Unable to Test, Low memory\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_row_vec_string_destroy(dataset_header);
return ;
}
P=mlfw_multiply_double_matrix_with_column_vector(I,m,NULL);
if(P==NULL)
{
printf("Unable to Test, Low memory\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_row_vec_string_destroy(dataset_header);
mlfw_column_vec_double_destroy(m);
mlfw_row_vec_string_destroy(parameter_header);
return ;
}
result_file=fopen(RESULTS_FILE_NAME,"w");
fprintf(result_file,"input(1),actual_output,predicted_output\n");
for(r=0;r<dataset_rows;r++)
{
for(c=0;c<dataset_columns;c++)
{
fprintf(result_file,"%lf,",mlfw_mat_double_get(dataset,r,c));
}
fprintf(result_file,"%lf\n",mlfw_column_vec_double_get(P,r));
}
fclose(result_file);
//Releases memory
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_row_vec_string_destroy(dataset_header);
mlfw_column_vec_double_destroy(m);
mlfw_row_vec_string_destroy(parameter_header);
mlfw_column_vec_double_destroy(P);
}
int main(int argc,char *argv[])
{
if(argc!=4)
{
printf("[Usage: test_it.out dataset_filename parameter_filename result_filename]\n");
return 0;
}
DATASET_FILE_NAME=argv[1];
PARAMETER_FILE_NAME=argv[2];
RESULTS_FILE_NAME=argv[3];
test_it();
return 0;
}
