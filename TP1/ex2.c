#include <stdio.h>
#include "mpi.h"

int main(int argc, char * argv[]){
    
    //EX2
    //1_le processus k envoie le message au processus de rang k+1%world_size
    //2_le processus k recoit le message du processus de rang k-1%world_size
    //3_ a partir du processus courant
    //4_ par la réception du processus qui a commencé la circulation
    
     
    int rank, buf, world_size;
    buf = 0;
    MPI_Status status;
    MPI_Init (&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    MPI_Comm_rank( MPI_COMM_WORLD, &rank);
    buf++;
    MPI_Send(&buf, 1, MPI_INT, (rank+1)%world_size, 1, MPI_COMM_WORLD);
    printf("Sending to %d\n", (rank+1)%world_size);
    MPI_Recv(&buf, 1, MPI_INT, (rank-1)%(world_size), 1, MPI_COMM_WORLD, &status);
    printf("Receiving from %d\n", (rank-1)%world_size);
    MPI_Finalize();
    
    
    return 0;
}


