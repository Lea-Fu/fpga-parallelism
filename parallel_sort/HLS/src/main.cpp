#include <cstdio>
#include "sort.hpp"
#include "sort2.hpp"
#include <cstdlib>
#include <algorithm>
#include <array>
#include <sys/time.h>
#include <chrono>
#include <iostream>

int sort1_test() {
    //clock_t t1 = clock();
    using namespace std::literals;
    const std::chrono::time_point<std::chrono::steady_clock> start =
            std::chrono::steady_clock::now();

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
                printf("for debugging: %d, %d, %d", i, res[i+1], c[i+1]); //for debugging
                return -1;
            }
        }
    }
    //printing if it is correct
    printf("First sorting algo: everything is correct!\n");

    printf("total time taken by CPU:\n");
    //clock_t t2 = clock();
    const auto end = std::chrono::steady_clock::now();
    //long millisec = (t2 - t1) * (1000.0 / CLOCKS_PER_SEC);
    //printf("Elapsed time: %lf milliseconds\n",
    //       (((t2 - t1) * 1.0e3) + ((t2 - t1) / 1.0e6)));
    //printf("time needed: %d milliseconds\n",millisec);
    std::cout
            << "Calculations took: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "µs = "
            << (end - start) / 1ms << "ms = "
            << (end - start) / 1s << "s.\n";

    return 0;
}

int sort2_test() {

    using namespace std::literals;
    const std::chrono::time_point<std::chrono::steady_clock> start =
            std::chrono::steady_clock::now();

    //create an arr_t (own type implemented in sort_types.h) and a standard array
    arr_t<2> memory[16];
    std::array<int, 32> c;
    //filling the arrays with random numbers between 0 and 99
    for (int i = 0; i < 100; i++) {
        for (int i = 0; i < 16; i++) {
            memory[i][0] = rand() % 100;
            memory[i][1] = rand() % 100;
            c[i*2] = memory[i][0];
            c[i*2+1] = memory[i][1];
        }

        //sort them with the standard sort for checking if our own sort is working right
        std::sort(c.begin(),c.end());
        //sorting with our self-made sort algorithm
        sort2<2, 32>(memory);

        //printing if something is incorrect
        for(int i = 0; i < 16; i++){
            if(c[i*2] != memory[i][0]){
                printf("for debugging: %d, %d, %d", i, memory[i][0], c[i*2]); //for debugging
                return -1;
            }
            if(c[i*2+1] != memory[i][1]){
                printf("for debugging: %d, %d, %d", i, memory[i][1], c[i*2+1]); //for debugging
                return -1;
            }
        }
    }
    //printing if it is correct
    printf("Second sorting algo: everything is correct!\n");

    printf("total time taken by CPU:\n");
    const auto end = std::chrono::steady_clock::now();
    std::cout
            << "Calculations took: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "µs = "
            << (end - start) / 1ms << "ms = "
            << (end - start) / 1s << "s.\n";

    return 0;
}

/**
 * this is the main for testing if the sort algorithm is sorting the elements right
 * @return if every element is sorted correctly
 */
int main(void) {

    int result = sort1_test();
    if (result) {
        return result;
    }

    result = sort2_test();
    if (result) {
        return result;
    }

    return 0;
}
