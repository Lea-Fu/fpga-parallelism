#ifndef SORT_TYPE_HPP
#define  SORT_TYPE_HPP


/**
 * this is a templated struct that defines an own type (arr_t) for the sorting elements.
 * the own type is needed, because of the hardware synthesis. in there are no pointers allowed and
 * normal arrays are  just pointing on the elements in the memory.
 * @tparam size the size of the array
 */
template <int size>
struct arr_t {
#if defined __has_include
#  if __has_include (<omp.h>)
#    include <omp.h>
    int a[size*16]; // pad every element (4 byte) with 60 additional bytes to prevent cache thrashing with openMP

    // Overloading [] operator to access elements in array style
    int& operator[](int i){
        return a[i*16+(i%2)]; // to just access the real elements which are padded, so we need
        // 0 = 0, 1 = 16, 2 = 32 ...
    }

#else // if we do not work with openMP
    int a[size];

    // Overloading [] operator to access elements in array style
    int& operator[](int i){
        return a[i];
    }
#  endif
#else // if has_include is not available
    int a[size];

    // Overloading [] operator to access elements in array style
    int& operator[](int i){
        return a[i];
    }
#endif

};

#endif
