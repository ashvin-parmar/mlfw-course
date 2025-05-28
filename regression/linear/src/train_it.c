#include<mlfw_matrix.h>
#include<mlfw_vector.h>
#include<mlfw_operations.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>		//For threading implementation in c programming

uint8_t STOP_FLAG=0;
uint64_t NUMBER_OF_ITERATION=-1;
char *DATASET_FILE_NAME=NULL;
double LEARNING_RATE=1.0;
dimension_t HISTORY_FILE_SIZE=0;
char *HISTORY_FILE_NAME=NULL;
char *PARAMETERS_FILE_NAME=NULL;
char *GRAPH_FILE_NAME=NULL;

void train_it()
{
FILE * graph_file;
mlfw_mat_double *history;
dimension_t history_rows,history_columns;
double iteration_number;
index_t history_index;
index_t i,j;

mlfw_row_vec_string *history_header;
mlfw_row_vec_string *parameter_header;
char title[16];
int x;
mlfw_mat_double *dataset; //For CSV File to Dataset matrix conversion
mlfw_row_vec_string *dataset_header;
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
printf("Unable to Train, Low on memory\n");
mlfw_mat_double_destroy(dataset);
mlfw_row_vec_string_destroy(dataset_header);
return ;
}
mlfw_mat_double_copy(I,dataset,0,1,0,0,dataset_rows-1,dataset_columns-2);

mlfw_mat_double_fill(I,0,0,dataset_rows-1,0,1.0);


IT=mlfw_mat_double_transpose(I,NULL);
if(IT==NULL)
{
printf("Low memory\n");
mlfw_mat_double_destroy(dataset);
mlfw_row_vec_string_destroy(dataset_header);
mlfw_mat_double_destroy(I);
return ;
}


