#include<mlfw_vector.h>
#include<mlfw_matrix.h>
#include<mlfw_learning.h>
#include<stdio.h>

double mlfw_get_r2_score(mlfw_column_vec_double *target_values_vector,mlfw_column_vec_double *predicted_values_vector)
{
mlfw_column_vec_double *A;
mlfw_column_vec_double *P;
mlfw_column_vec_double *R;
mlfw_row_vec_double *RT;
mlfw_column_vec_double *RTR;
double mean_of_actuals;
mlfw_column_vec_double *M;
mlfw_column_vec_double *AM;
mlfw_row_vec_double *AMT;
mlfw_column_vec_double *AMTAM;
double SSR;
double SST;
double r2score=0.0;
dimension_t target_values_vector_size,predicted_values_vector_size;
if(target_values_vector==NULL || predicted_values_vector==NULL) return r2score;
target_values_vector_size=mlfw_column_vec_double_get_size(target_values_vector);
predicted_values_vector_size=mlfw_column_vec_double_get_size(predicted_values_vector);
if(target_values_vector_size!=predicted_values_vector_size) return r2score;
A=target_values_vector;
P=predicted_values_vector;
R=mlfw_subtract_double_column_vector(A,P,NULL);
if(R==NULL) return r2score;
RT=mlfw_column_vec_double_transpose(R,NULL);
if(RT==NULL)
{
mlfw_column_vec_double_destroy(R);
return r2score;
}
RTR=mlfw_multiply_double_row_vector_with_column_vector(RT,R,NULL);
if(RTR==NULL)
{
mlfw_column_vec_double_destroy(R);
mlfw_row_vec_double_destroy(RT);
return r2score;
}
SSR=mlfw_column_vec_double_get(RTR,0);

mean_of_actuals=mlfw_column_vec_double_get_mean(A);
M=mlfw_column_vec_double_create_new_filled(target_values_vector_size,mean_of_actuals,NULL);
if(M==NULL)
{
mlfw_column_vec_double_destroy(R);
mlfw_row_vec_double_destroy(RT);
mlfw_column_vec_double_destroy(RTR);
return r2score;
}
AM=mlfw_subtract_double_column_vector(A,M,NULL);
if(AM==NULL)
{
mlfw_column_vec_double_destroy(R);
mlfw_row_vec_double_destroy(RT);
mlfw_column_vec_double_destroy(RTR);
mlfw_column_vec_double_destroy(M);
return r2score;
}
AMT=mlfw_column_vec_double_transpose(AM,NULL);
if(AMT==NULL)
{
mlfw_column_vec_double_destroy(R);
mlfw_row_vec_double_destroy(RT);
mlfw_column_vec_double_destroy(RTR);
mlfw_column_vec_double_destroy(M);
mlfw_column_vec_double_destroy(AM);
return r2score;
}
AMTAM=mlfw_multiply_double_row_vector_with_column_vector(AMT,AM,NULL);
if(AMTAM==NULL)
{
mlfw_column_vec_double_destroy(R);
mlfw_row_vec_double_destroy(RT);
mlfw_column_vec_double_destroy(RTR);
mlfw_column_vec_double_destroy(M);
mlfw_column_vec_double_destroy(AM);
mlfw_row_vec_double_destroy(AMT);
return r2score;
}
SST=mlfw_column_vec_double_get(AMTAM,0);
r2score=1-(SSR/SST);
//printf("Score of our tool is : %lf\n",r2score);

mlfw_column_vec_double_destroy(R);
mlfw_row_vec_double_destroy(RT);
mlfw_column_vec_double_destroy(RTR);
mlfw_column_vec_double_destroy(M);
mlfw_column_vec_double_destroy(AM);
mlfw_row_vec_double_destroy(AMT);
mlfw_column_vec_double_destroy(AMTAM);
return r2score;
}
