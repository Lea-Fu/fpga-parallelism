#include "sort.h"
#include <math.h>

/**
 * this is a small sort algorithm that can only sort two elements
 */
int* sort(int a, int b) {
	static int result[2];
	if(a > b) {
		result[0] = b;
		result[1] = a;
		return result;
	}else{
		result[0] = a;
		result[1] = b;
		return result;
	}
}


/**
 * this algorithm sorts through exactly six elements (hardcoded)
 *
 * with this approach it needs 387 FlipFlops and 1068 LookupTables
 */
sort_t multi_sort(int a, int b, int c, int d, int e, int f) {
	int tmp[2];
	sort_t result;
	#pragma HLS PIPELINE
	for(int i = 0; i < 2; i++){
		if(a > b) {
			tmp[0] = b;
			tmp[1] = a;
			a = tmp[0];
			b = tmp[1];
		}
		if(c > d) {
			tmp[0] = d;
			tmp[1] = c;
			c = tmp[0];
			d = tmp[1];
		}
		if(e > f) {
			tmp[0] = f;
			tmp[1] = e;
			e = tmp[0];
			f = tmp[1];
		}
	//pipeline this afterwards
		if(b > c) {
			tmp[0] = c;
			tmp[1] = b;
			b = tmp[0];
			c = tmp[1];
			}
		if(d > e) {
			tmp[0] = e;
			tmp[1] = d;
			d = tmp[0];
			e = tmp[1];
			}
	}
	if(a > b) {
				tmp[0] = b;
				tmp[1] = a;
				a = tmp[0];
				b = tmp[1];
			}
			if(c > d) {
				tmp[0] = d;
				tmp[1] = c;
				c = tmp[0];
				d = tmp[1];
			}
			if(e > f) {
				tmp[0] = f;
				tmp[1] = e;
				e = tmp[0];
				f = tmp[1];
			}
	result.sort_data[0] = a;
	result.sort_data[1] = b;
	result.sort_data[2] = c;
	result.sort_data[3] = d;
	result.sort_data[4] = e;
	result.sort_data[5] = f;
	return result;
}


/**
 * this algorithm can sort an arbitrary amount of elements, which size is chosen in the sort_types.h
 *
 * with pragma hls unroll, the whole loop gets executed in parallel,
 * but this only happens later in the synthesized hardware.
 * it has no impact on the software execution.
 *
 * with 16 elements as SORT_SIZE there are 251.936 FlipFlops and 561.019 LookupTables in use,
 * which is more than the Zynq 7020 has (106.400 FF and 53.200 LUT).
 *
 * with 6 elemnts there are 12.126 FF and 26.068 LUT
 *
 * with this example you can see, that you can't use this naive approach.
 */
sort_t all_sort(sort_t a) {
// #pragma HLS UNROLL //factor = pow(SORT_SIZE,2) //16*16
	sort_t result;
	for(int i = 0; i < pow(SORT_SIZE,2); i++){
	#pragma HLS UNROLL
		for(int i = 0; i < SORT_SIZE-1; i++) {
		#pragma HLS UNROLL
			if(a.sort_data[i] > a.sort_data[i+1]) {
				result.sort_data[i] = a.sort_data[i+1];
				result.sort_data[i+1] = a.sort_data[i];
				a.sort_data[i] = result.sort_data[i];
				a.sort_data[i+1] = result.sort_data[i+1];
			}
		}
	}
	return result;
}
