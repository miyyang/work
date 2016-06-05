#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define NUM_THREAD 1

int prime_number (int n)
{
    int i;
    int j;
    int prime;
    int total = 1;

    # pragma omp parallel \
    shared(n) \
    private(i, j, prime)

    # pragma omp for reduction ( + : total )
    for (i = 3; i <= n; i += 2)
    {
        prime = 1;
        if (i % 2 == 0)
            prime = 0;
        for (j = 3; j < i / 2; j += 2)
        {
            if (i % j == 0)
            {
                prime = 0;
                break;
            }
        }
        total = total + prime;
    }

    return total;
}

int main (int argc, char *argv[])
{
    int n;
    double wtime;
    long primes;

    printf ("Number of processors available = %d\n", omp_get_num_procs ( ) );
    printf ("Number of threads =              %d\n", omp_get_max_threads ( ) );
    printf("\n\tn\t\tprime_num\ttime(second)\n");
    n = 100000;

    omp_set_num_threads(NUM_THREAD);  

    wtime = omp_get_wtime();
    primes = prime_number(n);
    wtime = omp_get_wtime() - wtime;
    printf("\t%d\t\t%d\t\t%lf\n", n, primes, wtime);

    n = 500000;

    wtime = omp_get_wtime();
    primes = prime_number(n);
    wtime = omp_get_wtime() - wtime;
    printf("\t%d\t\t%d\t\t%lf\n", n, primes, wtime);

    n = 1000000;

    wtime = omp_get_wtime();
    primes = prime_number(n);
    wtime = omp_get_wtime() - wtime;
    printf("\t%d\t\t%d\t\t%lf\n", n, primes, wtime);

    return 0;
}
