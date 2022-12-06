#include <cstdio>
#include "sort.hpp"
#include "sort2.hpp"
#include <cstdlib>
#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>


#define WHOLE_SORT_SIZE 2048
#define HALF_SORT_SIZE (WHOLE_SORT_SIZE/2)


/**
 * Test for the first sorting implementation sort (a sorting network that works like bubblesort)
 * @return if every element is sorted correctly or not
 */
int sort1_test() {
    using namespace std::literals;
    const std::chrono::time_point<std::chrono::steady_clock> start =
            std::chrono::steady_clock::now();

    //create an arr_t (own type implemented in sort_types.h) and a standard array
    arr_t<WHOLE_SORT_SIZE> b;
    std::array<int, WHOLE_SORT_SIZE> c;
    //filling the arrays with random numbers between 0 and 99
    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < WHOLE_SORT_SIZE; j++) {
            b[j] = rand() % 100;
            c[j] = b[j];
        }
        //sort them with the standard sort for checking if our own sort is working right
        std::sort(c.begin(),c.end());
        //sorting with our self-made sort algorithm
        arr_t<WHOLE_SORT_SIZE> res = sort(b);

        //printing if something is incorrect
        for(int k = 0; k < WHOLE_SORT_SIZE; k++){
            if(c[k] != res[k]){
                printf("for debugging: %d, %d, %d", k, res[k + 1], c[k + 1]); //for debugging
                return -1;
            }
        }
    }
    //printing if it is correct
    printf("First sorting algo: everything is correct!\n");

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
 Test for the second sorting implementation sort2 (a bitonic mergesort)
 * @return if every element is sorted correctly or not
 */
int sort2_test() {

    using namespace std::literals;
    const std::chrono::time_point<std::chrono::steady_clock> start =
            std::chrono::steady_clock::now();

    //create an arr_t (own type implemented in sort_types.h) and a standard array
    arr_t<2> memory[HALF_SORT_SIZE];
    std::array<int, WHOLE_SORT_SIZE> c;
    //filling the arrays with random numbers between 0 and 99
    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < HALF_SORT_SIZE; j++) {
            memory[j][0] = rand() % 100;
            memory[j][1] = rand() % 100;
            c[j * 2] = memory[j][0];
            c[j * 2 + 1] = memory[j][1];
        }

        //sort them with the standard sort for checking if our own sort is working right
        std::sort(c.begin(),c.end());
        //sorting with our self-made sort algorithm
        sort2<2, WHOLE_SORT_SIZE>(memory);

        //printing if something is incorrect
        for(int k = 0; k < HALF_SORT_SIZE; k++){
            if(c[k*2] != memory[k][0]){
                printf("for debugging: %d, %d, %d, %d", i, k, memory[k][0], c[k*2]); //for debugging
                return -1;
            }
            if(c[k*2+1] != memory[k][1]){
                printf("for debugging: %d, %d, %d, %d", i, k, memory[k][1], c[k*2+1]); //for debugging
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
 * this is the main for testing if the sort algorithms are both sorting the elements right
 * @return if every element is sorted correctly
 */
int main(void) {

    //sorting network (bubblesort like)
    int result = sort1_test();
    if (result) {
        return result;
    }

    //bitonic mergesort
    result = sort2_test();
    if (result) {
        return result;
    }

    return 0;
}
