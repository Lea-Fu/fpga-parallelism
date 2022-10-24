#include <xtop_level_sort_hw.h>
#include <xtop_level_sort.h>
#include <xil_io.h>
#include <xil_cache.h>
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xtime_l.h"

//#define TIME_CONST (1.0/(667000000.0/2.0)) //667MHz ARM Core Clock

int main()
{
	uint32_t test_time;
	XTime gbl_time_before_test;
	XTime gbl_time_after_test;

    init_platform();
    Xil_DCacheDisable();

    XTop_level_sort sort_inst;
    XTop_level_sort_Initialize(&sort_inst, 0);

    int a[32] = {
    		2,4,3,6,8,7,66,5,44,33,97,42,57,90,54,65,76,87,36,24,36,5,3,9,12,36,21,88,54,22,43,0
    };
    print("unsorted array: \n\r");
    for(int i = 0; i < 32; i++){
    	xil_printf("%d,", a[i]);
    }
    print("\n\r");

    XTop_level_sort_Set_memory(&sort_inst, (u64)a);
    //don't use, when cache is disabled
    //Xil_DCacheFlush(); //write back content of cache to main mem


    //wait till the hardware is ready
    while(!XTop_level_sort_IsReady(&sort_inst));
    XTime_SetTime(0);
    XTime_GetTime(&gbl_time_before_test);
    //for(int i = 0; i < 10000000; i++); to test/prrof that the timer doesn't work properly
	//start sorting
	XTop_level_sort_Start(&sort_inst);
	//sorting is finished
	while(!XTop_level_sort_IsDone(&sort_inst));
	XTime_GetTime(&gbl_time_after_test);

    //don't use, when cache is disabled
    //Xil_DCacheInvalidate(); //mark cache lines as invalidate (so now read from main mem)

    print("sorted array: \n\r");
    for(int i = 0; i < 32; i++){
    	xil_printf("%d,", a[i]);
    }
    print("\n\r");

    test_time = (u64)gbl_time_after_test - (u64)gbl_time_before_test;
    print("just sorting time: ");
    printf("%lld microseconds", (long long)(1000000*test_time*1.0/COUNTS_PER_SECOND)); //*TIME_CONST);
    print("\n\r");

    cleanup_platform();
    return 0;
}
