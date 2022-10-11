#include "sort.hpp"


//this is needed because of the hardware synthesis, that needs a defined top level function without a template
void top_level_sort(int* memory){
#pragma HLS interface s_axilite port=return bundle=CONTROL //needed for control signals in axilite port
#pragma HLS interface m_axi port=memory //axi master port to main memory

    arr_t<SORT_SIZE> a;
    arr_t<SORT_SIZE> result;

    //take what we want to sort from the memory and put it into a
    for (int i = 0; i < SORT_SIZE; i++) {
        a[i] = memory[i];
    }

    //sort every element correctly
    result = sort(a);

    //take the sorted elements and put them back into the memory
    for (int i = 0; i < SORT_SIZE; i++) {
        memory[i] = result[i];
    }
}