A=mlfw_mat_double_create_column_vec(dataset,dataset_columns-1,NULL);
if(A==NULL)
{
printf("Unable to Train, Low memory\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_row_vec_string_destroy(dataset_header);
mlfw_mat_double_destroy(IT);
return ;
}
m=mlfw_column_vec_double_create_new_filled(I_columns,0.0,NULL);
if(m==NULL)
{
printf("Unable to Train, Low memory\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_row_vec_string_destroy(dataset_header);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(A);
return ;
}

history_rows=HISTORY_FILE_SIZE;
history_columns=I_columns+2;	//1 for error values at index 1
				//2 for iteration values at index 0

history=mlfw_mat_double_create_new_filled(history_rows,history_columns,0.0,NULL);
if(history==NULL)
{
printf("Unable to Train, Low memory\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_row_vec_string_destroy(dataset_header);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(A);
mlfw_column_vec_double_destroy(m);
return ;
}
graph_file=fopen(GRAPH_FILE_NAME,"w");
history_index=0;
k=0;
P=NULL;
E=NULL;
ET=NULL;
ETE=NULL;
ITE=NULL;
TMP=NULL;
um=NULL;
while(STOP_FLAG==0)		//loop starts
{
if(k==NUMBER_OF_ITERATION) break;	//Termination from loop
P=mlfw_multiply_double_matrix_with_column_vector(I,m,P);
if(P==NULL)
{
printf("Unable to Train, Low memory\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_row_vec_string_destroy(dataset_header);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(A);
mlfw_column_vec_double_destroy(m);
mlfw_mat_double_destroy(history);
return ;
}
E=mlfw_subtract_double_column_vector(P,A,E);
if(E==NULL)
{
printf("Unable to Train, Low memory\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_row_vec_string_destroy(dataset_header);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(A);
mlfw_column_vec_double_destroy(m);
mlfw_mat_double_destroy(history);
mlfw_column_vec_double_destroy(P);
return ;
}
ET=mlfw_column_vec_double_transpose(E,ET);
if(ET==NULL)
{
printf("Unable to Train, Low memory\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_row_vec_string_destroy(dataset_header);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(A);
mlfw_column_vec_double_destroy(m);
mlfw_mat_double_destroy(history);
mlfw_column_vec_double_destroy(P);
mlfw_column_vec_double_destroy(E);
return;
}
ETE=mlfw_multiply_double_row_vector_with_column_vector(ET,E,ETE);
if(ETE==NULL)
{
printf("Unable to Train, Low memory\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_row_vec_string_destroy(dataset_header);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(A);
mlfw_column_vec_double_destroy(m);
mlfw_mat_double_destroy(history);
mlfw_column_vec_double_destroy(P);
mlfw_column_vec_double_destroy(E);
mlfw_row_vec_double_destroy(ET);
return ;
}
sum_of_squared_error_values=mlfw_column_vec_double_get(ETE,0);
final_error_value=sum_of_squared_error_values/(2*I_rows);	//change

printf("Iteration Number: %" PRIu64 ", Error: %20.15lf\n",k+1,final_error_value);
fprintf(graph_file,"%" PRIu64 ",%lf\n",k+1,final_error_value);
iteration_number=(double)(k+1);
//logic to store error values, iteration and thier respective m vector values to history matrix starts
if(history_index==HISTORY_FILE_SIZE)
{
for(i=1;i<HISTORY_FILE_SIZE;i++)
{
for(j=0;j<history_columns;j++)
{
mlfw_mat_double_set(history,i-1,j,mlfw_mat_double_get(history,i,j));
}
}
history_index--;
}

mlfw_mat_double_set(history,history_index,0,iteration_number);
mlfw_mat_double_set(history,history_index,1,final_error_value);
j=mlfw_column_vec_double_get_size(m);
for(i=0;i<j;i++)
{
mlfw_mat_double_set(history,history_index,i+2,mlfw_column_vec_double_get(m,i));
//printf("Data: %lf\n",mlfw_column_vec_double_get(m,i));
}
history_index++;

//logic to store error values, iteration and thier respective m vector values to history matrix ends

//Now, Here are logic to update 'Mi' and 'Ci' to minimizes error values of (Yi=MiXi+Ci)
ITE=mlfw_multiply_double_matrix_with_column_vector(IT,E,ITE);
if(ITE==NULL)
{
printf("Low memory\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_row_vec_string_destroy(dataset_header);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(A);
mlfw_column_vec_double_destroy(m);
mlfw_mat_double_destroy(history);
mlfw_column_vec_double_destroy(P);
mlfw_column_vec_double_destroy(E);
mlfw_row_vec_double_destroy(ET);
mlfw_column_vec_double_destroy(ETE);
return ;
}
						//Learning rate
TMP=mlfw_multiply_double_scalar_with_column_vector((LEARNING_RATE)*(1.0/I_rows),ITE,TMP);
if(TMP==NULL)
{
printf("Low memory\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_row_vec_string_destroy(dataset_header);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(A);
mlfw_column_vec_double_destroy(m);
mlfw_mat_double_destroy(history);
mlfw_column_vec_double_destroy(P);
mlfw_column_vec_double_destroy(E);
mlfw_row_vec_double_destroy(ET);
mlfw_column_vec_double_destroy(ETE);
mlfw_column_vec_double_destroy(ITE);
return;
}

um=mlfw_subtract_double_column_vector(m,TMP,NULL);
if(um==NULL)
{
printf("Low memory\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_row_vec_string_destroy(dataset_header);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(A);
mlfw_column_vec_double_destroy(m);
mlfw_mat_double_destroy(history);
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

//mlfw_column_vec_double_destroy(P);
//mlfw_column_vec_double_destroy(E);
//mlfw_row_vec_double_destroy(ET);
//mlfw_column_vec_double_destroy(ETE);
//mlfw_column_vec_double_destroy(ITE);
//mlfw_column_vec_double_destroy(TMP);
++k;
}
fclose(graph_file);
//Store history matrix values in a file

history_header=mlfw_row_vec_string_create_new(history_columns);
if(history_header==NULL)
{
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_row_vec_string_destroy(dataset_header);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(A);
mlfw_column_vec_double_destroy(m);
mlfw_mat_double_destroy(history);
return ;
}
mlfw_row_vec_string_set(history_header,0,"iteration_number");
mlfw_row_vec_string_set(history_header,1,"error");
j=mlfw_column_vec_double_get_size(m);
for(i=0;i<j;i++)
{
sprintf(title,"theta(%d)",i);
mlfw_row_vec_string_set(history_header,i+2,title);
}
parameter_header=mlfw_row_vec_string_create_new(j);
if(parameter_header==NULL)
{
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_row_vec_string_destroy(dataset_header);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(A);
mlfw_column_vec_double_destroy(m);
mlfw_mat_double_destroy(history);
mlfw_row_vec_string_destroy(history_header);
return ;
}
for(i=0;i<j;i++)
{
sprintf(title,"theta(%d)",i);
mlfw_row_vec_string_set(parameter_header,i,title);
}

mlfw_mat_double_to_csv(history,HISTORY_FILE_NAME,history_header);
mlfw_column_vec_double_to_csv(m,PARAMETERS_FILE_NAME,parameter_header);
//Releases memory
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_row_vec_string_destroy(dataset_header);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(A);
mlfw_column_vec_double_destroy(m);
mlfw_mat_double_destroy(history);

mlfw_column_vec_double_destroy(P);
mlfw_column_vec_double_destroy(E);
mlfw_row_vec_double_destroy(ET);
mlfw_column_vec_double_destroy(ETE);
mlfw_column_vec_double_destroy(ITE);
mlfw_column_vec_double_destroy(TMP);
//mlfw_column_vec_double_destroy(um);		//Because matrix m already released

mlfw_row_vec_string_destroy(history_header);
mlfw_row_vec_string_destroy(parameter_header);
}
void * thread_function(void *p)
{
train_it();
return NULL;
}
int main(int argc,char *argv[])
{
pthread_t thread_id;
char *ptr;
char m;
int result;
if(argc!=7 && argc!=8)
{
printf("[Usage: train_it.out dataset_filename learning_rate history_file_name history_file_size parameter_file graph_data_file number_of_iteration(optional)]\n");
return 0;
}
DATASET_FILE_NAME=argv[1];
ptr=NULL;
LEARNING_RATE=(double)strtod(argv[2],&ptr);
HISTORY_FILE_NAME=argv[3];
ptr=NULL;
HISTORY_FILE_SIZE=(dimension_t)strtoull(argv[4],&ptr,10);
if(HISTORY_FILE_SIZE<5) 
{
printf("History file size must be more than equal to 5.\n");
return 0;
}
PARAMETERS_FILE_NAME=argv[5];
GRAPH_FILE_NAME=argv[6];
if(argc==8)
{
ptr=NULL;
NUMBER_OF_ITERATION=strtoull(argv[7],&ptr,10);
}

result=pthread_create(&thread_id,NULL,thread_function,NULL);
if(result!=0)
{
printf("Unable to create thread\n");
return 0;
}
while(1)		//an infinite loop on main thread
{
m=getchar();
if(m=='\n')		//enter key passed
{
STOP_FLAG=1;
break;
}
}
pthread_join(thread_id,NULL);	//wait for the thread to end thread_function
return 0;
}
