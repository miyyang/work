#include <stdio.h>
#include <ctime>


static void HandleError( cudaError_t err,
                         const char *file,
                         int line ) {
    if (err != cudaSuccess) {
        printf( "%s in %s at line %d\n", cudaGetErrorString( err ),
                file, line );
        exit( EXIT_FAILURE );
    }
}
#define HANDLE_ERROR( err ) (HandleError( err, __FILE__, __LINE__ ))

template< typename T >
void swap( T& a, T& b ) {
    T t = a;
    a = b;
    b = t;
}

struct DataBlock
{
int *outbitmap;
int *dev_in;
int *dev_out;
int *bitmap;
};

__global__ void update(int *in, int *out, int dim){
    int offset = threadIdx.x + blockIdx.x * blockDim.x;
    int x = offset % dim;
    int y = (int)(offset / dim);
    while (offset < dim * dim) {
        int sum = 0;
        for(int i=-1; i < 2; i++) {
            for(int j=-1; j < 2; j++) {
                int xtemp = (x + i + dim) % dim;
                int ytemp = (y + j + dim) % dim;
                int offsettemp = xtemp + ytemp * dim;
                sum = sum + in[offsettemp];
            }
        }
        sum = sum - in[offset];
        if (in[offset] == 1) {
            if (sum == 2 || sum ==3) {
                out[offset] = 1;
            }
            else {
                out[offset] = 0;
            }
        }
        else {
            if( sum == 3) {
                out[offset] = 1;
            }
            else {
                out[offset] = 0;
            }
        }
        offset = offset + blockDim.x * gridDim.x;
    }
}

int main(int argc, char *argv[]) {
    
    clock_t start;
    clock_t gpu_start;
    float gpu_comp_time = 0;
    float gpu_mem_to_time = 0, gpu_mem_back_time=0;
    int dim = atoi(argv[1]);
    int nStep = atoi(argv[2]);
//    int frequency = atoi(argv[3]);
    int size = dim * dim;
    int step;
    DataBlock data;
    data.bitmap=(int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        data.bitmap[i] = 0;
    }
    data.bitmap[1]=1;
    data.bitmap[dim+2] = 1;
    data.bitmap[2 * dim + 0] = 1;
    data.bitmap[2 * dim + 1] = 1;
    data.bitmap[2 * dim + 2] = 1;
    data.outbitmap=(int *)malloc(size * sizeof(int));
    int bitmapSize=size * sizeof(int);
    
    start=clock();
    
    gpu_start = clock();
    HANDLE_ERROR(cudaMalloc( (void **)&(data.dev_in), bitmapSize));
    HANDLE_ERROR(cudaMalloc( (void **)&(data.dev_out), bitmapSize));
    HANDLE_ERROR(cudaMemcpy(data.dev_in, data.bitmap, bitmapSize, cudaMemcpyHostToDevice));
    gpu_mem_to_time = ((float)(clock() - gpu_start)) / CLOCKS_PER_SEC;
    
    // dim3 dimgrid(dim / 16, dim / 16);
    // dim3 dimblock(16, 16);
    int grid_dim;
    int block_dim;
    if (dim < 1024) {
        grid_dim = dim;
        block_dim = dim;
    }
    else {
        grid_dim = 1024;
        block_dim = 1024;
    }
    
    gpu_start = clock();

    for(step = 0; step < nStep; step++ ){
        
        update<<<grid_dim, block_dim>>>(data.dev_in, data.dev_out,dim);
        
        swap(data.dev_in,data.dev_out);
    }

    cudaDeviceSynchronize();
    gpu_comp_time = ((float)(clock() - gpu_start)) / CLOCKS_PER_SEC;
    gpu_start = clock();
    HANDLE_ERROR(cudaMemcpy(data.outbitmap, data.dev_out, bitmapSize, cudaMemcpyDeviceToHost));
    gpu_mem_back_time = ((float)(clock() - gpu_start)) / CLOCKS_PER_SEC;
    HANDLE_ERROR(cudaFree(data.dev_out));
    HANDLE_ERROR(cudaFree(data.dev_in));
    
    printf("%f %f %f ", gpu_comp_time, gpu_mem_to_time, gpu_mem_back_time);
    printf("%f\n", ((float)(clock() - start)) / CLOCKS_PER_SEC);
}