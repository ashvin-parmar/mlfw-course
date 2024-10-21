//Testcase for Train Machine to learn new feature of finding minimum error Values

#include<mlfw_matrix.h>
#include<mlfw_vector.h>
#include<mlfw_operations.h>
#include<stdio.h>
#include<stdlib.h>
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
double sum_of_squared_error_values; //Value inside ETE which is ordered(1*1) Matrix (Column vector) 
double final_error_value; //Finally divide sum_of_squared_error with number of matrix 

dataset=mlfw_mat_double_from_csv("IceCreamSales.cssv");
if(dataset==NULL)
{
printf("Unable to load dataset fromo IceCreamSales.csv File\n");
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

/*  COPY
1 argu: Target Matrix
2 argu: Source Matrix to copy from
3 argu: Row index to start copy data from target matrix
4 argu: Columns index to start copy data from target matrix
5 argu: Row index to start copy data from source matrix
6 argu: Coulmn index to start copy data from source matrix
7 argu: Row index to end copy data from source matrix
8 argu: Column index to end copy data form source matrix
*/
//void mlfw_mat_double_copy(mlfw_mat_double *target,mlfw_mat_double *source,index_t from_target_row_index,index_t from_target_column_index,index_t from_source_row_index,index_t from_source_column_index,index_t to_source_row_index,index_t to_source_column_index);
mlfw_mat_double_copy(I,dataset,0,1,0,0,dataset_columns-1,0);

/* FILL
1 argu: Matrix to fill data
2 argu: Starting row index to fill value
3 argu: Starting columns index to fill value
4 argu: Ending row index to fill value
5 argu: Ending column index to fill value
6 argu: Value to fill on those places of matrix
*/
//void mlfw_mat_double_fill(mlfw_mat_double *matrix,index_t from_row_index,index_t from_column_index,index_t to_row_index,index_t to_column_index,double value);
mlfw_mat_double_fill(I,0,1,dataset_rows-1,0,1.0);

/*	CREATE COLUMN VECTOR FROM MATRIX COLUMN
1 argu: Target matrix of which columns are to be extracted in column vector
2 argu: Index of columns that need to be extracted
*/
//mlfw_column_vec_double * mlfw_mat_double_create_column_vec(mlfw_mat_double *matrix,index_t column_index);
A=mlfw_mat_double_create_column_vec(dataset,1);
if(A==NULL)
{
printf("Unable to Train, Low memory\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
return ;
}
/*	CREATE COLUMN VECTOR OF SIZE N for 'Mn' (Y=MX+C)
1 argu: Size equals to Xn's N elements so I_columns
2 argu: Set value as '0.0'
*/
//mlfw_column_vec_double * mlfw_column_vec_double_create_new_filled(dimension_t size,double value);
m=mlfw_column_vec_double_create_new_filled(I_columns,0.0);
if(m=NULL)
{
printf("Unable to Train, Low memory\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_column_vec_double_destroy(A);
return ;
}
/* CREATE A COLUMN MATRIX WITH ORDER AS (I_rows*1) Because Multiple of I and m gives us this (PREDICATE PROFIT)
 A=B*C
1 argu: Matrix A
2 argu: Matrix B (Maybe column vector)
*/
//mlfw_column_vec_double * mlfw_multiply_double_matrix_with_column_vector(mlfw_mat_double *matrix,mlfw_column_vec_double*vector);
P=mlfw_multiply_double_matrix_with_column_vector(I,m);
if(P==NULL)
{
printf("Unable to Train, Low memory\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_column_vec_double_destroy(A);
mlfw_column_vec_double_destroy(m);
return ;
}
/*	CREATE A COLUMN VECTOR OF ERROR VALUES (P-A) [Predicate-Actual]
1 argu: Predicated Values
2 argu: Actual Values
*/
//mlfw_column_vec_double * mlfw_subtract_double_column_vector(mlfw_column_vec_double *first_vector,mlfw_column_vec_double *second_vector);
E=mlfw_subtract_double_column_vector(P,A);
if(E==NULL)
{
printf("Unable to Train, Low memory\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_column_vec_double_destroy(A);
mlfw_column_vec_double_destroy(m);
mlfw_column_vec_double_destroy(P);
return ;
}
/*	COLUMN VECTOR TO ROW VECTOR (TRANSPOSE)
1 argu: Column vector to convert it into row vector
*/
//mlfw_row_vec_double * mlfw_transpose_double_column_vector(mlfw_column_vec_double *column_vector);
ET=mlfw_column_vec_double_transpose(E);
if(ET==NULL)
{
printf("Unable to Train, Low memory\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_column_vec_double_destroy(A);
mlfw_column_vec_double_destroy(m);
mlfw_column_vec_double_destroy(P);
mlfw_column_vec_double_destroy(E);
return;
}
/*	MULTIPLY TWO VECTOR
1 argu: Column vector
2 argu: Row vector
*/
//mlfw_column_vec_double * mlfw_multiply_double_column_vector_with_double_row_vector(mlfw_column_vec_double * column_vector,mlfw_row_vec_double *row_vector);
ETE=mlfw_multiply_double_row_vector_with_column_vector(ET,E);
if(ETE==NULL)
{
printf("Unable to Train, Low memory\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_column_vec_double_destroy(A);
mlfw_column_vec_double_destroy(m);
mlfw_column_vec_double_destroy(P);
mlfw_column_vec_double_destroy(E);
mlfw_row_vec_double_destroy(ET);
return ;
}
//double mlfw_column_vec_double_get(mlfw_column_vec_double *vector,index_t index);
sum_of_squared_error_values=mlfw_column_vec_double_get(ETE,0);
final_error_value=sum_of_squared_error_values/I_columns;

//Now, Here are logic to update 'Mi' and 'Ci' to minimizes error values of (Yi=MiXi+Ci)

//Releases memory
printf("Unable to Train, Low memory\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_column_vec_double_destroy(A);
mlfw_column_vec_double_destroy(m);
mlfw_column_vec_double_destroy(P);
mlfw_column_vec_double_destroy(E);
mlfw_row_vec_double_destroy(ET);
mlfw_column_vec_double_destroy(ETE);
}
//void mlfw_mat_double_copy(mlfw_mat_double *target,mlfw_mat_double *source,index_t from_target_row_index,index_t from_target_column_index,index_t from_source_row_index,index_t from_source_column_index,index_t to_source_row_index,index_t to_source_column_index);
//mlfw_column_vec_double * mlfw_mat_double_create_column_vec(mlfw_mat_double *matrix,index_t column_index);
//mlfw_column_vec_double * mlfw_multiply_double_matrix_with_column_vector(mlfw_mat_double *matrix,mlfw_column_vec_double*vector);
//mlfw_column_vec_double * mlfw_subtract_double_column_vector(mlfw_column_vec_double *first_vector,mlfw_column_vec_double *second_vector);
//mlfw_row_vec_double * mlfw_transpose_double_column_vector(mlfw_column_vec_double *column_vector);
//mlfw_column_vec_double * mlfw_multiply_double_column_vector_with_double_row_vector(mlfw_column_vec_double * column_vector,mlfw_row_vec_double *row_vector);
//double mlfw_column_vec_double_get(mlfw_column_vec_double *vector index_t index);
int main()
{
int x;
train_it();
return 0;
}
