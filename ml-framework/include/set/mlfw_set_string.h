#ifndef __MLFW_SET_STRING__
#define __MLFW_SET_STRING__

struct __mlfw_set_string;
typedef struct  __mlfw_set_string mlfw_set_string;

mlfw_set_string * mlfw_set_string_create_new();
void mlfw_set_string_destroy(mlfw_set_string *set);

void mlfw_set_string_get(mlfw_set_string *set,index_t i,char **string);
//return -1 in case of low memory, 0 in case of  not added because of duplicacy, 1 in case of added
int mlfw_set_string_add(mlfw_set_string *set,char *string);
dimension_t mlfw_set_string_get_size(mlfw_set_string *set);

#endif
