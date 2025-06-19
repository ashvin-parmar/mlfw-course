#include<mlfw_encoder.h>
#include<stdio.h>
#include<mlfw_vector.h>
int main()
{
mlfw_row_vec_string *header;
header=mlfw_row_vec_string_create_new(3);
mlfw_row_vec_string_set(header,0,"sex");
mlfw_row_vec_string_set(header,1,"smoker");
mlfw_row_vec_string_set(header,2,"region");
mlfw_encoder_encode_binary("insurance.csv","be_insurance.csv",header);
return 0;
}
