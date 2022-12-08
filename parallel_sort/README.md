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
<br>

|       | Raspberry Pi 4 |                      |                   | CPU i5                     | num_threads(2)             |                            | CPU Ryzen 5                | num_threads(6)          |                            | FPGA        |                   | GPU                                                                      |
|-------|----------------|----------------------|-------------------|----------------------------|----------------------------|----------------------------|----------------------------|-------------------------|----------------------------|-------------|-------------------|--------------------------------------------------------------------------|
|       | bubble sort    | bubble sort parallel | bitonic mergesort | bubble sort                | bubble sort parallel       | bitonic mergesort          | bubble sort                | bubble sort parallel    | bitonic mergesort          | bubble sort | bitonic mergesort | bubble sort                                                              |
| 16    |                |                      |                   | 5us                        | 471us                      | 6us                        | 19us                       | 388us                   | 16us                       |             |                   | OpenCL execution time: 0.2451 msWhole Calc 7718µs = 7ms                  |
| 32    |                |                      |                   | 17us                       | 830us                      | 16us                       | 22us                       | 795us                   | 21us                       |             |                   | OpenCL execution time: 0.5128 msWhole Calc 10487µs = 10ms                |
| 64    |                |                      |                   | 48us                       | 1707us                     | 36us                       | 42us                       | 1462us                  | 36us                       | -           |                   | OpenCL execution time: 1.0187 msWhole Calc 17290µs = 17ms                |
| 128   |                |                      |                   | 191us                      | 4037us                     | 127us                      | 116us                      | 2813us                  | 79us                       | -           |                   | OpenCL execution time: 2.0943 msWhole Calc 36368µs = 36ms                |
| 256   |                |                      |                   | 731us                      | 7418us                     | 374us                      | 300us                      | 5935us                  | 255us                      | -           | -                 | OpenCL execution time: 4.0221 msWhole Calc 66539µs = 66ms                |
| 512   |                |                      |                   | 3162us                     | 16128us                    | 1831us                     | 1285us                     | 11513us                 | 848us                      | -           | -                 | OpenCL execution time: 8.1586 msWhole Calc 126283µs = 126ms              |
| 1024  |                |                      |                   | 11960us                    | 32570us                    | 7224us                     | 3944us                     | 23650us                 | 2736us                     | -           | -                 | OpenCL execution time: 15.8241 msWhole Calc 250888µs = 250ms             |
| 2048  |                |                      |                   | 38839us                    | 71582us                    | 24942us                    | 16374us                    | 48344us                 | 11060us                    | -           | -                 | OpenCL execution time: 32.5062 msWhole Calc 499768µs = 499ms             |
| 4096  |                |                      |                   | 139383us                   | 184737us                   | 114255us                   | 63937us                    | 102211us                | 42991us                    | -           | -                 | OpenCL execution time: 66.3929 msWhole Calc 1011611µs = 1011ms = 1s      |
| 8192  |                |                      |                   | 483319us                   | 509015us                   | 455356us                   | 315240us                   | 237826us                | 271174us                   | -           | -                 | OpenCL execution time: 141.6652 msWhole Calc 2105625µs = 2105ms = 2s     |
| 16384 |                |                      |                   | 1971529us = 1971ms         | 1722637us = 1722ms         | 1927274us = 1927ms         | 1290206us = 1290ms         | 614645us = 614ms        | 1511090us = 1511ms         | -           | -                 | OpenCL execution time: 297.9275 msWhole Calc 2782859µs = 2782ms = 2s     |
| 32768 |                |                      |                   | 7751014us= 7751ms= 7s      | 6775991us = 6775ms = 6s    | 10447404us = 10447ms = 10s | 5179926us = 5179ms = 5s    | 1830286us = 1830ms = 1s | 5002547us = 5002ms = 5s    | -           | -                 | OpenCL execution time: 734.0964 msWhole Calc 5338790µs = 5338ms = 5s     |
| 65536 |                |                      |                   | 42765607us = 42765ms = 42s | 27942849us = 27942ms = 27s | 51926602us = 51926ms = 51s | 20880548us = 20880ms = 20s | 6332793us = 6332ms = 6s | 19495397us = 19495ms = 19s | -           | -                 | OpenCL execution time: 2069.0165 msWhole Calc 11283997µs = 11283ms = 11s |
