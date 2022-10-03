#include <stdio.h>
#include "sort.h"

int main(void) {

	int* res = sort(6,4);
	sort_t in;
	in.sort_data[0] = 32;
	in.sort_data[1] = 6;
	in.sort_data[2] = 5;
	in.sort_data[3] = 10;
	in.sort_data[4] = 50;
	in.sort_data[5] = 13;
	sort_t res2 = multi_sort(40,6,3,1,2,97);
	sort_t res3 = all_sort(in);

	printf("%d,", res[0]);
	printf("%d\n", res[1]);

	printf("%d,", res2.sort_data[0]);
	printf("%d,", res2.sort_data[1]);
	printf("%d,", res2.sort_data[2]);
	printf("%d,", res2.sort_data[3]);
	printf("%d,", res2.sort_data[4]);
	printf("%d\n", res2.sort_data[5]);

	printf("%d,", res3.sort_data[0]);
	printf("%d,", res3.sort_data[1]);
	printf("%d,", res3.sort_data[2]);
	printf("%d,", res3.sort_data[3]);
	printf("%d,", res3.sort_data[4]);
	printf("%d\n", res3.sort_data[5]);
}
