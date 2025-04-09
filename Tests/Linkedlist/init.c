#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "string/string.h"

typedef char* CStr;
#define T CStr
#include "linkedlist/linkedlist.h"
 
typedef uint32_t U32;
#define T U32
#include "linkedlist/linkedlist.h"

#define printfy(string, fmtt){\
    String str = list_to_string(string, fmtt);\
    struct StringFormat fmt = string_format(&str);\
    printf("%.*s\n", fmt.spacing, fmt.ref);\
    string_free(str);\
}\
 

int main(int argc, char const *argv[])
{
    U32 arr[] = {55,4,23,66,23,76,12};
    char *arr_str[] =  {"James", "Mike", "Wowaski"};

    LinkedList_U32  ll = list_from(U32,{4,23,66,23,76,12});
    LinkedList_CStr llc = list_from(CStr,{"James", "Mike", "Wowaski"});

    list_push_head(ll, 55); // add 55 head of list

    // Print out
    printfy(ll, "%d");
    printfy(llc, "\"%s\"");
    
    
    // Assert
    char *catch_str;
    uint32_t catch_int;
    for(size_t i=0; !list_is_empty(ll); i++){
        list_pop_front(ll, catch_int);
        printf("[assert: %d] ", catch_int); fflush(stdout);
        assert(catch_int == arr[i]);
    }
    printf("\n");
    for(size_t i=0; !list_is_empty(llc); i++){
        list_pop_front(llc, catch_str);
        printf("[assert: %s] ", catch_str); fflush(stdout);
        assert(!strcmp(catch_str, arr_str[i]));
    }
    printf("\n");
    
    return 0;
}


