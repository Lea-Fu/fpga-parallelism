#ifndef SORT_TYPE_HPP
#define  SORT_TYPE_HPP

#include <vector>

using namespace std;


template <int size>
struct arr_t {
    int a[size];

    // Overloading [] operator to access elements in array style
    int& operator[](int i){
        return a[i];
    }
};

#endif
