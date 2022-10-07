#ifndef SORT_HPP
#define  SORT_HPP

#include <omp.h>
#include "sort_types.hpp"
#include <vector>


//   size    | FF      | LUT
// Zynq 7020 | 106.400 | 53.200
// 6         | 773     | 1.507
// 16        | 4.618   | 10.555
// 32        | 17.426  | 42.077

#define SORT_SIZE 6
arr_t<SORT_SIZE> top_level_sort(arr_t<SORT_SIZE> a); //used for the hardware synthesis/ component

//because this function needs a template, it can't be in the cpp file
/**
 * self-made sorting algorithm (when I say array, I mean the self-made type arr_t)
 *
 * #pragma HLS is needed for the hardware synthesis (so later on FPGA),
 * #pragma omp is needed for paralleling with OpenMP (so later for CPU and Raspberry Pi)
 *
 * @tparam size the size of the array with the elements we want to sort
 * @param a the input array
 * @return the correctly sorted array
 */
template <int size>
arr_t<size> sort(arr_t<size> a){

    int tmp[2];
    for (int j = 0; j < size/2 ; j++) {
#pragma HLS PIPELINE
        #pragma omp parallel for firstprivate(tmp)
        for (int i = 0; i < size - 1; i+=2) {
#pragma HLS UNROLL
            if (a[i] > a[i + 1]) {
                tmp[0] = a[i + 1];
                tmp[1] = a[i];
                a[i] = tmp[0];
                a[i + 1] = tmp[1];
            }
        }
#pragma HLS PIPELINE
        #pragma omp parallel for firstprivate(tmp)
        for (int i = 1; i < size - 2; i+=2) {
#pragma HLS UNROLL
            if (a[i] > a[i + 1]) {
                tmp[0] = a[i + 1];
                tmp[1] = a[i];
                a[i] = tmp[0];
                a[i + 1] = tmp[1];
            }
        }
    }
// this is not needed for the correct result, but for the correct pipelining of the hardware synthesis
#pragma HLS PIPELINE
    #pragma omp parallel for firstprivate(tmp)
    for (int i = 0; i < size - 1; i += 2) {
#pragma HLS UNROLL
        if (a[i] > a[i + 1]) {
            tmp[0] = a[i + 1];
            tmp[1] = a[i];
            a[i] = tmp[0];
            a[i + 1] = tmp[1];
        }
    }
    return a;
}

#endif
