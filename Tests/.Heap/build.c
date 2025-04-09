#include "Heap/HeapInt.h"
#include <assert.h>

bool display_int_sample(const int val){
    printf("%d, ", val);
}

bool compare_int(const int val1, const int val2){
    return val1 > val2;
}

int main(int argc, char const *argv[])
{
    struct HeapTrait trait = {
        .compare_value = compare_int,
        .display_value = display_int_sample
    };


    int arr[] = {23,54,27,53,37,34};
    size_t len = sizeof(arr)/sizeof(arr[0]);

    Vector_i32 vec = vector_i32_new();
    for (size_t i = 0; i < len; i++)
    {
        vector_i32_push(&vec, arr[i]);
    }

    vector_i32_display(&vec, display_int);

    Heap heap = heap_build_from_vec(vec, trait);
    
    print_heap(&heap);

    int catch;
    heap_pop(&heap, &catch);
    assert(catch == 54);
    print_heap(&heap);

    heap_pop(&heap, &catch);
    assert(catch == 53);
    print_heap(&heap);

    heap_pop(&heap, &catch);
    assert(catch == 37);
    print_heap(&heap);

    

    return 0;
}
