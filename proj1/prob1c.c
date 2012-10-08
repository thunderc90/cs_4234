
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main (int argc, char *argv[])
{
  int n, nthreads = 1, i, j, seed;
  double x, sum = 0.0, priv_sum = 0.0;
  double t0, t1;
  struct drand48_data drand_buf;

  if(argc > 1) {
    nthreads = atoi(argv[1]);
  }

  n = 100000000;

  t0 = omp_get_wtime();

  #pragma omp parallel \
    num_threads(nthreads) \
    private(seed, drand_buf,\
        x, priv_sum)
  {
    
    #pragma omp for 
    for (i=0; i<n; i++){
      seed = 1202107158 + omp_get_thread_num() * 1999;
      srand48_r (seed, &drand_buf);
      drand48_r (&drand_buf, &x);

      priv_sum += x;
    }

    #pragma omp critical
    sum += priv_sum;
  }

  t1 = omp_get_wtime();
  printf("time: %7.3f\n", t1-t0);
  printf("sum: %f\n", sum); 

}
