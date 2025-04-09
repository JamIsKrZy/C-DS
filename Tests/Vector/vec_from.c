#include "../ColorFormat.h"
#include <assert.h>


#define VEC_U32_TYPE
#include "Vector/Vector.h"


int main(int argc, char const *argv[])
{
    int arr[] = {2,6,3,5};
    VectorU32 vec = vector_from(U32, {5,3,6,2});
    printf(CYAN "New Vec Created \n");
    
    vector_print(vec, "%d");

    for (size_t i = 0; !vector_is_empty(vec); i++){
        assert(vector_pop(vec)  == arr[i]);
    }
    
    
    

   
    return 0;
}
