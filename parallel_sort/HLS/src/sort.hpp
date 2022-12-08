#ifndef SORT_HPP
#define  SORT_HPP

#if defined __has_include
#  if __has_include (<omp.h>)
#    include <omp.h>
#  endif
#endif
#include <cstdio>
#include "sort_types.hpp"

//sorting network bubblesort like

//   size    | FF      | LUT
// Zynq 7020 | 106.400 | 53.200
// 6         | 773     | 1.507
// 16        | 4.618   | 10.555
// 32        | 17.426  | 42.077

#define SORT_SIZE 32
void top_level_sort(int* memory); //used for the hardware synthesis/ component

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

    //printf("%d\n", omp_get_max_threads( ));
    //printf("%d\n", omp_get_num_procs( ));
    int tmp[2];
    for (int j = 0; j < size/2 ; j++) {
#pragma HLS PIPELINE
        //#pragma omp parallel for private(tmp),shared(a),default(none) num_threads(2)  // just comment this in, when you want to sort more than > 10000 elements (otherwise the timing is better without the use of openMP)
        for (int i = 0; i < size - 1; i+=2) {
            //printf("%d\n", omp_get_thread_num());
#pragma HLS UNROLL
            if (a[i] > a[i + 1]) {
                tmp[0] = a[i + 1];
                tmp[1] = a[i];
                a[i] = tmp[0];
                a[i + 1] = tmp[1];
            }
        }
#pragma HLS PIPELINE
        //#pragma omp parallel for default(none),shared(a),private(tmp) num_threads(2)  // just comment this in, when you want to sort more than > 10000 elements (otherwise the timing is better without the use of openMP)
        for (int i = 1; i < size - 2; i+=2) {
#pragma HLS UNROLL
            if (a[i] > a[i + 1]) {
                tmp[0] = a[i + 1];
                tmp[1] = a[i];
                a[i] = tmp[0];
                a[i + 1] = tmp[1];
            }
        }
    }/* commented out for time measurements on CPU
// this is not needed for the correct result, but for the correct pipelining of the hardware synthesis
#pragma HLS PIPELINE
    //#pragma omp parallel for default(none),shared(a),private(tmp)  num_threads(2)  // just comment this in, when you want to sort more than > 10000 elements (otherwise the timing is better without the use of openMP)
    for (int i = 0; i < size - 1; i += 2) {
#pragma HLS UNROLL
        if (a[i] > a[i + 1]) {
            tmp[0] = a[i + 1];
            tmp[1] = a[i];
            a[i] = tmp[0];
            a[i + 1] = tmp[1];
        }
    }*/
    return a;
}

#endif
