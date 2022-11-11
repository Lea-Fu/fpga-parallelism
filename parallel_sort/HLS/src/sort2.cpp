#include "sort2.hpp"


//this is needed because of the hardware synthesis, that needs a defined top level function without a template
void top_level_sort2(arr_t<MEM_BUS_SIZE>* memory){
#pragma HLS interface s_axilite port=return bundle=CONTROL //needed for control signals in axilite port
#pragma HLS interface m_axi port=memory //axi master port to main memory

    sort2<MEM_BUS_SIZE, SORT_SIZE>(memory);
}
