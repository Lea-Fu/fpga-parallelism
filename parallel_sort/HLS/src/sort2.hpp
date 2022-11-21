#ifndef SORT2_HPP
#define  SORT2_HPP

#if defined __has_include
#  if __has_include (<omp.h>)
#    include <omp.h>
#  endif
#endif
#include <cstdio>
#include "sort_types.hpp"


//   size    | FF      | LUT
// Zynq 7020 | 106.400 | 53.200
// 6         |         |
// 16        |         |
// 32        |         |

//needed because we need the log2 at compile time
constexpr  size_t log2(size_t n) {
    return ((n<2)?0: 1+log2(n/2));
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
void merge(int sortLevels[SortSize][log2(SortSize)+1], bool readyLeft[log2(SortSize)+1], bool readyRight[log2(SortSize)+1], int level){
    if (readyLeft[level] && readyRight[level]) {
        int mergeSize = 1<<level; //pow(2, level);

        int left = 0;
        int right = mergeSize;
        int dest = 0;
        //check if we have to write into left or right
        if (readyLeft[level+1]) {
            dest += mergeSize*2;
            readyRight[level+1] = true;
        } else {
            readyLeft[level+1] = true;
        }
        while (left < mergeSize && right < mergeSize*2) {
#pragma HLS UNROLL
            if (sortLevels[left][level] <= sortLevels[right][level]) {
                sortLevels[dest++][level+1] = sortLevels[left][level];
                left++;
            } else {
                sortLevels[dest++][level+1] = sortLevels[right][level];
                right++;
            }
        }
        while (left+mergeSize > right) {
            sortLevels[dest++][level+1] = sortLevels[right++][level];
        }
        while (left+mergeSize < right) {
            sortLevels[dest++][level+1] = sortLevels[left++][level];
        }
        readyLeft[level] = false;
        readyRight[level] = false;
    }
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
void sort2(arr_t<MemBusSize> *a){

    //half pyramid (plus one level for the end result)
    int sortLevels[SortSize][log2(SortSize)+1] = {};

    //readyFlag
    bool readyLeft[log2(SortSize)+1] = {false};
    bool readyRight[log2(SortSize)+1] = {false};

    //top to bottom
    for (int i = 0; i < SortSize/2 ; i++) {
        //get input from MemBus
        arr_t<MemBusSize> input = a[i];

        sortLevels[0][0] = input[0]; //left
        readyLeft[0] = true;
        sortLevels[1][0] = input[1]; //right
        readyRight[0] = true;

        //merge
        for (int k = 0; k < log2(SortSize); k++) {
#pragma HLS PIPELINE
            merge<MemBusSize,SortSize>(sortLevels, readyLeft, readyRight, k);
        }
    }

    //write sorted result back into the memory
    for (int i = 0; i < SORT_SIZE/2; i++) {
        a[i][0] = sortLevels[i*2][log2(SortSize)];
        a[i][1] = sortLevels[i*2+1][log2(SortSize)];
    }
}


#endif
