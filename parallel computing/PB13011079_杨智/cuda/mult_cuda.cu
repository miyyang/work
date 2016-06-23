// matrix multiplication
// CA_LAB4

#include<stdio.h>
#include<iostream>
#include<cstdlib>
#include<time.h>
#include<cuda.h>

#define TILE_WIDTH 32
#define DEBUG 0
using namespace std;

void print(float *A, int n, int m)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		cout << A[n*i+j] << " ";
		cout<<endl;
}

void init_matrix (float *mat, float value, int n, int m)
{
	int size = n * m; 
	for (int i = 0; i < size; i++)
		mat[i] = value;
}

void multMatrixSeq (float *mA, float *mB, float *mC, int n, int m, int o)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < o; j++)
		{
			float sum = 0;
			for (int k = 0; k < m; k++)
			{
				sum += mA[m*i+k] * mB[o*k+j];
			}
			mC[o*i+j] = sum;
		}
	}
}

__global__ void CU_multMatrixThread (float *mA, float *mB, float *mC, int n, int m, int o)
{
	int row = blockIdx.y * blockDim.y + threadIdx.y;
	int col = blockIdx.x * blockDim.x + threadIdx.x;

	if ((row<n) && (col<o))
	{
		float temp = 0;
		for (int i = 0; i < m; i++)
			temp += mA[row*m+i] * mB[i*o+col];
		mC[row*o+col] = temp;
	}
}

__global__ void CU_multMatrixTiled(float *mA, float *mB, float *mC, int n, int m, int o){
	__shared__ float tmpM1[TILE_WIDTH][TILE_WIDTH];
	__shared__ float tmpM2[TILE_WIDTH][TILE_WIDTH];

	int bx = blockIdx.x;
	int by = blockIdx.y;
	int tx = threadIdx.x;
	int ty = threadIdx.y;

	int row = by * TILE_WIDTH + ty;
	int col = bx * TILE_WIDTH + tx;

	float Pvalue = 0;

	for (int k = 0; k < (m + TILE_WIDTH - 1) / TILE_WIDTH; ++k)
	{
		if (k*TILE_WIDTH + tx < m && row < n)
			tmpM1[ty][tx] = mA[row * m + k*TILE_WIDTH + tx];
		else
			tmpM1[ty][tx] = 0;

		if (k*TILE_WIDTH + ty < m && col < o)
			tmpM2[ty][tx] = mB[(k*TILE_WIDTH + ty) * o + col];
		else
			tmpM2[ty][tx] =0;

		__syncthreads();
		
		for(int k = 0; k < TILE_WIDTH; ++k)
			Pvalue += tmpM1[ty][k] * tmpM2[k][tx];
		
		__syncthreads();
	}

	if (row < n && col < o)
		mC[row * o + col] = Pvalue;
}

void multMatrixTiled(float *A, float *B, float *C, int n, int m, int o)
{
	float blockSize = TILE_WIDTH;
	float *mA, *mB, *mC;

	cudaMalloc(&mA, n * m * sizeof(float));
	cudaMalloc(&mB, m * o * sizeof(float));
	cudaMalloc(&mC, n * o * sizeof(float));

	cudaMemcpy(mA, A, n * m * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(mB, B, m * o * sizeof(float), cudaMemcpyHostToDevice);

	dim3 threads(blockSize,blockSize,1);
	dim3 blocks(ceil(o/blockSize),ceil(n/blockSize),1);
	CU_multMatrixThread<<<blocks,threads>>>(mA,mB,mC,n,m,o);

	cudaMemcpy (C, mC, n * o * sizeof(float), cudaMemcpyDeviceToHost);

	cudaFree(mA);
	cudaFree(mB);
	cudaFree(mC);

}

void multMatrixThread(float *A, float *B, float *C, int n, int m, int o)
{
	float blockSize = TILE_WIDTH;
	float *mA, *mB, *mC;

	cudaMalloc(&mA, n * m * sizeof(float));
	cudaMalloc(&mB, m * o * sizeof(float));
	cudaMalloc(&mC, n * o * sizeof(float));

	cudaMemcpy(mA, A, n * m * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(mB, B, m * o * sizeof(float), cudaMemcpyHostToDevice);

	dim3 threads(blockSize,blockSize,1);
	dim3 blocks(ceil(o/blockSize),ceil(n/blockSize),1);
	CU_multMatrixThread<<<blocks,threads>>>(mA,mB,mC,n,m,o);

	cudaMemcpy (C, mC, n * o * sizeof(float), cudaMemcpyDeviceToHost);

	cudaFree(mA);
	cudaFree(mB);
	cudaFree(mC);
}

int compareMatrix (float *A, float *B,int n, int m)
{
	int size = n * m;
	for (int i = 0; i < size; i++ )
	{
	if (A[i] != B[i])
	{
		cout<<"the sequential result and parallel result are not equal"<<endl;
		return 0;
	}
	}
	cout<<"the sequential result and parallel result are equal"<<endl;
	return 0;
}

int main(int argc, char* argv[])
{
	clock_t start, finish;
	double elapsedsequential, elapsedParallel, elapsedParallelTiles, optimizationP, optimizationT;
	int kkkkk = atoi(argv[1]);
	int n = kkkkk;
	int m = kkkkk;
	int o = kkkkk;

	float *matA = (float *) malloc(n * m * sizeof(float));
	float *matB = (float *) malloc(m * o * sizeof(float));
	float *matCS = (float *) malloc(n * o * sizeof(float));
	float *matCP = (float *) malloc(n * o * sizeof(float));
	float *matCPT = (float *) malloc(n * o * sizeof(float));

	init_matrix(matA,1.5,n,m);
	init_matrix(matB,1.5,m,o);
	init_matrix(matCS,0,n,o);
	init_matrix(matCP,0,n,o);
	init_matrix(matCPT,0,n,o);


	start = clock();
	multMatrixSeq(matA,matB,matCS,n,m,o);
	finish = clock();
	elapsedsequential = (((double) (finish - start)) / CLOCKS_PER_SEC );
	cout<< "sequential matrix multiplication: " << elapsedsequential << "sec"<< endl<< endl;

	start = clock();
	multMatrixThread(matA,matB,matCP,n,m,o);
	finish = clock();
	elapsedParallel = (((double) (finish - start)) / CLOCKS_PER_SEC );
	cout<< "parallel matrix multiplication without using Tiles: " << elapsedParallel << "sec"<< endl<< endl;

	start = clock();
	multMatrixTiled(matA,matB,matCPT,n,m,o);
	finish = clock();
	elapsedParallelTiles = (((double) (finish - start)) / CLOCKS_PER_SEC );
	cout<< "parallel matrix multiplication using Tiles: " << elapsedParallelTiles << "sec"<< endl<< endl;

	optimizationP = elapsedsequential/elapsedParallel;
	cout<< "speedup without using Tiles: " << optimizationP <<endl;

	optimizationT = elapsedsequential/elapsedParallelTiles;
	cout<< "speedup using Tiles: " << optimizationT <<endl;

	cout<< "check parallel result without using Tiles: " <<endl;
	compareMatrix(matCS,matCP,n,o);
	cout<< "check parallel result using Tiles: " <<endl;
	compareMatrix(matCS,matCPT,n,o);
	
	if (DEBUG)
	{
		print(matCS,n,o);
		cout<<endl;
		print(matCP,n,o);
		cout<<endl;
		print(matCPT,n,o);
	}

	free (matA);
	free (matB);
	free (matCS);
	free (matCP);
	free (matCPT);
	return 0;
}
