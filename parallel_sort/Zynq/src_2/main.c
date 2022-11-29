#include <xtop_level_sort2_hw.h>
#include <xtop_level_sort2.h>
#include <xil_io.h>
#include <xil_cache.h>
#include <stdio.h>
//#include "platform.h" //not needed when cache is turned off
#include "xil_printf.h"
#include <xtmrctr.h>

//#define TIME_CONST (1.0/(667000000.0/2.0)) //667MHz ARM Core Clock

int main()
{
	XTmrCtr timer;
	u32 time = 0;
	XTmrCtr_Initialize(&timer, XPAR_AXI_TIMER_0_DEVICE_ID);

    //init_platform();
    Xil_DCacheDisable();

    XTop_level_sort2 sort_inst;
    XTop_level_sort2_Initialize(&sort_inst, 0);

    int a[32] = {
    		2,4,3,6,8,7,66,5,44,33,97,42,57,90,54,65,76,87,36,24,36,5,3,9,12,36,21,88,54,22,43,0
    };
    print("unsorted array: \n\r");
    for(int i = 0; i < 32; i++){
    	xil_printf("%d,", a[i]);
    }
    print("\n\r");

    XTop_level_sort2_Set_memory(&sort_inst, (u64)a);
    //don't use, when cache is disabled
    //Xil_DCacheFlush(); //write back content of cache to main mem


    //wait till the hardware is ready
    while(!XTop_level_sort2_IsReady(&sort_inst));
    XTmrCtr_Start(&timer, 0x0);
	//start sorting
	XTop_level_sort2_Start(&sort_inst);
	//sorting is finished
	while(!XTop_level_sort2_IsDone(&sort_inst));
	XTmrCtr_Stop(&timer, 0x0);

    //don't use, when cache is disabled
    //Xil_DCacheInvalidate(); //mark cache lines as invalidate (so now read from main mem)

    print("sorted array: \n\r");
    for(int i = 0; i < 32; i++){
    	xil_printf("%d,", a[i]);
    }
    print("\n\r");

    time = XTmrCtr_GetValue(&timer, 0x0);
    xil_printf("AXI Timer: %d cycles, ", time);
    xil_printf("AXI Timer: %d nanoseconds", time*10);
    print("\n\r");
    XTmrCtr_SetResetValue(&timer, 0x0, 0);

    //cleanup_platform();
    return 0;
}

//time for first sorting algo with 32 elements: 3980 nanoseconds
//time for second sorting algo with 32 elements: 9670 nanoseconds
