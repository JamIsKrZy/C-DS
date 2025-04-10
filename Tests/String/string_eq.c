#include "string/string.h"
#include <assert.h>
#include <stdarg.h>

void printfy(StrSlice *slice){
    struct StringFormat fmt = strslice_format(slice);
    printf("%.*s\n", fmt.spacing, fmt.ref); fflush(stdout);
}


void print_slices(int len, ...){
    va_list list;
    va_start(list, len);
    
    for (size_t i = 0; i < len; i++){
        StrSlice *slc = va_arg(list, StrSlice*);
        printfy(slc);
    }
    
    va_end(list);
}

int main(){
    String str_1 = string_from_cstr("Make me something");
    String str_2 = string_from_cstr("Hawaiin");
    String str_3 = string_from_cstr("Hawaiin");
    
    StrSlice slc_1 = string_to_slice(&str_1);
    StrSlice slc_2 = string_to_slice(&str_2);
    StrSlice slc_3 = string_to_slice(&str_3);
    
    print_slices(3, &slc_1, &slc_2,  &slc_3);

    printf("%d\n", str_slice_eq(&slc_1,&slc_2));fflush(stdout);
    printf("%d\n", str_slice_eq(&slc_2,&slc_3));fflush(stdout);

    assert(str_slice_eq(&slc_1,&slc_2) ==  false);
    assert(str_slice_eq(&slc_2,&slc_3) ==  true);
    
}