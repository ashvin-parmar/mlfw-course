#include<stdio.h>
#include<stdlib.h>
#include<stdio_ext.h>
#include<mlfw_matrix.h>
#include<mlfw_vector.h>
#include<mlfw_operations.h>
int main(int argc,char *argv[])
{
double temperature_c;
double temperature_f;
double profit;
mlfw_column_vec_double *parameter_vector;
mlfw_row_vec_double *featured_vector;
mlfw_column_vec_double *predicted_value_vector;
FILE *file;
if(argc!=2)
{
printf("Usage: [App temperature_in_celcius]\n");
return 0;
}
file=fopen("trained_parameter.csv","r");
if(file==NULL)
{
fprintf(stderr,"trained_parameter.csv does not exists\n");
return 0;
}
temperature_c=strtod(argv[1],NULL);
temperature_f=(temperature_c*9.0/5.0)+32.0;
featured_vector=mlfw_row_vec_double_create_new(2);
if(featured_vector==NULL)
{
printf("Low on memory\n");
return 0;
}
mlfw_row_vec_double_set(featured_vector,0,1.0);
mlfw_row_vec_double_set(featured_vector,1,temperature_f);
parameter_vector=mlfw_column_vec_double_from_csv("trained_parameter.csv");
if(parameter_vector==NULL)
{
printf("Low on memory\n");
mlfw_row_vec_double_destroy(featured_vector);
return 0;
}
predicted_value_vector=mlfw_multiply_double_row_vector_with_column_vector(featured_vector,parameter_vector);
if(predicted_value_vector==NULL)
{
printf("Low on memory\n");
mlfw_row_vec_double_destroy(featured_vector);
mlfw_column_vec_double_destroy(parameter_vector);
return 0;
}
profit=mlfw_column_vec_double_get(predicted_value_vector,0);
mlfw_row_vec_double_destroy(featured_vector);
mlfw_column_vec_double_destroy(parameter_vector);
mlfw_column_vec_double_destroy(predicted_value_vector);
printf("Predicted Profit in USD: %10.2lf\n",profit);
return 0;
}
