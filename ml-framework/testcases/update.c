//Testcase for Train Machine to learn new feature of finding minimum error Values
//Update m and c value's as per sir code

#include<mlfw_matrix.h>
#include<mlfw_vector.h>
#include<mlfw_operations.h>
#include<stdio.h>
#include<stdlib.h>

uint64_t NUMBER_OF_ITERATION=100000;
void train_it()
{
mlfw_mat_double *dataset; //For CSV File to Dataset matrix conversion
dimension_t dataset_rows;
dimension_t dataset_columns;

mlfw_mat_double *I; //For Dataset to conversion of 'Xn' elements Matrix + One columns for Unity
dimension_t I_rows;
dimension_t I_columns;

mlfw_column_vec_double *A; //For Actual Matrix data values (That one columns from dataset Matrix for 'Yn')
mlfw_column_vec_double *m; //For Slope of matrix 'Mn' Values
mlfw_column_vec_double *P; // For Predicated Matrix data values (That one column which can be generated based on I*m Matrix)
mlfw_column_vec_double *E; //Error Values data (Predicate -Actual) [P-A]
mlfw_row_vec_double *ET; //Transpose of E Column vector to Row Vector
mlfw_column_vec_double *ETE; //Multiplication of E with E(Transpose) : Gives ETE

mlfw_mat_double *IT;

mlfw_column_vec_double *ITE;

mlfw_column_vec_double *TMP;

mlfw_column_vec_double *um;

uint64_t k;
double sum_of_squared_error_values; //Value inside ETE which is ordered(1*1) Matrix (Column vector) 
double final_error_value; //Finally divide sum_of_squared_error with number of matrix 
char filename[101];
//printf("Enter training dataset name[.csv formate]: ");
//scanf("%s",filename);
//dataset=mlfw_mat_double_from_csv(filename);
dataset=mlfw_mat_double_from_csv("training_dataset.csv");
if(dataset==NULL)
{
printf("Unable to load dataset from %s File\n",filename);
return ;
}
mlfw_mat_double_get_dimension(dataset,&dataset_rows,&dataset_columns);
I_rows=dataset_rows;
I_columns=dataset_columns-1+1;		//+1 Columns for Unity | -1 Columns of Yn Data
I=mlfw_mat_double_create_new(I_rows,I_columns);
if(I==NULL)
{
printf("Unable to Train, Low on memory\n");
mlfw_mat_double_destroy(dataset);
return ;
}
mlfw_mat_double_copy(I,dataset,0,1,0,0,dataset_rows-1,dataset_columns-1);

mlfw_mat_double_fill(I,0,0,dataset_rows-1,0,1.0);


IT=mlfw_mat_double_transpose(I);
if(IT==NULL)
{
printf("Low memory\n");
mlfw_mat_double_destroy(dataset);
mlfw_mat_double_destroy(I);
return ;
}


A=mlfw_mat_double_create_column_vec(dataset,1);
if(A==NULL)
{
printf("Unable to Train, Low memory\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_mat_double_destroy(IT);
return ;
}
m=mlfw_column_vec_double_create_new_filled(I_columns,0.0);
if(m==NULL)
{
printf("Unable to Train, Low memory\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(A);
return ;
}

k=1;
while(k<=NUMBER_OF_ITERATION)
{

P=mlfw_multiply_double_matrix_with_column_vector(I,m);
if(P==NULL)
{
printf("Unable to Train, Low memory\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(A);
mlfw_column_vec_double_destroy(m);
return ;
}
E=mlfw_subtract_double_column_vector(P,A);
if(E==NULL)
{
printf("Unable to Train, Low memory\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(A);
mlfw_column_vec_double_destroy(m);
mlfw_column_vec_double_destroy(P);
return ;
}
ET=mlfw_column_vec_double_transpose(E);
if(ET==NULL)
{
printf("Unable to Train, Low memory\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(A);
mlfw_column_vec_double_destroy(m);
mlfw_column_vec_double_destroy(P);
mlfw_column_vec_double_destroy(E);
return;
}
ETE=mlfw_multiply_double_row_vector_with_column_vector(ET,E);
if(ETE==NULL)
{
printf("Unable to Train, Low memory\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(A);
mlfw_column_vec_double_destroy(m);
mlfw_column_vec_double_destroy(P);
mlfw_column_vec_double_destroy(E);
mlfw_row_vec_double_destroy(ET);
return ;
}
sum_of_squared_error_values=mlfw_column_vec_double_get(ETE,0);
final_error_value=sum_of_squared_error_values/(2*I_rows);	//change

printf("Iteration Number: %" PRIu64 ", Error: %20.15lf\n",k,final_error_value);

//Now, Here are logic to update 'Mi' and 'Ci' to minimizes error values of (Yi=MiXi+Ci)
ITE=mlfw_multiply_double_matrix_with_column_vector(IT,E);
if(ITE==NULL)
{
printf("1: Low memory\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(A);
mlfw_column_vec_double_destroy(m);
mlfw_column_vec_double_destroy(P);
mlfw_column_vec_double_destroy(E);
mlfw_row_vec_double_destroy(ET);
mlfw_column_vec_double_destroy(ETE);
return ;
}
						//Learning rate
TMP=mlfw_multiply_double_scalar_with_column_vector(0.0001/I_rows,ITE);
if(TMP==NULL)
{
printf("2: Low memory\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(A);
mlfw_column_vec_double_destroy(m);
mlfw_column_vec_double_destroy(P);
mlfw_column_vec_double_destroy(E);
mlfw_row_vec_double_destroy(ET);
mlfw_column_vec_double_destroy(ETE);
mlfw_column_vec_double_destroy(ITE);
return;
}

um=mlfw_subtract_double_column_vector(m,TMP);
if(um==NULL)
{
printf("3: Low memory\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(A);
mlfw_column_vec_double_destroy(m);
mlfw_column_vec_double_destroy(P);
mlfw_column_vec_double_destroy(E);
mlfw_row_vec_double_destroy(ET);
mlfw_column_vec_double_destroy(ETE);
mlfw_column_vec_double_destroy(ITE);
mlfw_column_vec_double_destroy(TMP);
return;
}
mlfw_column_vec_double_destroy(m);		//old m vector released
m=um; 	//now, m is pointing to newly created vector with updated values

mlfw_column_vec_double_destroy(P);
mlfw_column_vec_double_destroy(E);
mlfw_row_vec_double_destroy(ET);
mlfw_column_vec_double_destroy(ETE);
mlfw_column_vec_double_destroy(ITE);
mlfw_column_vec_double_destroy(TMP);
++k;
}
//Releases memory
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(A);
mlfw_column_vec_double_destroy(m);
}
int main()
{
int x;
train_it();
return 0;
}
