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

|       | Raspberry Pi 4 |                      |                   | CPU i5                     | num_threads(2)             |                            | CPU Ryzen 5 | num_threads(6)       |                   | FPGA        |                   | GPU         |
|-------|----------------|----------------------|-------------------|----------------------------|----------------------------|----------------------------|-------------|----------------------|-------------------|-------------|-------------------|-------------|
|       | bubble sort    | bubble sort parallel | bitonic mergesort | bubble sort                | bubble sort parallel       | bitonic mergesort          | bubble sort | bubble sort parallel | bitonic mergesort | bubble sort | bitonic mergesort | bubble sort |
| 16    |                |                      |                   | 5us                        | 471us                      | 6us                        |             |                      |                   |             |                   |             |
| 32    |                |                      |                   | 17us                       | 830us                      | 16us                       |             |                      |                   |             |                   |             |
| 64    |                |                      |                   | 48us                       | 1707us                     | 36us                       |             |                      |                   | -           |                   |             |
| 128   |                |                      |                   | 191us                      | 4037us                     | 127us                      |             |                      |                   | -           |                   |             |
| 256   |                |                      |                   | 731us                      | 7418us                     | 374us                      |             |                      |                   | -           | -                 |             |
| 512   |                |                      |                   | 3162us                     | 16128us                    | 1831us                     |             |                      |                   | -           | -                 |             |
| 1024  |                |                      |                   | 11960us                    | 32570us                    | 7224us                     |             |                      |                   | -           | -                 |             |
| 2048  |                |                      |                   | 38839us                    | 71582us                    | 24942us                    |             |                      |                   | -           | -                 |             |
| 4096  |                |                      |                   | 139383us                   | 184737us                   | 114255us                   |             |                      |                   | -           | -                 |             |
| 8192  |                |                      |                   | 483319us                   | 509015us                   | 455356us                   |             |                      |                   | -           | -                 |             |
| 16384 |                |                      |                   | 1971529us = 1971ms         | 1722637us = 1722ms         | 1927274us = 1927ms         |             |                      |                   | -           | -                 |             |
| 32768 |                |                      |                   | 7751014us= 7751ms= 7s      | 6775991us = 6775ms = 6s    | 10447404us = 10447ms = 10s |             |                      |                   | -           | -                 |             |
| 65536 |                |                      |                   | 42765607us = 42765ms = 42s | 27942849us = 27942ms = 27s | 51926602us = 51926ms = 51s |             |                      |                   | -           | -                 |             |
