#define DEFINE_ALL_STRING_ITER_TYPE
#include "StringIter.h"

struct CharIter char_iter_new(String *str){
    return (struct CharIter){
        .index = 0,
        .str_ref = str
    };
}
bool char_iter_next(struct CharIter *iter, char *return_val){
    if(!iter){
        *return_val = 0;
        return false;
    }

    if(iter->index >= iter->str_ref->buffer.len){
        *return_val = 0;
        return false;
    }

    *return_val = iter->str_ref->buffer.alloc[iter->index++];
    return true;
}


struct StrWindowIter str_window_new(String *str, size_t window_size){
    return (struct StrWindowIter){
        .index = 0,
        .window_size = window_size,
        .str_ref = str
    };
}

bool str_window_next(struct StrWindowIter *iter, StrSlice *return_slice){
    if(!iter){
        return_slice->len = 0;
        return_slice->ptr = NULL;
        return false;
    }

    size_t window_size = iter->window_size; 

    if((iter->index + window_size) > iter->str_ref->buffer.len){
        return_slice->len = 0;
        return_slice->ptr = NULL;
        return false;
    }

    return_slice->len = window_size;
    return_slice->ptr = iter->str_ref->buffer.alloc + iter->index;

    iter->index += 1;
    return true;
}   

struct MultiCharIter multi_char_new(String *str, size_t chuck_size){
    return (struct MultiCharIter){
        .chunck = chuck_size,
        .index = 0,
        .str_ref = str
    };
}
bool multi_char_next(struct MultiCharIter *iter, StrSlice *return_slice) {
    if (!iter || !iter->str_ref) {
        return_slice->len = 0;
        return_slice->ptr = NULL;
        return false;
    }

    size_t index = iter->index;
    size_t chunk = iter->chunck;

    const struct String *str_ref = iter->str_ref;
    const VectorChar *buffer = &str_ref->buffer;

    size_t buf_len = buffer->len;
    char *buf_ptr = buffer->alloc;

    if (index >= buf_len) {
        return_slice->len = 0;
        return_slice->ptr = NULL;
        return false;
    }

    size_t slice_len = (index + chunk >= buf_len) ? (buf_len - index) : chunk;
    return_slice->len = slice_len;
    return_slice->ptr = buf_ptr + index;

    iter->index = index + chunk;

    return true;
}

struct RevCharIter rev_char_new(String *str){
    return (struct RevCharIter){
        .index = str->buffer.len-1,
        .str_ref = str
    };
}
bool rev_char_next(
    struct RevCharIter *iter, 
    char *return_char
){
    if(!iter || iter->index >= iter->str_ref->buffer.len) return false;


    *return_char = iter->str_ref->buffer.alloc[iter->index];
    if(iter->index == 0){
        iter->index = iter->str_ref->buffer.len;
        return true;
    }
    iter->index -= 1;
    return true;
}

struct WordStrIter word_str_iter_new(String *str){
    return (struct WordStrIter){
        .index = 0,
        .str_ref = str
    };
}
bool word_str_iter_next(
    struct WordStrIter *iter, 
    StrSlice *return_slice
){
    if(!iter) return false;

    size_t index_arr = iter->index;
    VectorChar vec = iter->str_ref->buffer;

    if(index_arr < vec.len){
        
        while (vec.alloc[index_arr] == ' '){
            if(index_arr >= vec.len) goto out;
            index_arr++;
        }
        return_slice->ptr = vec.alloc + index_arr;

        while (vec.alloc[index_arr] != ' '){
            if(index_arr >= vec.len) break;
            index_arr++;
        }
        return_slice->len = (vec.alloc + index_arr) - (return_slice->ptr); 
        iter->index = index_arr;

        return true;
    }   
    out:

    *return_slice = (StrSlice){
        .len = 0,
        .ptr = NULL
    };
    return false;
}




