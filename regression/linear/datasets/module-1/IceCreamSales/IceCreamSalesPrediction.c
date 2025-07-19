#include<mlfw_matrix.h>
#include<mlfw_vector.h>
#include<mlfw_operations.h>
#include<stdio.h>
#define MODEL_FILE "trained_parameter.csv"
int main()
{
double temperature_c;
double temperature_f;
double profit;
char b;
double m,c;
mlfw_column_vec_double *model;
printf("Enter today's temprature: ");
scanf("%lf",&temperature_c);
while((b=getchar())!='\n' && b!=EOF);
temperature_f=((temperature_c*9)/5)+32;

model=mlfw_column_vec_double_from_csv(MODEL_FILE);
if(model==NULL) 
{
printf("Some problem\n");
return 0;
}
c=mlfw_column_vec_double_get(model,0);
m=mlfw_column_vec_double_get(model,1);
profit=(temperature_f*m)+c;
printf("Today's Profit is: %lf\n",profit);
mlfw_column_vec_double_destroy(model);
return 0;
}
