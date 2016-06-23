#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <cuda.h>

__global__ void generatePrimes(int *sizeD, int *maxPrimeD, int *numPrimesD) {
	__shared__ int numPrimesB;
	__shared__ int maxPrimeB;
	if(threadIdx.x == 0) {
		numPrimesB = 0;
		maxPrimeB = 0;
	}
	__syncthreads();
	int no = 9 + (blockIdx.x * 2000) + (2 * threadIdx.x);
	if(no < *sizeD) {
		int noRt = __double2int_ru(sqrt(__int2double_rn(no)));
		int k=3;
		for (k = 3; k <= noRt; k += 2) {
			if (no % k == 0) {
				break;
			}
		}
		if (k > noRt) {
			atomicAdd(&numPrimesB, 1);
			atomicMax(&maxPrimeB, no);
		}
		__syncthreads();
		if(threadIdx.x == 0) {
			atomicAdd(numPrimesD, numPrimesB);
			atomicMax(maxPrimeD, maxPrimeB);
		}
	}
}

int main(int argc, char* argv[]) {

	struct timeval t;
	double start_t, end_t, time_spent;
	int maxPrime = 0, numPrimes = 0, size = atoi(argv[1]);
	int gridSize = (int)(floor(size/2000.0));
	dim3 dimGrid(gridSize+1);
	dim3 dimBlock(1000);

	int *sizeD, *maxPrimeD, *numPrimesD;
	cudaMalloc((void**)&sizeD, sizeof(int));
	cudaMalloc((void**)&maxPrimeD, sizeof(int));
	cudaMalloc((void**)&numPrimesD, sizeof(int));

	gettimeofday(&t, NULL);
	start_t = (t.tv_sec * 1000000.0) + t.tv_usec;
	cudaMemcpy(sizeD, &size, sizeof(int),cudaMemcpyHostToDevice);
	cudaMemcpy(maxPrimeD, &maxPrime, sizeof(int),cudaMemcpyHostToDevice);
	cudaMemcpy(numPrimesD, &numPrimes, sizeof(int),cudaMemcpyHostToDevice);
	generatePrimes<<<dimGrid, dimBlock>>> (sizeD, maxPrimeD, numPrimesD);
	cudaMemcpy(&maxPrime, maxPrimeD, sizeof(int),cudaMemcpyDeviceToHost);
	cudaMemcpy(&numPrimes, numPrimesD, sizeof(int),cudaMemcpyDeviceToHost);
	gettimeofday(&t, NULL);
	end_t = (t.tv_sec * 1000000.0) + t.tv_usec;
	time_spent = end_t - start_t;

	cudaFree(sizeD);
	cudaFree(maxPrimeD);
	cudaFree(numPrimesD);

	
	printf("Max prime number %d\ninput size %d\nTotal time %f secs\nprime number %d\n",
			maxPrime, size, time_spent / 1000000.0, numPrimes+4);
	
	return 0;
}