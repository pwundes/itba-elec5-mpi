
#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank, size, i, provided;
    int A;
    //char hostname[50];

    MPI_Init_thread(&argc, &argv, MPI_THREAD_SINGLE,&provided);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        for (i=1; i<size; i++)
            MPI_Send(&i, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
    } else {
        MPI_Recv(&A, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    //gethostname(&hostname);

    if (rank == 0)
    {
        printf("Esperando los mensajes...\n");
    } else {
    	printf("My rank %d of %d\n", rank, size );
	printf("A=");
        printf("%i ", A);
	printf("\n");
    }

    MPI_Finalize();
}
