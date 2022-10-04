#include <cstdio>
#include "sort.hpp"
#include <cstdlib>
#include <algorithm>


int main(void) {

    arr_t<16> b;
    std::array<int, 16> c;
    for (int i = 0; i < 100; i++) {
        for (int i = 0; i < 16; i++) {
            b[i] = rand() % 100;
            c[i] = b[i];
        }
        std::sort(c.begin(),c.end());
        arr_t<16> res = sort(b);

        for(int i = 0; i < 16; i++){
            if(c[i] != res[i]){
                printf("%d, %d, %d", i, res[i+1], c[i+1]); //for debugging
                return -1;
            }
        }
    }
    printf("everything is correct");
}
