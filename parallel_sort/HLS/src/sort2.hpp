#ifndef SORT2_HPP
#define  SORT2_HPP

#if defined __has_include
#  if __has_include (<omp.h>)
#    include <omp.h>
#  endif
#endif
#include <cstdio>
#include "sort_types.hpp"
#include <limits.h>
#include <assert.h>

//bitonic mergesort

//   size    | FF      | LUT
// Zynq 7020 | 106.400 | 53.200
// 6         |         |
// 16        |         |
// 32        |  2.783  | 4.473

//needed because we need the log2 at compile time
constexpr size_t log2 (size_t val) {
    if (val == 0) return UINT_MAX;
    if (val == 1) return 0;
    unsigned int res = 0;
    while (val > 1) {
        val >>= 1;
        res++;
    }
    return res;
}

#define MEM_BUS_SIZE 2
#define SORT_SIZE 32
void top_level_sort2(arr_t<MEM_BUS_SIZE>* memory); //used for the hardware synthesis/ component

/**
 * function to merge the left and right part
 * @tparam MemBusSize size of the memory bus
 * @tparam SortSize size of the array to sort
 * @param sortLevels all levels of the pyramid
 * @param readyLeft true, when left side is ready
 * @param readyRight true, when right side is ready
 * @param level level that we are in (at the pyramid) to sort
 */
template <int MemBusSize,int SortSize>
arr_t<SortSize> merge(arr_t<MemBusSize> input) {
#pragma HLS PIPELINE

    //half pyramid (plus one level for the end result)
    static int sortLevels[SortSize][log2(SortSize) + 1] = {};
#pragma HLS RESET VARIABLE=sortLevels

    //readyFlag
    static bool readyLeft[log2(SortSize) + 1] = {false};
    static bool readyRight[log2(SortSize) + 1] = {false};
#pragma HLS RESET VARIABLE=readyLeft
#pragma HLS RESET VARIABLE=readyRight

    arr_t<SortSize> sorted;

    sortLevels[0][0] = input[0]; //left
    readyLeft[0] = true;
    sortLevels[1][0] = input[1]; //right
    readyRight[0] = true;

    for (int level = 0; level < log2(SortSize); level++) {
#pragma HLS PIPELINE

        const int mergeSize = 1 << level; //pow(2, level);

        if (readyLeft[level] && readyRight[level]) {

            int dest = 0;

            //check if we have to write into left or right
            if (readyLeft[level + 1]) {
                dest += mergeSize * 2;
                readyRight[level + 1] = true;
            } else {
                readyLeft[level + 1] = true;
            }


            int tmpBitonic1[SortSize];
            int tmpBitonic2[SortSize];

            for (int i = 0; i < mergeSize; i++) {
    #pragma HLS UNROLL
                if (sortLevels[i][level] < sortLevels[mergeSize * 2 - i - 1][level]) {
                    tmpBitonic2[i] = sortLevels[i][level];
                    tmpBitonic2[mergeSize * 2 - i - 1] = sortLevels[mergeSize * 2 - i - 1][level];
                } else {
                    tmpBitonic2[i] = sortLevels[mergeSize * 2 - i - 1][level];
                    tmpBitonic2[mergeSize * 2 - i - 1] = sortLevels[i][level];
                }
            }

            for (int i = 0, d = mergeSize / 2, n = mergeSize; i < level; i++, n /= 2, d /= 2) {
                for (int m = 0; m < mergeSize * 2; m++) {
    #pragma HLS UNROLL
                    tmpBitonic1[m] = tmpBitonic2[m];
                }

                for (int j = 0, o = 0; j < 2 << i; j++, o += n) {
    #pragma HLS UNROLL
                    for (int k = d, l = 0; k > 0; k--, l++) {
    #pragma HLS UNROLL
                        if (tmpBitonic1[o + l] < tmpBitonic1[o + l + d]) {
                            tmpBitonic2[o + l] = tmpBitonic1[o + l];
                            tmpBitonic2[o + l + d] = tmpBitonic1[o + l + d];
                        } else {
                            tmpBitonic2[o + l] = tmpBitonic1[o + l + d];
                            tmpBitonic2[o + l + d] = tmpBitonic1[o + l];
                        }
                    }
                }
            }

            for (int i = 0; i < mergeSize * 2; i++) {
    #pragma HLS UNROLL
                sortLevels[dest + i][level + 1] = tmpBitonic2[i];
            }

            readyLeft[level] = false;
            readyRight[level] = false;

        }
    }

    for (int i = 0; i < SortSize; i++) {
        sorted[i] = sortLevels[i][log2(SortSize)];
    }

    readyLeft[log2(SortSize)] = false; //reset
    return sorted;
}



//because this function needs a template, it can't be in the cpp file
/**
 * self-made second sorting algorithm that sorts in a merge sort fashion
 *
 * #pragma HLS is needed for the hardware synthesis (so later on FPGA),
 * #pragma omp is needed for paralleling with OpenMP (so later for CPU and Raspberry Pi) TODO
 *
 * @tparam MemBusSize size of the memory bus
 * @tparam SortSize size of the array to sort
 * @param a the input array
 */
template <int MemBusSize,int SortSize>
void sort2(arr_t<MemBusSize> *a) {
#pragma HLS DATAFLOW

    arr_t<SortSize> sorted;
#pragma HLS ARRAY_PARTITION variable=sorted complete dim=1
    //store each element in merge function
    for (int i = 0; i < SortSize/2; i++) {
//#pragma HLS PIPELINE OFF
        arr_t<MemBusSize> input = a[i];
        sorted = merge<MemBusSize, SortSize>(input);
    }

    //write sorted result back into the memory
    for (int i = 0; i < SortSize/2; i++) {
#pragma HLS PIPELINE OFF
        a[i][0] = sorted[i*2];//[log2(SortSize)];
        a[i][1] = sorted[i*2+1]; //[log2(SortSize)];
    }
}


#endif
