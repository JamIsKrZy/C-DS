#include "Vector/Vector.h"
#include "../ColorFormat.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define u32 unsigned int 
VECTOR_TYPE(u32);

int main(int argc, char const *argv[])
{
    Vector_u32 vec = vector_from(u32, {5,3,6,2});
    printf(CYAN "New Vec Created \n");

    printf(CYAN "Before: ");
    vector_print(vec, "%d");

    vector_push(vec, 1001);

    printf("After: ");
    vector_print(vec, "%d");

    printf(RESET);

    
    Vector_u32 clone_vec = vector_clone(vec);
    printf( YELLOW "\nSUCCESSFULLY CLONED\n");

    
    printf("Cloned Vec: ");
    vector_print(clone_vec, "%d");

    printf("Adding changes to clone_vec! \n");
    size_t len = vector_get_len(clone_vec);
    vector_swap(clone_vec, 0, len-1);

    printf("Cloned Vec: ");
    vector_print(clone_vec, "%d");



    printf(RESET "\nChecking both vec if not affecting one another\n");
    printf(CYAN "Orig Vec: ");
    vector_print(vec, "%d");
    printf(RESET);
    printf(YELLOW "Cloned Vec: ");
    vector_print(clone_vec, "%d");
    
   
    return 0;
}
