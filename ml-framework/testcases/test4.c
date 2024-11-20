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
index_t r,c;
mlfw_mat_double *I; //For Dataset to conversion of 'Xn' elements Matrix + One columns for Unity
dimension_t I_rows;
dimension_t I_columns;
dimension_t IT_rows;
dimension_t IT_columns;
mlfw_mat_double *IT;

dataset=mlfw_mat_double_from_csv("IceCreamSales.csv");
if(dataset==NULL)
{
printf("Unable to load dataset fromo IceCreamSales.csv File\n");
return ;
}

mlfw_mat_double_get_dimension(dataset,&dataset_rows,&dataset_columns);

for(r=0;r<dataset_rows;r++)
{
for(c=0;c<dataset_columns;c++)
{
printf("%lf ",mlfw_mat_double_get(dataset,r,c));
}
printf("\n");
}


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
mlfw_mat_double_copy(I,dataset,0,1,0,0,dataset_rows-1,0);

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


for(r=0;r<I_rows;r++)
{
for(c=0;c<I_columns;c++)
{
printf("%lf ",mlfw_mat_double_get(I,r,c));
}
printf("\n");
}
//IT=mlfw_mat_double_create_new(I_columns,I_rows);


IT=mlfw_mat_double_transpose(I);

if(IT==NULL)
{
printf("Unable to compute\n");
return ;
}
mlfw_mat_double_get_dimension(IT,&IT_rows,&IT_columns);

for(r=0;r<IT_rows;r++)
{
for(c=0;c<IT_columns;c++)
{
printf("%lf ",mlfw_mat_double_get(IT,r,c));
}
printf("\n");
}
}
int main()
{
int x;
train_it();
return 0;
}
