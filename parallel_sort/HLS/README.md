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
       2. Export RTL Code (into ip_repo Directory from Vivado)
          --> go into directiory and extract zip folder

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
       1.-4. 1. if reloaded: Refresh IP Catalog --> Upgrade Selected
             2. in end design: remove debug logic analyzer
                --> block design --> rightclick bug --> clear debug
             3. in end design: rightclick design_1 --> Generate Output Products...
                --> Synthesis Options --> Global --> Generate
             4. (just necessary for sort_2) in end design:
                [to get rid of the negative slack]
                Tools --> Settings...
                --> Synthesis --> Settings
                     --> -directive* --> PerformanceOptimized
                     --> -retiming* -->  checked
                     --> Apply
                --> Implementation --> Settings
                     --> Opt Design --> -directive* --> ExploreWithRemap
                     --> Place Design --> -directive* --> AltSpreadLogic_high
                     --> Post-Place Phys Opt Design --> -directive* -->  AlternateFlowWithRetiming
                     --> Route Design --> -directive* --> HigherDelayCost
                     --> Post-Route Phys Opt Design --> is_enabled* -->  checked
                     --> Post-Route Phys Opt Design --> tcl_post* -->  Path to AddRetime.tcl
                     --> Post-Route Phys Opt Design --> -directive* -->  AddRetime
                     --> Apply
                (https://docs.xilinx.com/r/en-US/ug904-vivado-implementation/Using-Directives?tocId=tiGPVMrdHU~0e0pAOJjFJQ)
       5. Run Synthesis
       6. Run Implementation
       7. Generate Bitstream
       8. File --> Export --> Export Hardware... --> Include Bitstream
       9. Tools --> Launch Vitis IDE

4. Vitis

       1. File --> New --> Application Project... --> Add
          --> Create new platform from hardware (XSA) --> Browse...
          --> Empty Application(C) --> write Code for FPGA here
       2. Modify BSP Settings... --> standalone --> stdin --> ps7_uart_1
         --> stdout --> ps7_uart_1
       3. Playbutton --> Run Configurations... --> Single Application Debug --> Target Setup
          --> !Reset Entire System --> !program FPGA --> check bitstream file --> Apply
       4. connect real FPGA to your computer
       5. Xilinx --> Program Device --> Program
       6. Console Plus Symbole --> 4 Command Shell Console
       7. Playbutton --> 1 Debugger_fpga_parallelism_vitis_(default)
