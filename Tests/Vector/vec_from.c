#include "../ColorFormat.h"
#include <assert.h>
#include <stdint.h>

typedef uint32_t U32;
#define T U32
#include "vector/vector.h"


int main(int argc, char const *argv[])
{
    U32 arr[] = {2,6,3,5};
    Vector_U32 vec = vector_from(U32, {5,3,6,2});
    printf(CYAN "New Vec Created \n");
    
    vector_print(vec, "%d");

    for (size_t i = 0; !vector_is_empty(vec); i++){
        assert(vector_pop(vec)  == arr[i]);
    }
    
    
    

   
    return 0;
}
