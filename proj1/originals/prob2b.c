
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main (int argc, char *argv[])
{
#define amat(I,J) a[I*n + J]
#define bmat(I,J) b[I*n + J]
#define cmat(I,J) c[I*n + J]

  int n, nthreads, i, j, k;
  double *a, *b, *c;
  double t0, t1;

  n = 1000;
  nthreads = atoi(argv[1]);
  omp_set_num_threads (nthreads);

  a = (double *) malloc (n * n * sizeof (double));
  b = (double *) malloc (n * n * sizeof (double));
  c = (double *) malloc (n * n * sizeof (double));

  t0 = omp_get_wtime();

#pragma omp parallel for private (i, j, k) 
  for (j=0; j<n; j++) 
    for (i=0; i<n; i++) 
      for (k=0; k<n; k++) 
         cmat(i,j) = cmat(i,j) + amat(i,k) * bmat(k,j);

  t1 = omp_get_wtime();
  printf("nthreads, time: %d %6.2f\n", nthreads, t1-t0);
}
