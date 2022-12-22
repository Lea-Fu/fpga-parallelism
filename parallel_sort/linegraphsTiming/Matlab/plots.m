x_fpga_bubble = [16 32];
x_fpga_merge = [16 32 64];
y_fpga_bubble = [3151 3843];
y_fpga_merge = [3891 5337 6896];
plot(x_fpga_bubble, y_fpga_bubble, 'b.-', x_fpga_merge, y_fpga_merge, 'r.-')
xticks(x_fpga_merge)
title('Zeitmessungen FPGA')
xlabel('Anzahl Elemente')
ylabel('Zeit in Nanosekunden')
legend('bubblesort','bitonic mergesort','Location','northwest')
figure;

x = [16 32 64 128 256 512 1024 2048 4096 8192 16384 32768 65536];
y_raspi_bubble = [0.028 0.089 0.289 0.730 2.052 6.639 25.815 99.125 393.521 1600.953 8443.902 37344.280 150145.319];
y_raspi__parallel_bubble = [0.484 0.504 0.730 0.844 1.582 3.385 9.558 33.388 127.646 507.622 4020.958 39347.572 161154.931];
y_raspi_merge = [0.039 0.123 0.269 0.618 1.271 4.823 17.174 61.734 335.293 1587.502 14395.382 52438.889 194528.410];
x_fpga_merge_zoom = [16 32 64 128 256 512 1024 2048 4096];
subplot(3,1,1)
plot(x, y_raspi_bubble, 'b.-', x, y_raspi__parallel_bubble, 'c.-', x, y_raspi_merge, 'r.-')
xticks(x)
ax=gca; ax.XAxis.Exponent = 0;
ax=gca; ax.YAxis.Exponent = 0;
title('Zeitmessungen Raspberry Pi 4')
xlabel('Anzahl Elemente')
ylabel('Zeit in Millisekunden')
legend('bubblesort', 'parallel bubblesort', 'bitonic mergesort','Location','northwest')
subplot(3,1,2)
plot(x, y_raspi_bubble, 'b.-', x, y_raspi__parallel_bubble, 'c.-', x, y_raspi_merge, 'r.-')
xlim([16 4096])
ylim([0.0 1000])
xticks(x_fpga_merge_zoom)
title('Zeitmessungen Raspberry Pi 4 Zoom')
subplot(3,1,3)
plot(x, y_raspi_bubble, 'b.-', x, y_raspi__parallel_bubble, 'c.-', x, y_raspi_merge, 'r.-')
xlim([16 64])
ylim([0.0 0.8])
xticks(x_fpga_merge)
title('Zeitmessungen Raspberry Pi 4 Zoom')
figure;

x = [16 32 64 128 256 512 1024 2048 4096 8192 16384 32768 65536];
y_cpui5_bubble = [0.072 0.074 0.118 0.240 1.067 2.266 7.210 28.207 108.477 429.105 1749.546 7055.420 32416.705];
y_cpui5__parallel_bubble = [0.624 1.284 2.325 4.429 9.375 17.465 42.983 92.729 295.716 591.468 1539.134 4971.618 22319.961];
y_cpui5_merge = [0.054 0.060 0.100 0.160 0.368 1.778 6.076 24.710 114.561 457.957 1886.338 9159.550 42702.610];
plot(x, y_cpui5_bubble, 'b.-', x, y_cpui5__parallel_bubble, 'c.-', x, y_cpui5_merge, 'r.-')
xticks(x)
ax=gca; ax.XAxis.Exponent = 0;
ax=gca; ax.YAxis.Exponent = 0;
title('Zeitmessungen CPU i5')
xlabel('Anzahl Elemente')
ylabel('Zeit in Millisekunden')
legend('bubblesort', 'parallel bubblesort', 'bitonic mergesort','Location','northwest')
figure;

x = [16 32 64 128 256 512 1024 2048 4096 8192 16384 32768 65536];
y_cpuRyzen5_bubble = [0.017 0.028 0.040 0.088 0.281 1.015 3.916 15.344 65.219 309.035 1286.446 5252.279 20765.194];
y_cpuRyzen5__parallel_bubble = [0.372 0.754 1.443 2.805 5.703 11.649 23.642 48.513 101.845 238.377 628.084 1821.525 6374.055];
y_cpuRyzen5_merge = [0.016 0.026 0.039 0.092 0.247 0.818 2.912 10.720 41.432 274.802 1496.998 5058.049 19688.556];
plot(x, y_cpuRyzen5_bubble, 'b.-', x, y_cpuRyzen5__parallel_bubble, 'c.-', x, y_cpuRyzen5_merge, 'r.-')
xticks(x)
ax=gca; ax.XAxis.Exponent = 0;
ax=gca; ax.YAxis.Exponent = 0;
title('Zeitmessungen CPU Ryzen 5')
xlabel('Anzahl Elemente')
ylabel('Zeit in Millisekunden')
legend('bubblesort', 'parallel bubblesort', 'bitonic mergesort','Location','northwest')
figure;

