#include<mlfw_encoder.h>
#include<stdio.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
mlfw_row_vec_string * encode_columns;
dimension_t size;
char *input_file;
char *output_file;
index_t i;
if(argc<4)
{
printf("Usage: [./encode_one_hot.out input_file output_file column_name1 column_name2 ...]\n");
return 0;
}
input_file=argv[1];
output_file=argv[2];
encode_columns=mlfw_row_vec_string_create_new(argc-3);
if(encode_columns==NULL)
{
printf("Low on memory\n");
return 0;
}

for(i=3;i<argc;i++)
{
mlfw_row_vec_string_set(encode_columns,i-3,argv[i]);
}

mlfw_encoder_encode_one_hot(input_file,output_file,encode_columns);
mlfw_row_vec_string_destroy(encode_columns);
return 0;
}
