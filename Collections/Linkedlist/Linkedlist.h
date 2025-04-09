#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_


#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

#ifndef todo
    #define todo ({\
        fprintf(stderr, "Unimplemented! at %s:%d: \n", __FILE__, __LINE__); \
        abort();\
    })
#endif


#define INIT_LINKEDLIST_TYPE(type)\
struct ll_node_##type {\
    struct ll_node_##type *next;\
    struct ll_node_##type *prev; \
    type element;\
};\
typedef struct {\
    struct ll_node_##type *head;\
    struct ll_node_##type *tail;\
    size_t len;\
} Linkedlist##type;\

#define LL_ALLOC(type) calloc(1, sizeof(type))

#define list_new() {\
    .head = NULL,\
    .tail = NULL,\
    .len = 0,\
}


#define list_from(type,...) ({\
    type arr[] = __VA_ARGS__;\
    size_t len = sizeof(arr)/sizeof(arr[0]);\
    Linkedlist##type ll = list_new();\
    for (size_t i = 0; i < len; i++) {list_push_tail(ll, arr[i]);}\
    ll;\
})


#define list_push_head(ll, val) ({\
    bool return_flag = true;\
    __typeof__(ll.head) node = LL_ALLOC(__typeof__(ll.head));\
    if(!node){\
        return_flag = false;\
    } \
    else\
    {\
        node->element = val;\
        if(!ll.head){\
            ll.head = ll.tail = node;\
            ll.len += 1;\
        }\
        else\
        {\
            node->next = ll.head;\
            ll.head->prev = node; \
            ll.head = node;\
            ll.len += 1;\
        }\
    }\
    return_flag;\
})

#define list_push_tail(ll, val) ({\
    bool return_flag = true;\
    __typeof__(ll.head) node = LL_ALLOC(__typeof__(ll.head));\
    if(!node){\
        return_flag = false;\
    } \
    else\
    {\
        node->element = val;\
        if(!ll.tail){\
            ll.tail = ll.head = node;\
        }\
        else\
        {\
            node->prev = ll.tail;\
            ll.tail->next = node;\
            ll.tail = node;\
        }\
        ll.len += 1;\
    }\
    return_flag;\
})



#define list_pop_front() todo
#define list_pop_back() todo

#define list_insert() todo
#define list_len() todo

#define list_remove_nth() todo
#define list_() todo

#define list_free() todo


#ifdef __STRING_DEFINE__

#define list_to_string(ll, fmt)({\
    String str = string_new();\
    __typeof__(ll.head) node = ll.head;\
    char buffer[16];\
    string_push_cstr(&str, "[ ");\
    while (node)\
    {\
        snprintf(\
            buffer, \
            sizeof(buffer), \
            node->next? fmt", ": fmt" ", \
            node->element\
        );\
        string_push_cstr(&str, buffer);\
        node = node->next;\
    }\
    string_push_cstr(&str, "]");\
    str;\
})

#endif

#endif


