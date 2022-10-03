#ifndef SORT_H
#define  SORT_H

#include "sort_types.h"

/**
 * this is the header for the sort algorithms.
 *
 * first there are sort and multi_sort that are used for fix sized elements and
 * all_sort is used for variable sized elements.
 */

int* sort(int a, int b);
sort_t multi_sort(int a, int b, int c, int d, int e, int f);
sort_t all_sort(sort_t a);

#endif
