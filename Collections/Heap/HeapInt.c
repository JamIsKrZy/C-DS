#include "HeapInt.h"
#include <stdio.h>
#include <stddef.h>

#define self Heap *heap


/**
 * Notes, as the element is being swapped upward,
 * the other swapped value has to heaapify downward
 */



Heap heap_new(struct HeapTrait traits){
    Heap heap = {
        .triats = traits,
        .vec = vector_i32_new(),
    };
    if(!(heap.vec.alloc)){
        perror("Allocation error!");
 	exit(EXIT_FAILURE);
    } 
    return heap;
}

static bool index_is_within_bounds(Vector_i32 *vec, size_t index){
    return index < vec->length;
}



// if swapping exist, return true
// used for push helper
// this do not validate the siblings
static size_t heapify_up(
    Vector_i32 *vec, 
    bool (*compare_value)(const int val1, const int val2)
){
    size_t index = vec->length-1;
    while (index)
    {
        size_t parent = (index -1 ) /2;

        if(compare_value(vector_i32_get(vec, index), vector_i32_get(vec, parent))){
            vector_i32_swap(vec, index, parent);
            index = parent;
        } else {
            break;
        }

    }
    return index;
}

// if swapping exist, return true
//from the starting index until the leaf
// use for pop
static void heapify_down(
    Vector_i32 *vec, 
    size_t parent,
    bool (*compare_value)(const int val1, const int val2)
){  
    while (true) {
        size_t left_child = 2 * parent + 1;
        size_t right_child = 2 * parent + 2;
        size_t swap_child = parent;

        if (index_is_within_bounds(vec, left_child) &&
            compare_value(vector_i32_get(vec, left_child), vector_i32_get(vec, swap_child))) {
            swap_child = left_child;
        }

        if (index_is_within_bounds(vec, right_child) &&
            compare_value(vector_i32_get(vec, right_child), vector_i32_get(vec, swap_child))) {
            swap_child = right_child;
        }

        if (swap_child == parent) {
            break;  // Heap property is satisfied
        }

        vector_i32_swap(vec, parent, swap_child);
        parent = swap_child;
    }
}


static void compare_with_parent(
    Vector_i32 *vec, 
    size_t child, 
    bool (*compare)(const int val1, const int val2) 
){
    size_t parent = (child - 1) /2;
    
    if(compare(vector_i32_get(vec, child), vector_i32_get(vec, parent))){
        vector_i32_swap(vec, parent, child);
    }
}

static size_t heapify_sub_tree(
    Vector_i32 *vec,
    size_t left_child,
    size_t right_child,
    bool (*compare)(const int val1, const int val2)
){
    size_t parent = (right_child - 1) /2;
    size_t to_swap;
    
    if(compare(vector_i32_get(vec, left_child),vector_i32_get(vec, right_child))){
        to_swap = left_child;
    } else {
        to_swap = right_child;
    }
    
    if(compare(vector_i32_get(vec, to_swap),vector_i32_get(vec, parent))){
        vector_i32_swap(vec, parent, to_swap);
        return to_swap;
    }

    return 0;
}


Heap heap_build_from_vec(Vector_i32 vec, struct HeapTrait traits){
    if(vec.alloc == NULL){
        perror("Unallocated Vector!");
        exit(EXIT_FAILURE);
    }
    
    Heap heap = {
        .vec = vec,
        .triats = traits
    };

    size_t len = vec.length-1; 
    if(len % 2 == 1){
        compare_with_parent(&vec, len, traits.compare_value);
        len--;
    }
    
    int catch;
    while(len) {
        if((catch = heapify_sub_tree(&vec, len-1, len, traits.compare_value))){
            heapify_down(&vec, catch, traits.compare_value);
        }
        len -=2;
    }
    
    return heap;
    
}

bool heap_push(self, const int val){
    if(!heap) return false;

    //push on the end of the list then heap up
    vector_i32_push(&heap->vec, val);
    heapify_up(&heap->vec, heap->triats.compare_value);
    return true;
}

bool heap_pop(self, int *return_value){
    if(!heap) return false;

    bool signal = vector_i32_swap_remove(&heap->vec, 0, return_value);

    if(signal){
        heapify_down(&heap->vec, 0,heap->triats.compare_value);
        return true;
    }
    return false;
}

bool heap_peek(self, int *return_val){
    if(heap->vec.length == 0){
        return_val = 0;
        return false;  
    } 

    int temp = vector_i32_get(&heap->vec, 0);
    memcpy(return_val, &temp, sizeof(int));
    return true;
}


void print_heap(self){
    size_t len = heap->vec.length;
    printf("[ ");
    for (size_t i = 0; i < len; i++)
    {
        heap->triats.display_value(vector_i32_get(&heap->vec, i));
    }
    printf(" ]\n");
}

