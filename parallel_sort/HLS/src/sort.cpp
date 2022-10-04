#include "sort.hpp"


//this is needed because of the hardware synthesis, that needs a defined top level function without a template
arr_t<SORT_SIZE> top_level_sort(arr_t<SORT_SIZE> a){

    return sort<SORT_SIZE>(a);
}