#include <xtop_level_sort_hw.h>
#include <xtop_level_sort.h>
#include <xil_io.h>
#include <xil_cache.h>
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"

int main()
{
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
    Xil_DCacheFlush(); //write back content of cache to main mem


    if (XTop_level_sort_IsReady(&sort_inst)) {
    	//start sorting
    	XTop_level_sort_Start(&sort_inst);

    	//sorting is finished
    	while(!XTop_level_sort_IsDone(&sort_inst));
    }

    Xil_DCacheInvalidate(); //mark cache lines as invalidate (so now read from main mem)

    print("sorted array: \n\r");
    for(int i = 0; i < 32; i++){
    	xil_printf("%d,", a[i]);
    }
    print("\n\r");

    cleanup_platform();
    return 0;
}
