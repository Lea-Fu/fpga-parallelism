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
    int a[size];

    // Overloading [] operator to access elements in array style
    int& operator[](int i){
        return a[i];
    }
};

/**
 * start address in the memory for configuration
 */
struct config_t{
    int start_address;
};

#endif
