#ifndef STRING_H_
#define STRING_H_


#include <stddef.h>
#include <stdbool.h>

#define VEC_CHAR_STRING_TYPE
#include "../vector/vector.h"

#define __STRING_DEFINE__ 


typedef struct String {
    __VectorChar__ buffer;
} String; 

typedef struct StrSlice{
    char *ptr;
    size_t len;
} StrSlice;


/**
 * - Do not free
 * 
 */
struct StringFormat{
    int spacing;
    char *ref;
};


String string_new();
String string_clone(String *str);
String string_from_cstr(const char *cstr);
String string_from_slice(const char *cstr);

void string_push(char letter);
void string_push_str(String *str, String *src);
void string_push_cstr(String *str, const char *src);
StrSlice string_to_slice(String *str);

char* string_into_cstr(String str); 



StrSlice string_slice(const String *src, const size_t start, const size_t end);
StrSlice string_slice_from_cstr(char const *src, const size_t start, const size_t end);
StrSlice string_slice_from_strslice(const StrSlice *src, const size_t start, const size_t end);

void string_free(String str);

void print_string(String *str);

/**
 * Formats a String into a StringFormat struct.
 *
 * @param str Pointer to the String to format.
 * @return A StringFormat struct containing formatting data.
 *
 * @example \
 * String str = string_from("Hello, World!");
 * StringFormat fmt = string_format(&str);
 * print_format(&fmt);
 */
struct StringFormat string_format(String *str);
struct StringFormat strslice_format(StrSlice *slice);

size_t string_len(String *str);
void string_clear(String *str);

/**
 * @brief 
 * 
 * @param str1 
 * @param str2 
 * @return bool 
 *  
 */
int str_slice_eq(StrSlice *str1, StrSlice *str2);



#endif