x = [16 32 64 128 256 512 1024 2048 4096 8192 16384 32768 65536];
y_gpu_bubble_execution_OpenCL = [0.2451 0.5128 1.0187 2.0943 4.0221 8.1586 15.8241 32.5062 66.3929 141.6652 297.9275 734.0964 2069.0165];
y_gpu_bubble_whole = [7.718 10.487 17.290 36.368 66.539 126.283 250.888 499.768 1011.611 2105.625 2782.859 5338.790 11283.997];
plot(x, y_gpu_bubble_execution_OpenCL, 'b.-', x, y_gpu_bubble_whole, 'r.-')
xticks(x)
ax=gca; ax.XAxis.Exponent = 0;
ax=gca; ax.YAxis.Exponent = 0;
title('Zeitmessungen GPU')
xlabel('Anzahl Elemente')
ylabel('Zeit in Millisekunden')
legend('bubblesort OpenCL execution time', 'bubblesort whole Calc','Location','northwest')
figure;





y_fpga_bubble_vergleich = [0.003151 0.003843];
y_fpga_merge_vergleich = [0.003891 0.005337 0.006896];
y_raspi_bubble_vergleich = [0.028 0.089 0.289];
y_raspi__parallel_bubble_vergleich = [0.484 0.504 0.730];
y_raspi_merge_vergleich = [0.039 0.123 0.269];
y_cpui5_bubble_vergleich = [0.072 0.074 0.118];
y_cpui5__parallel_bubble_vergleich = [0.624 1.284 2.325];
y_cpui5_merge_vergleich = [0.054 0.060 0.100];
y_cpuRyzen5_bubble_vergleich = [0.017 0.028 0.040];
y_cpuRyzen5__parallel_bubble_vergleich = [0.372 0.754 1.443];
y_cpuRyzen5_merge_vergleich = [0.016 0.026 0.039];
y_gpu_bubble_execution_OpenCL_vergleich = [0.2451 0.5128 1.0187];
y_gpu_bubble_whole_vergleich = [7.718 10.487 17.290];
plot(x_fpga_bubble, y_fpga_bubble_vergleich, 'b.-', x_fpga_merge, y_fpga_merge_vergleich, 'r.-', x_fpga_merge, y_raspi_bubble_vergleich, 'm.-', x_fpga_merge, y_raspi__parallel_bubble_vergleich, 'c.-', x_fpga_merge, y_raspi_merge_vergleich, 'y.-', x_fpga_merge, y_cpui5_bubble_vergleich, 'g.-', x_fpga_merge, y_cpui5__parallel_bubble_vergleich, 'k.-', x_fpga_merge, y_cpui5_merge_vergleich, 'b.-', x_fpga_merge, y_cpuRyzen5_bubble_vergleich, 'b.-', x_fpga_merge, y_cpuRyzen5__parallel_bubble_vergleich, 'c.-', x_fpga_merge, y_cpuRyzen5_merge_vergleich, 'r.-', x_fpga_merge, y_gpu_bubble_execution_OpenCL_vergleich, 'b.-', x_fpga_merge, y_gpu_bubble_whole_vergleich, 'r.-')
title('Alle Zeitmessungen')
xlabel('Anzahl Elemente')
ylabel('Zeit in Millisekunden')
xticks(x)
ax=gca; ax.XAxis.Exponent = 0;
ax=gca; ax.YAxis.Exponent = 0;
figure;


plot(x_fpga_bubble, y_fpga_bubble_vergleich, 'b.-', x_fpga_merge, y_raspi_bubble_vergleich, 'm.-', x_fpga_merge, y_raspi__parallel_bubble_vergleich, 'c.-', x_fpga_merge, y_cpui5_bubble_vergleich, 'g.-', x_fpga_merge, y_cpui5__parallel_bubble_vergleich, 'k.-', x_fpga_merge, y_cpuRyzen5_bubble_vergleich, 'b.-', x_fpga_merge, y_cpuRyzen5__parallel_bubble_vergleich, 'c.-', x_fpga_merge, y_gpu_bubble_execution_OpenCL_vergleich, 'b.-', x_fpga_merge, y_gpu_bubble_whole_vergleich, 'r.-')
title('Alle Zeitmessungen Bubblesort')
xlabel('Anzahl Elemente')
ylabel('Zeit in Millisekunden')
xticks(x_fpga_merge)
ax=gca; ax.XAxis.Exponent = 0;
ax=gca; ax.YAxis.Exponent = 0;
figure;

plot(x_fpga_merge, y_fpga_merge_vergleich, 'r.-', x_fpga_merge, y_raspi_merge_vergleich, 'y.-', x_fpga_merge, y_cpui5_merge_vergleich, 'b.-', x_fpga_merge, y_cpuRyzen5_merge_vergleich, 'c.-')
title('Alle Zeitmessungen Bitonic Mergesort')
xlabel('Anzahl Elemente')
ylabel('Zeit in Millisekunden')
xticks(x_fpga_merge)
ax=gca; ax.XAxis.Exponent = 0;
ax=gca; ax.YAxis.Exponent = 0;
figure;