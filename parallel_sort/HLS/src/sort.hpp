#ifndef SORT_HPP
#define  SORT_HPP

#include "sort_types.hpp"
#include <vector>

using namespace std;


//   size    | FF      | LUT
// Zynq 7020 | 106.400 | 53.200
// 6         | 580     | 1.091
// 16        | 4.105    | 9.319

#define SORT_SIZE 16
arr_t<SORT_SIZE> top_level_sort(arr_t<SORT_SIZE> a);

//because this function needs a template, it can't be in the cpp file
template <int size>
arr_t<size> sort(arr_t<size> a){

    int tmp[2];
    for (int j = 0; j < size/2 ; j++) {
#pragma HLS PIPELINE
        for (int i = 0; i < size - 1; i+=2) {
#pragma HLS UNROLL
            if (a[i] > a[i + 1]) {
                tmp[0] = a[i + 1];
                tmp[1] = a[i];
                a[i] = tmp[0];
                a[i + 1] = tmp[1];
            }
        }
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
#pragma HLS PIPELINE
    for (int i = 0; i < size - 1; i+=2) {
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
