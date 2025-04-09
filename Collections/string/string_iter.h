#ifndef STRING_ITERATORS_H
#define STRING_ITERATORS_H

#include "stdbool.h"

#ifndef STRING_H_
    #warning "String Library is not imported! including to library..."
    #include "string.h"
#endif


// #define DEFINE_ALL_STRING_ITER_TYPE
#if defined(DEFINE_ALL_STRING_ITER_TYPE)
#define CHAR_ITER
#define STR_WINDOW_ITER
#define MULTI_CHAR_ITER
#define REVERSE_CHAR_ITER
#define STRING_LINE_ITER
#define WORD_STRING_ITER
#endif // DEFINE_ALL_STRING_TYPE


#if defined(CHAR_ITER)
struct CharIter{
    size_t index;
    const String *str_ref;
};

struct CharIter char_iter_new(String *str);
bool char_iter_next(struct CharIter *iter, char *return_val);

#endif // CHAR_ITER
#if defined(STR_WINDOW_ITER)
struct StrWindowIter{
    size_t index;
    size_t window_size;
    const String  *str_ref;
};
struct StrWindowIter str_window_new(String *str, size_t window_size);
bool str_window_next(struct StrWindowIter *iter, StrSlice *return_slice);

#endif // STR_WINDOW_ITER
#if defined(MULTI_CHAR_ITER)

struct MultiCharIter{
    size_t index;
    size_t chunck;
    const String *str_ref;
};

struct MultiCharIter multi_char_new(String *str, size_t chuck_size); 
bool multi_char_next(struct MultiCharIter *iter, StrSlice *return_slice);

#endif // MULTI_CHAR_ITER
#if defined(REVERSE_CHAR_ITER)

struct RevCharIter{
    size_t index;
    String *str_ref;
};

struct RevCharIter rev_char_new(String *str);
bool rev_char_next(struct RevCharIter *iter, char *return_char);


#endif // REVERSE_STRING_ITER
#if defined(STRING_LINE_ITER)

struct StrLineIter{
    size_t index;
    String *str_ref;
};

#endif // STRING_LINE_ITER
#if defined(WORD_STRING_ITER)

struct WordStrIter{
    size_t index;
    String *str_ref;
};

struct WordStrIter word_str_iter_new(String *str);
bool word_str_iter_next(struct WordStrIter *iter, StrSlice *return_slice);


#endif // WORD_STRING_ITER

#if defined noninini
struct PredicateStrIter;
#endif

#endif