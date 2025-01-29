#include<mlfw_encoder.h>
#include<stdio.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
int *encode_columns;
char *column_string;
char *s,*e;
dimension_t size;
char *input_file;
char *output_file;
char has_header;
int header_exists;
index_t i;
if(argc!=5)
{
printf("Usage: [./encode_one_hot.out input_file output_file column_to_encode(Comma-Seperated) has_header]\n");
return 0;
}
input_file=argv[1];
output_file=argv[2];
column_string=argv[3];
has_header=argv[4][0];
if(has_header=='y' || has_header=='Y') header_exists=1;
else header_exists=0;
size=0;
for(i=0,size=0;column_string[i]!='\0';i++)
{
if(column_string[i]==',') size++;
}
size++;
encode_columns=(int *)malloc(sizeof(int)*size);
if(encode_columns==NULL)
{
printf("Low on memory\n");
return 0;
}
i=0;
s=column_string;
while(1)
{
e=s+1;
while(*e!='\0' && *e!=',') e++;
if(*e=='\0') 
{
encode_columns[i]=atoi(s);
break;
}
else 
{
*e='\0';
encode_columns[i]=atoi(s);
i++;
s=e+1;
}
}
mlfw_encoder_encode_one_hot(input_file,output_file,encode_columns,size,header_exists);
free(encode_columns);
return 0;
}
