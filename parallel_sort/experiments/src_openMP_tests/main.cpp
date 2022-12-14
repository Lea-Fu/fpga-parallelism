#include <iostream>
#include <chrono>
#include <omp.h>

int main() {

    using namespace std::literals;
    const auto start =
            std::chrono::steady_clock::now();

       int a[100000];
       int c[100000];
       for (int i = 0; i < 1; i++) {
           for (int j = 0; j < 100000; j++) {
               a[j] = rand() % 100;
               c[j] = a[j];
           }
       }


       int tmp[2];
       int b[100000];
       /*
   #pragma omp parallel for private(tmp), shared(a, b), default(none), num_threads(1) //#pragma omp parallel default(none) shared(a, size) private(tmp)
       for (int i = 0; i < 1000 - 1; i += 2) {
           if (a[i*16] > a[i*16 + 1]) {
               tmp[0] = a[i*16 + 1];
               tmp[1] = a[i*16];
               b[i*16] = tmp[0];
               b[i*16 + 1] = tmp[1];

           }
           //printf("%d",b[i]);
       }
*/

       int size = 40000;

        for(int i = 0; i < size-1; i++ ) {
            int first = i % 2;
    #pragma omp parallel for default(none),shared(a,first,size) num_threads(6)
    //without OpenMP: 2ms:1000 elements   328ms:16000 elements   842ms:25000 elements   1430ms:32000 elements   2306ms:40000 elements
    //with OpenMP:    23ms:1000 elements  456ms:16000 elements   793ms:25000 elements   1123ms:32000 elements   1531ms:40000 elements
            for(int j = first; j < size-1; j+=2) {
                if(a[j] > a[j+1]) {
                    int tmp = a[j];
                    a[j] = a[j+1];
                    a[j+1] = tmp;
                }
            }
        }

        /*for(int i = 0; i < size; i++) {
            std::cout << a[i] << std::endl;
        }*/

       const auto end = std::chrono::steady_clock::now();
       std::cout
               << "\nCalculations took: "
               << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "µs = "
               << (end - start) / 1ms << "ms = "
               << (end - start) / 1s << "s.\n";

       return (long long)b;
       /*

    double start;
    double end;
    start = omp_get_wtime();

    int a[16000];
    int b[16000];
    int c[16000];
    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < 16000; j++) {
            a[j] = rand() % 100;
            b[j] = a[j];
        }
    }
/*
//#pragma omp parallel for shared(a, b, c), default(none), num_threads(2)
int threads = omp_get_max_threads();
#pragma omp parallel num_threads(threads) shared(a, b, c)
    {
        int t = omp_get_thread_num();
#pragma omp for
        for (int i = 0; i < 16000/threads; ++i) {
            c[16000/threads * t + i] = a[16000/threads * t + i] + b[16000/threads * t + i];
        }
    }

    end = omp_get_wtime();
    printf("Work took %f seconds\n", end - start);

    const auto end = std::chrono::steady_clock::now();


    std::cout
            << "\nCalculations took: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "µs = "
            << (end - start) / 1ms << "ms = "
            << (end - start) / 1s << "s.\n";
    return 0;
    */
}