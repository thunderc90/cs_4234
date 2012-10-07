
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main (int argc, char *argv[])
{
  int n, nthreads, i, j, seed;
  double x, sum;
  double t0, t1;
  struct drand48_data drand_buf;

  n = 100000000;
  sum = 0.0;

  t0 = omp_get_wtime();
  seed = 1202107158 + omp_get_thread_num() * 1999;
  srand48_r (seed, &drand_buf);

  for (i=0; i<n; i++){
    drand48_r (&drand_buf, &x);
    sum = sum + x;
  }

  t1 = omp_get_wtime();
  printf("time: %7.3f\n", t1-t0);

}
