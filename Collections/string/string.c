#include "string.h"
#include <stdint.h>
#include "../vector/vector.h"
#include <string.h>
#include <stdint.h>

#define Char char

#define IF_STRING_ALLOCATED(str) if(!str->buffer.alloc){\
    panic("Unallocated String Memory");\
}

#define panic(msg, ...) do { \
    fprintf(stderr, "PANIC: at %s:%d: " msg "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
    abort(); \
} while (0)


String string_new(){
    return (String) {
        .buffer = vector_with_capacity(Char, 16),
    };
}

String string_clone(String *str){
    return (String){
        .buffer = vector_clone(str->buffer)
    };
}

String string_from_cstr(const char *cstr){
    if(!cstr){
        panic("String is Empty!");       
    }

    size_t len = strlen(cstr);
    String str = {
        .buffer = vector_with_capacity(Char, len)
    };

    memcpy(str.buffer.alloc, cstr, len);
    str.buffer.len = len;
    return str;
}

void string_push_cstr(String *str, const char *src){
    if(!str->buffer.alloc) {
        panic("String is not defined/allocated!");
    }
    
    __VectorChar__ local_buffer = str->buffer;

    size_t len = strlen(src);
    size_t f_len = local_buffer.len + len;
    while (f_len > local_buffer.cap){
        vector_grow(local_buffer);
    }
    
    memcpy(((char*) local_buffer.alloc)+local_buffer.len, src, len);
    local_buffer.len = f_len;

    str->buffer = local_buffer;
}

void print_string(String *str){
    IF_STRING_ALLOCATED(str);
    __VectorChar__ buffer = str->buffer;
    printf("%.*s\n", (int)buffer.len, buffer.alloc);
    
}

struct StringFormat string_format(String *str){
    IF_STRING_ALLOCATED(str);
    return (struct StringFormat){
        .spacing = str->buffer.len > INT32_MAX? 
            INT32_MAX : 
            (int)str->buffer.len,
        .ref = str->buffer.alloc
    };
}

void string_free(String str){
    if(!str.buffer.alloc){\
        panic("Unallocated String Memory");\
    }
    vector_free(str.buffer);
}


void string_clear(String *str){
    IF_STRING_ALLOCATED(str);
    str->buffer.len = 0;
}

StrSlice string_slice(
    const String *src, 
    const size_t start, 
    const size_t end
){
    __VectorChar__ local_buffer = src->buffer;
    if(!local_buffer.alloc) {
        panic("String is not defined/allocated!");
    } else if(end < start){
        panic("Incorrect Slice Handle! diagnostic: end < start");
    }else if(start >= local_buffer.len){
        panic("Slice start out of bounds!");
    } else if(end > local_buffer.len){
        panic("Slice end out of bounds!");
    }

    return (StrSlice){
        .ptr = ((char*)local_buffer.alloc)+start,
        .len = end - start
    };
}

StrSlice string_to_slice(String *str){
    return (StrSlice){
        .len = str->buffer.len,
        .ptr = str->buffer.alloc
    };
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"

StrSlice string_slice_from_cstr(
    char const *src, 
    const size_t start, 
    const size_t end
){  
    if(!src) {
        panic("String is not defined/allocated!");
    } 
    size_t len = strlen(src);
    if(end < start){
        panic("Incorrect Slice Handle! diagnostic: end < start");
    } else if(start > len){
        panic("Slice start out of bounds!");
    } else if(end > len){
        panic("Slice end out of bounds!");
    }

    return (StrSlice){
        .ptr = src + start,
        .len = end - start,
    };
}

#pragma GCC diagnostic pop



StrSlice string_slice_from_strslice(
    const StrSlice *src, 
    const size_t start, 
    const size_t end
){
    if(!src && !src->ptr) {
        panic("String is not defined/allocated!");
    } 

    if(end < start){
        panic("Incorrect Slice Handle! diagnostic: end < start");
    } else if(start > src->len){
        panic("Slice start out of bounds!");
    } else if(end > src->len){
        panic("Slice end out of bounds!");
    }

    return (StrSlice){
        .ptr = src->ptr + start,
        .len = end - start,
    };

}



struct StringFormat strslice_format(StrSlice *slice){
    return (struct StringFormat){
        .spacing = slice->len > INT32_MAX? INT32_MAX : (int)slice->len,
        .ref = slice->ptr
    };
}

char* string_into_cstr(String str){
    if(!str.buffer.alloc){\
        panic("Unallocated String Memory");\
    }
    (str.buffer.alloc)[str.buffer.len] = '\0';
    return str.buffer.alloc;
}


int str_slice_eq(StrSlice *str1, StrSlice *str2){
    if(str1->len != str2->len) return false;
    return !memcmp(str1->ptr, str2->ptr, str1->len);
}








