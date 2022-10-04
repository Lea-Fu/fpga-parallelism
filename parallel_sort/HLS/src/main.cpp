#include <cstdio>
#include "sort.hpp"
#include <vector>

using namespace std;


int main(void) {

	arr_t<16> a = {7, 5, 3, 16, 2, 9,4, 4, 2, 87, 45, 24, 18, 91, 245, 19};
	arr_t<16> res = sort(a);

    for(int i = 0; i < 16; i++){
        printf("%d,", res[i]);
    }

}
