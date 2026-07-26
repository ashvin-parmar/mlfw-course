#include <stdio.h>
#include <mlfw_matrix.h>
#include <mlfw_vector.h>
#include <stdlib.h>
/**
 * Author: Ashvin
 * Date: 2026-07-27
 * Description: 
 */
int main(int argc,char *argv[]) 
{
	mlfw_mat_double *matrix;
	mlfw_row_vec_string *header;
	dimension_t rows,columns;
	index_t i;
	double min,max;
	char column_title[11];
	char *filename;
	char *end;
	if(argc!=6)
	{
		printf("Usage [create_matrix_csv rows columns min max filename]\n");
		return 0;
	}

	rows=atoi(argv[1]);
	columns=atoi(argv[2]);
	min=strtod(argv[3],&end);
	max=strtod(argv[4],&end);
	filename=argv[5];
	matrix=mlfw_mat_double_create_new_random_filled(rows,columns,min,max,NULL);
	if(matrix==NULL)
	{
		printf("Unable to create matrix for csv file\n");
		return 0;
	}
	header=mlfw_row_vec_string_create_new(columns);
	if(header==NULL)
	{
		printf("Unable to create matrix for csv file\n");
		return 0;
	}
	for(i=0;i<columns;i++)
	{
		sprintf(column_title,"%u",i);
		mlfw_row_vec_string_set(header,i,column_title);
	}
	mlfw_mat_double_to_csv(matrix,filename,header);
	mlfw_mat_double_destroy(matrix);
	mlfw_row_vec_string_destroy(header);

    return 0;
}

