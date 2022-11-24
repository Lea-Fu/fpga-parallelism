this directory is for the C/C++ Code that is written for the CPU (also the Raspberry Pi),
and the FPGA. It gets generated into Verilog/VHDL Code as an RTL Export. In here is also the
use of OpenMP.

<br>

***

**How To Use:**

1. Clion or other IDE for
   
       1. C/C++ Code for CPU (implies Raspberry Pi) and FPGA

2. Vitis HLS

       1. Run C Synthesis
       2. Export RTL Code

3. Vivado

       1. Create Block Design
       2. Tools --> Settings --> IP --> Repository --> +
       3. + --> Zynq --> Run Block Automation
          --> TopLevelSort(2) --> Run Connection Automation --> Regenerate Layout 
          --> + --> Axi Timer
          --> TopLevelSort(2) Connection rightclick --> Debug (2 times (on both sides))
          --> Run Connection Automation --> Regenerate Layout --> save (ctrl+s)
          --> Validate design --> save (ctrl+s)
       4. Sources --> design_1 rightclick --> Create HDL Wrapper...
       5. Run Synthesis
       6. Run Implementation
       7. Generate Bitstream
       8. File --> Export --> Export Hardware... --> Include Bitstream
       9. Tools --> Launch Vitis IDE

4. Vitis

       1. File --> New --> Application Project... --> Add 
          --> Create new platform from hardware (XSA) --> Browse...
          --> Empty Application(C) --> write Code for FPGA here