#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_THREAD 4
#define DEBUG 0

int main (int argc, char *argv[]) 
{
    int i, j, k;
    double wtime;
    int chunk = 10;
    int scale = atoi(argv[1]);

    float** a = (float**)malloc(sizeof(float*) * scale);
    for (i = 0; i < scale; i++)
        a[i] = (float*)malloc(sizeof(float) * scale);
    float** b = (float**)malloc(sizeof(float*) * scale);
    for (i = 0; i < scale; i++)
        b[i] = (float*)malloc(sizeof(float) * scale);
    float** c = (float**)malloc(sizeof(float*) * scale);
    for (i = 0; i < scale; i++)
        c[i] = (float*)malloc(sizeof(float) * scale);

    wtime = omp_get_wtime();
    #pragma omp parallel shared(a,b,c,scale,chunk) private(i,j,k) num_threads(NUM_THREAD)
    {
        srand(time(0));
        #pragma omp for schedule (static, chunk) 
        for (i=0; i<scale; i++)
            for (j=0; j<scale; j++)
                a[i][j]= rand() / 1000;
        #pragma omp for schedule (static, chunk)
        for (i=0; i<scale; i++)
            for (j=0; j<scale; j++)
                b[i][j]= rand() / 1000;
        #pragma omp for schedule (static, chunk)
        for (i=0; i<scale; i++)
            for (j=0; j<scale; j++)
                c[i][j]= 0;

        #pragma omp for schedule (static, chunk)
        for (i=0; i<scale; i++)    
        {
            for(j=0; j<scale; j++)       
                for (k=0; k<scale; k++)
                    c[i][j] += a[i][k] * b[k][j];
        }
    }
    wtime = omp_get_wtime() - wtime;
    printf("time: %lf s\n", wtime);

    if (DEBUG)
    {
        for (i = 0; i < scale; i++)
        {
            for (j = 0; j < scale; j++)
                printf("%f", c[i][j]);
            printf("\n");
        }
    }

    return 0;
}