#include <stdint.h>
#include <stdio.h>

#include "String/String.h"
#include "Linkedlist/Linkedlist.h"

#define U32 uint32_t
INIT_LINKEDLIST_TYPE(U32)

#define CSTR char*
INIT_LINKEDLIST_TYPE(CSTR)

int main(int argc, char const *argv[])
{
    LinkedlistU32 ll = list_from(U32, {4,23,66,23,76,12});
    LinkedlistCSTR llc = list_from(CSTR, {"James", "Mike", "Wowaski"});
    
    String str = list_to_string(ll, "%d");
    {
        struct StringFormat fmt = string_format(&str);
        printf("%.*s\n", fmt.spacing, fmt.ref);
    }

    String str2 = list_to_string(llc, "\"%s\"");
    {
        struct StringFormat fmt = string_format(&str2);
        printf("%.*s\n", fmt.spacing, fmt.ref);
    }

    
    
    string_free(str);
    return 0;
}
