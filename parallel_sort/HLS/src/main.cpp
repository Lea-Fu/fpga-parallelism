#include <cstdio>
#include "sort.hpp"
#include <cstdlib>
#include <algorithm>

/**
 * this is the main for testing if the sort algorithm is sorting the elements right
 * @return if every element is sorted correctly
 */
int main(void) {

    //create an arr_t (own type implemented in sort_types.h) and a standard array
    arr_t<16> b;
    std::array<int, 16> c;
    //filling the arrays with random numbers between 0 and 99
    for (int i = 0; i < 100; i++) {
        for (int i = 0; i < 16; i++) {
            b[i] = rand() % 100;
            c[i] = b[i];
        }
        //sort them with the standard sort for checking if our own sort is working right
        std::sort(c.begin(),c.end());
        //sorting with our self-made sort algorithm
        arr_t<16> res = sort(b);

        //printing if something is incorrect
        for(int i = 0; i < 16; i++){
            if(c[i] != res[i]){
                printf("%d, %d, %d", i, res[i+1], c[i+1]); //for debugging
                return -1;
            }
        }
    }
    //printing if it is correct
    printf("everything is correct");
    return 0;
}
