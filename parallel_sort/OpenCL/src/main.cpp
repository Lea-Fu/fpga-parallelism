#if defined(__APPLE__) || defined(__MACOSX)
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif

/*#if defined(__APPLE__) || defined(__MACOSX)
#include </Library/Developer/CommandLineTools/SDKs/MacOSX12.3.sdk/System/Library/Frameworks/OpenCL.framework/Headers/cl.h>
#else
#include <CL/cl.h>
#endif
 */

#include <stdio.h>
#include <stdlib.h>


#define SORT_SIZE 32

//compute kernel which sorts elements and runs for every work item created
const char *KernelSource =
        "__kernel                                        \n"
        "void KernelSource(__global float *a,            \n"
        " const int offset)                              \n"
        "{                                               \n"
        "    int tmp[2] = {0,0};                         \n"
        "    int i = get_global_id(0)*2+offset;          \n"
        "    int size = get_global_size(0);              \n"
        "    if (size-1 != get_global_id(0) || offset!=1)\n"
        "    {                                           \n"
        "           if (a[i] > a[i + 1])                 \n"
        "           {                                    \n"
        "               tmp[0] = a[i + 1];               \n"
        "               tmp[1] = a[i];                   \n"
        "               a[i] = tmp[0];                   \n"
        "               a[i + 1] = tmp[1];               \n"
        "           }                                    \n"
        "    }                                           \n"
        "}                                               \n";



int main(void) {
    int i;
    float *a = (float*)malloc(sizeof(float) * SORT_SIZE);
    //create "random" numbers to sort
    for(i = 0; i < SORT_SIZE; i++)
    {
        a[i] = rand() % 100;
    }
    /*
    int tmp[2];
    for (int j = 0; j < SORT_SIZE/2 ; j++) {
        for (int i = 0; i < SORT_SIZE - 1; i+=2) {
            if (a[i] > a[i + 1]) {
                tmp[0] = a[i + 1];
                tmp[1] = a[i];
                a[i] = tmp[0];
                a[i + 1] = tmp[1];
            }
        }
        for (int i = 1; i < SORT_SIZE - 2; i+=2) {
            if (a[i] > a[i + 1]) {
                tmp[0] = a[i + 1];
                tmp[1] = a[i];
                a[i] = tmp[0];
                a[i + 1] = tmp[1];
            }
        }
    }
     */

    //compute platform id
    cl_platform_id *platforms = NULL;
    cl_uint     num_platforms;
    //set up the platform
    cl_int clStatus = clGetPlatformIDs(0, NULL, &num_platforms);
    platforms = (cl_platform_id *)
            malloc(sizeof(cl_platform_id)*num_platforms);
    clStatus = clGetPlatformIDs(num_platforms, platforms, NULL);
    //compute the devices id
    cl_device_id     *device_list = NULL;
    cl_uint           num_devices;
    //connect to a compute device
    clStatus = clGetDeviceIDs( platforms[0], CL_DEVICE_TYPE_GPU, 0,NULL, &num_devices);
    device_list = (cl_device_id *)
            malloc(sizeof(cl_device_id)*num_devices);
    clStatus = clGetDeviceIDs( platforms[0],CL_DEVICE_TYPE_GPU, num_devices, device_list, NULL);
    //compute context
    cl_context context;
    //create compute context
    context = clCreateContext( NULL, num_devices, device_list, NULL, NULL, &clStatus);
    //create a command queue
    cl_command_queue command_queue = clCreateCommandQueue(context, device_list[0], 0, &clStatus);
    //create memory buffers on the device
    cl_mem A_clmem = clCreateBuffer(context, CL_MEM_READ_ONLY, SORT_SIZE * sizeof(float), NULL, &clStatus);
    //write our data set into the input array in device memory
    clStatus = clEnqueueWriteBuffer(command_queue, A_clmem, CL_TRUE, 0, SORT_SIZE * sizeof(float), a, 0, NULL, NULL);
    //create the compute program from the source buffer
    cl_program program = clCreateProgramWithSource(context, 1,(const char **)&KernelSource, NULL, &clStatus);
    //build the program executable
    clStatus = clBuildProgram(program, 1, device_list, NULL, NULL, NULL);
    if(clStatus){
        printf("Could not build program!");
        return clStatus;
    }

    //create the compute kernel in the program we wish to run
    cl_kernel kernel = clCreateKernel(program, "KernelSource", &clStatus);
    //set the arguments to our compute kernel
    clStatus = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&A_clmem);
    //execute the kernel
    size_t global_size = SORT_SIZE/2;
    size_t local_size = 16;
    for (int j = 0; j < SORT_SIZE/2; ++j) {
        int offset = 0;
        clSetKernelArg(kernel, 1, sizeof(unsigned int), &offset);
        clStatus = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_size, &local_size, 0, NULL, NULL);
        offset = 1;
        clSetKernelArg(kernel, 1, sizeof(unsigned int), &offset);
        clStatus = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_size, &local_size, 0, NULL, NULL);
    }

    //read back the results (A_clmem) from the device to verify the output (a)
    clStatus = clEnqueueReadBuffer(command_queue, A_clmem, CL_TRUE, 0, SORT_SIZE * sizeof(float), a, 0, NULL, NULL);
    //cleanup and wait for all the commands to complete
    clStatus = clFlush(command_queue);
    clStatus = clFinish(command_queue);
    //display result
    for(i = 0; i < SORT_SIZE; i++)
        printf("%f\n", a[i]);
    //release all OpenCL allocated objects and host buffers
    clStatus = clReleaseKernel(kernel);
    clStatus = clReleaseProgram(program);
    clStatus = clReleaseMemObject(A_clmem);
    clStatus = clReleaseCommandQueue(command_queue);
    clStatus = clReleaseContext(context);
    free(a);
    free(platforms);
    free(device_list);
    return 0;

}