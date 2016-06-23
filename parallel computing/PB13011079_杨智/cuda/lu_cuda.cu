#include <cuda.h>
#include <stdio.h>
#include <math.h>

__global__ void add( float *a, float *b, float *c) {
	int tid = blockIdx.x;
	c[tid] = a[tid] + b[tid];
}


__global__ void scale(float *a, int size, int index){
 	int i;
	int start=(index*size+index);
	int end=(index*size+size);
	
	for(i=start+1;i<end;i++)
		a[i]=(a[i]/a[start]);
}

__global__ void reduce(float *a, int size, int index, int b_size){
	extern __shared__ float pivot[];
	int i;

	int tid=threadIdx.x;
	int bid=blockIdx.x;
	int block_size=b_size;

	int start;
	int end;
	int pivot_row;
	int my_row;

	if(tid==0)
		for(i=index;i<size;i++) pivot[i]=a[(index*size)+i];

	__syncthreads();

	pivot_row=(index*size);
	my_row=(((block_size*bid) + tid)*size);
	start=my_row+index;
	end=my_row+size;

	if(my_row >pivot_row)
		for(i=start+1;i<end;i++)
			a[i]=a[i]-(a[start]*pivot[(i-my_row)]);
}

float a[5001][5001];
float b[5001][5001];
float c[5001][5001];
float result[5001][5001];


int main(int argc, char *argv[]){
	int N;
	int blocks;
	float *dev_a;
	int i;
	int j;
	N = atoi(argv[1]);	
	clock_t start, finish;
	double elapse;

	cudaMalloc((void**)&dev_a, N * N * sizeof(float));
	srand((unsigned)2);
	for (i = 0; i <= N; i++)
		for (j = 0; j <= N; j++)
		a[i][j] = ((rand() % 10) + 1);
	cudaMemcpy(dev_a, a, N * N * sizeof(float), cudaMemcpyHostToDevice);

	start = clock();
	for(i = 0; i < N; i++){
		scale<<<1,1>>>(dev_a, N, i);
		blocks = N / 50;
		reduce<<<blocks,50,N*sizeof(float)>>>(dev_a, N, i, 50);
	}
 	finish = clock();
	elapse = (((double) (finish - start)) / CLOCKS_PER_SEC);
	printf("lu decompositon: %lf sec\n", elapse);

	cudaMemcpy(c, dev_a, N * N * sizeof(float),cudaMemcpyDeviceToHost);
	cudaFree( dev_a );
	
	return 0;
}