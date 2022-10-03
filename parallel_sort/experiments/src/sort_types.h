#ifndef SORT_TYPE_H
#define  SORT_TYPE_H

#define SORT_SIZE 6 //16

/**
 * this is a header for selfmade type definitions.
 *
 * with this it is later easier to change the size of the array so that you can decide how many
 * elements you want to sort.
 *
 * in hardware we don't want to have a pointer, we want the real element, because we need real in- and outputs
 * to work with.
 * without this we can't parallelize the elements.
 * if we would use a pointer it would get translated to a memory interface,
 * which could only transfer one element at a time. (https://docs.xilinx.com/r/en-US/ug1399-vitis-hls/Pointers)
 */

typedef struct { //now it is no pointer, without the struct the array is just a pointer
	int sort_data[SORT_SIZE];
} sort_t;

#endif
