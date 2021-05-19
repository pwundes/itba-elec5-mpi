
#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank, size, i, provided;
    float A[10];
    char hostname[50];

    MPI_Init_thread(&argc, &argv, MPI_THREAD_SINGLE,&provided);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        for (i=0; i<10; i++)
            A[i] = 10-i;
        for (i=1; i<size; i++)
            MPI_Send(A, 10, MPI_FLOAT, i, 0, MPI_COMM_WORLD);
    } else {
        MPI_Recv(A, 10, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    gethostname(&hostname);

    if (rank == 0)
    {
        printf("Esperando los mensajes...\n");
    } else {
    	printf("My rank %d of %d, host: %s\n", rank, size, hostname );
	printf("Here are my values for A\n");
	for (i=0; i<10; i++)
        	printf("%f ", A[i]);
	printf("\n");
    }

    MPI_Finalize();
}
