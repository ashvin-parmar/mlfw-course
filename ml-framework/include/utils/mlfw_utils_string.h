#ifndef __MLFW_UTILS_STRING__ 
#define __MLFW_UTILS_STRING__
#include<inttypes.h>
int mlfw_strcmp_case_insensitive(const char *left,const char *right);
void mlfw_uint32_to_binary(uint32_t number,char *binary_string);
#endif
