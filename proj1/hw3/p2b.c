#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    int myid, numprocs, next, token;
    MPI_Status status;
    MPI_Request request;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);

    next = myid+1;

    if (myid == 0)
    {
	FILE *fp = fopen("file", "r");

	while(token != -1) {
		fscanf(fp, "%d", &token);
		if(token != -1)
			token++;
		MPI_Isend(&token, 1, MPI_INT, next, 0, MPI_COMM_WORLD, &request);
	}

	fclose(fp);
    }
    else if (myid == numprocs-1) {
	while(token != -1) {
		MPI_Irecv(&token, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD,
			 &request);
		printf("Final value %d\n", token);
	}
    } else {
	while(token != -1) {
		MPI_Irecv(&token, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD,
			 &request);
        	printf("Rank %d: got %d from rank %d.\n", myid, token, status.MPI_SOURCE);
;		if(token != -1)
        		token++;
		MPI_Isend(&token, 1, MPI_INT, next, 0, MPI_COMM_WORLD, &request);
	}
    }
    MPI_Wait(&request, &status);
    MPI_Finalize();
}
