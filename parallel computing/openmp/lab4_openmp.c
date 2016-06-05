#include <stdio.h> 
#include <stdlib.h>
#include <omp.h> 
#include <time.h>

#define MAXN 5001
#define NNN 2000
#define NUM_OF_THREADS 4
  
double A[MAXN][MAXN]; 
double L[MAXN][MAXN];
double U[MAXN][MAXN];
int nthreads,tid;  

int factorize() {
	int i, j, k; 
	#pragma omp parallel shared(A) private(tid, i, j, k)     
	{ 
		for (k = 0; k < NNN; k++)         
		{
			#pragma omp for            
			for (i = k + 1; i < NNN; i++)                 
				A[i][k] = A[i][k] / A[k][k]; 
			#pragma omp for         
			for (i = k + 1; i < NNN; i++)                 
				for (j = k + 1; j < NNN; j++)                 
				{ 
					A[i][j] = A[i][j] - A[i][k] * A[k][j];                 
				}         
		}     
	}
	for (i = 0; i < NNN; i++)         
		for (j = 0; j < NNN; j++)         
		{
			if (i <= j) 
				U[i][j] = A[i][j];             
			else 
				L[i][j] = A[i][j];         
		}     
	return 0; 
}  

int main() 
{ 
	double wtime;
	int i, j;

	srand((unsigned)time(NULL));   
	for (i = 0; i < NNN; i++)         
		for (j = 0; j < NNN; j++) 
		{
			A[i][j] = rand() / 1000; 
			L[i][j] = 0;
			U[i][j] = 0;
		}

	omp_set_num_threads(NUM_OF_THREADS);  

	for (i = 0; i < NNN; i++) 
		L[i][i] = 1; 

	wtime = omp_get_wtime();     
	factorize(); 
	wtime = omp_get_wtime() - wtime; 

	printf("time = %lf s\n", wtime);  

	return 0; 
}