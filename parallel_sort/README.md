Time Measurements <br>

Measured 100 times each and then divide by 100. <br>

Raspberry Pi 4 = Broadcom BCM2711, Quad core Cortex-A72 (ARM v8) 64-bit SoC @ 1.5GHz, 4 Cores <br>
CPU i5 = 2,9 GHz Dual-Core Intel Core i5 (MacBook Pro (Retina, 13", Anfang 2015)) 2 Cores <br>
CPU Ryzen 5 = AMD Ryzen 5 3600, processor, 6 Cores with 3,6 GHz clock frequency <br>
FPGA = Zynq-7020 <br>
GPU = Intel Iris Graphics 6100 1536 MB <br>

Because of the Look-Up-Table usage of the FPGA the algorithms can't sort more than the measured elements in Hardware! <br>

1 << 4  = 16 <br>
1 << 16 = 65536 <br>

FPGA: measured 64 elements with 80MHz the others with 100MHz <br>
<br>

|       | Raspberry Pi 4                | num_threads(4)                |                               | CPU i5                     | num_threads(2)             |                            | CPU Ryzen 5                | num_threads(6)          |                            | FPGA             |                   | GPU                                                                       |
|-------|-------------------------------|-------------------------------|-------------------------------|----------------------------|----------------------------|----------------------------|----------------------------|-------------------------|----------------------------|------------------|-------------------|---------------------------------------------------------------------------|
|       | bubblesort                    | bubblesort parallel           | bitonic mergesort             | bubblesort                 | bubblesort parallel        | bitonic mergesort          | bubblesort                 | bubblesort parallel     | bitonic mergesort          | bubblesort       | bitonic mergesort | bubblesort                                                                |
| 16    | 28us                          | 484us                         | 39us                          | 72us                       | 624us                      | 54us                       | 17us                       | 372us                   | 16us                       | 3151ns = 3,151us | 3891ns = 3,891us  | OpenCL execution time: 0.2451 ms Whole Calc 7718µs = 7ms                  |
| 32    | 89us                          | 504us                         | 123us                         | 74us                       | 1284us = 1ms               | 60us                       | 28us                       | 754us                   | 26us                       | 3843ns = 3,843us | 5337ns = 5,337us  | OpenCL execution time: 0.5128 ms Whole Calc 10487µs = 10ms                |
| 64    | 289us                         | 730us                         | 269us                         | 118us                      | 2325us = 2ms               | 100us                      | 40us                       | 1443us = 1ms            | 39us                       | -                | 6896ns= 6,896us   | OpenCL execution time: 1.0187 ms Whole Calc 17290µs = 17ms                |
| 128   | 730us                         | 844us                         | 618us                         | 240us                      | 4429us = 4ms               | 160us                      | 88us                       | 2805us = 2ms            | 92us                       | -                | -                 | OpenCL execution time: 2.0943 ms Whole Calc 36368µs = 36ms                |
| 256   | 2052us = 2ms                  | 1582us = 1ms                  | 1271us = 1ms                  | 1067us = 1ms               | 9375us = 9ms               | 368us                      | 281us                      | 5703us = 5ms            | 247us                      | -                | -                 | OpenCL execution time: 4.0221 ms Whole Calc 66539µs = 66ms                |
| 512   | 6639us = 6ms                  | 3385us = 3ms                  | 4823us = 4ms                  | 2266us = 2ms               | 17465us = 17ms             | 1778us = 1ms               | 1015us = 1ms               | 11649us = 11ms          | 818us                      | -                | -                 | OpenCL execution time: 8.1586 ms Whole Calc 126283µs = 126ms              |
| 1024  | 25815us = 25ms                | 9558us = 9ms                  | 17174us = 17ms                | 7210us = 7ms               | 42983us = 42ms             | 6076us = 6ms               | 3916us = 3ms               | 23642us = 23ms          | 2912us = 2ms               | -                | -                 | OpenCL execution time: 15.8241 ms Whole Calc 250888µs = 250ms             |
| 2048  | 99125us = 99ms                | 33388us = 33ms                | 61734us = 61ms                | 28207us = 28ms             | 92729us = 92ms             | 24710us = 24ms             | 15344us = 15ms             | 48513us = 48ms          | 10720us = 10ms             | -                | -                 | OpenCL execution time: 32.5062 ms Whole Calc 499768µs = 499ms             |
| 4096  | 393521us = 393ms              | 127646us = 127ms              | 335293us = 335ms              | 108477us = 108ms           | 295716us = 295ms           | 114561us = 114ms           | 65219us = 65ms             | 101845us = 101ms        | 41432us = 41ms             | -                | -                 | OpenCL execution time: 66.3929 ms Whole Calc 1011611µs = 1011ms = 1s      |
| 8192  | 1600953us = 1600ms = 1s       | 507622us = 507ms              | 1587502us = 1587ms = 1s       | 429105us = 429ms           | 591468us = 591ms           | 457957us = 457ms           | 309035us = 309ms           | 238377us = 238ms        | 274802us = 274ms           | -                | -                 | OpenCL execution time: 141.6652 ms Whole Calc 2105625µs = 2105ms = 2s     |
| 16384 | 8443902us = 8443ms = 8s       | 4020958us = 4020ms = 4s       | 14395382us = 14395ms = 14s    | 1749546us = 1749ms = 1s    | 1539134us = 1539ms = 1s    | 1886338us = 1886ms = 1s    | 1286446us = 1286ms = 1s    | 628084us = 628ms        | 1496998us = 1496ms = 1s    | -                | -                 | OpenCL execution time: 297.9275 ms Whole Calc 2782859µs = 2782ms = 2s     |
| 32768 | 37344280us = 37344ms = 37s    | 39347572us = 39347ms = 39s    | 52438889us = 52438ms = 52s    | 7055420us = 7055ms = 7s    | 4971618us = 4971ms = 4s    | 9159550us = 9159ms = 9s    | 5252279us = 5252ms = 5s    | 1821525us = 1821ms = 1s | 5058049us = 5058ms = 5s    | -                | -                 | OpenCL execution time: 734.0964 ms Whole Calc 5338790µs = 5338ms = 5s     |
| 65536 | 150145319us = 150145ms = 150s | 161154931us = 161154ms = 161s | 194528410us = 194528ms = 194s | 32416705us = 32416ms = 32s | 22319961us = 22319ms = 22s | 42702610us = 42702ms = 42s | 20765194us = 20765ms = 20s | 6374055us = 6374ms = 6s | 19688556us = 19688ms = 19s | -                | -                 | OpenCL execution time: 2069.0165 ms Whole Calc 11283997µs = 11283ms = 11s |





1 Mikrosekunde = 1000 Nanosekunden <br>
1 Millisekunde = 1000 Mikrosekunden <br>
1 Sekunde = 1000 Millisekunden <br>
ns < us < ms < s <br>
