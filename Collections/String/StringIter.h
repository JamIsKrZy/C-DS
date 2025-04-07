#ifndef STRING_ITERATORS_H
#define STRING_ITERATORS_H

#ifndef STRING_H_
    #warning "String Library is not imported! including to library..."
    #include "String.h"
#endif


#define DEFINE_ALL_STRING_ITER_TYPE
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
    String *str_ref;
};
char char_iter_next(struct CharIter iter);

#endif // CHAR_ITER
#if defined(STR_WINDOW_ITER)
struct StrWindowIter{
    size_t index;
    size_t window_size;
    String *str_ref;
};

StrSlice str_window_next(struct StrWindowIter);

#endif // STR_WINDOW_ITER
#if defined(MULTI_CHAR_ITER)

struct MultiCharIter{
    size_t index;
    size_t chuck;
    String *str_ref;
};

StrSlice multi_char_next(struct MultiCharIter);

#endif // MULTI_CHAR_ITER
#if defined(REVERSE_CHAR_ITER)

struct ReverseCharIter{
    size_t index;
    String *str_ref;
};

char reverse_char_next();


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



#endif // WORD_STRING_ITER

#if defined noninini
struct PredicateStrIter;
#endif

#endif