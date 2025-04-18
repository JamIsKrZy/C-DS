#ifndef VECTOR_STRING_H
#define VECTOR_STRING_H

#include "Vector_Template.h"


#define string char*
VECTORR_TEMPLATE_INIT_TYPE(string)
VECTOR_TEMPLATE_INIT_PROTOTYPE(string)

char* string_new_concat(char* str1, char* str2);
char* string_new_concat_dir(char* str1, char* str2);
void display_string(const char *val);
char* string_clone(const char* str);
size_t string_longest_size(Vector_string *vec, size_t minimum);
char *trim_prefix(const char *str1, const char *str2);

#endif