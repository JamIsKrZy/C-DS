#ifndef LINKEDLIST_H_METHODS_
#define LINKEDLIST_H_METHODS_


#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>


#define panic(msg, ...) do { \
    fprintf(stderr, "PANIC: at %s:%d: " msg "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
    abort(); \
} while (0)

#ifndef todo
    #define todo ({\
        fprintf(stderr, "Unimplemented! at %s:%d: \n", __FILE__, __LINE__); \
        abort();\
    })
#endif



// [Deprecated]
// #define INIT_LINKEDLIST_TYPE(type)\
// struct ll_node_##type {\
//     struct ll_node_##type *next;\
//     struct ll_node_##type *prev; \
//     type element;\
// };\
// typedef struct {\
//     struct ll_node_##type *head;\
//     struct ll_node_##type *tail;\
//     size_t len;\
// } LinkedList_##type;

#define LL_ALLOC(type) calloc(1, sizeof(type))
#define LL_FREE(ptr) free(ptr)

#define list_new() {\
    .head = NULL,\
    .tail = NULL,\
    .len = 0,\
}


#define list_from(type,...) ({\
    type arr[] = __VA_ARGS__;\
    size_t len = sizeof(arr)/sizeof(arr[0]);\
    LinkedList_##type ll = list_new();\
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



#define list_pop_front(ll, return_value)({\
    bool return_flag = true;\
    if(!ll.head){\
        return_flag = false;\
    }\
    else\
    {\
        __typeof__(ll.head) node = ll.head;\
        if(node){\
            return_value = node->element;\
            if(ll.head = node->next)\
                ll.head->prev = NULL;\
\
            LL_FREE(node);  \
            ll.len -= 1;\
        }\
        else\
        {\
            return_flag = false;\
        }\
    }\
    return_flag;\
})

#define list_pop_back(ll, return_value) ({\
    bool return_flag = true;\
    if(!ll.tail){\
        return_flag = false;\
    }\
    else \
    {\
        __typeof__(ll.head) node = ll.tail;\
        if(node){\
            return_value = node->element;\
            if (ll.tail = node->prev)\
                ll.tail->next = NULL;\
            LL_FREE(node);\
            ll.len -= 1;\
        }\
        else\
        {\
            return_flag = false;\
        }\
    }\
    return_flag;\
})

#define list_insert(ll, value, index) ({}) 

#define list_len(ll) (ll->len)

#define list_remove_nth() do{\
}while(0)

#define list_is_empty(ll) (ll.len? false: true)

#define list_get_ref(ll, index) ({\
    __typeof__(ll->head) node = ll.head;\
    for (\
        __typeof__(index) __i__ = index; \
        i > 0; \
        __i__++\
    ){\
        if(node){\
            node = node->next;\
        }\
        else\
        {\
            panic("Linkedlist Out of Bounds!");\
        }\
    }    \
    node\
})

/**
 * Creates a copy of the value
 */
#define list_get(ll, index) ({\
})

#define list_free() do{\
} while(0)


#ifdef __STRING_DEFINE_FLAG__ 

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






#ifdef T

// Helper macros for name pasting
#define _LL_JOIN(a, b) a##b
#define LL_JOIN(a, b) _LL_JOIN(a, b)

// Helper macro to sanitize type names for pointers
#ifdef T_NAME
    #define LL_TYPE_NAME T_NAME
#else
    // Default to raw T if no custom name is given
    #define LL_TYPE_NAME T
#endif

#define LL_STRUCT_NAME(name) LL_JOIN(name, LL_TYPE_NAME)

// Define the node struct
struct LL_STRUCT_NAME(ll_node_) {
    struct LL_STRUCT_NAME(ll_node_) *next;
    struct LL_STRUCT_NAME(ll_node_) *prev;
    T element;
};

// Define the linked list struct
typedef struct {
    struct LL_STRUCT_NAME(ll_node_) *head;
    struct LL_STRUCT_NAME(ll_node_) *tail;
    size_t len;
} LL_STRUCT_NAME(LinkedList_);

// Cleanup after including
#undef _LL_JOIN
#undef LL_JOIN
#undef LL_STRUCT_NAME
#undef LL_TYPE_NAME
#ifdef T_NAME
    #undef T_NAME
#endif
#undef T

#endif // T


