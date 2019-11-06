#include <stdio.h>
#include "mpi.h"

int main(int argc, char * argv[]){
    
    //EX1
     
    int rank, buf;
    MPI_Status status;
    MPI_Init (&argc, &argv);

    
        
    int world_size = MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if(world_size%2 == 1){
        printf("Number of processes uneven\n");
        MPI_Finalize();
    }

    MPI_Comm_rank( MPI_COMM_WORLD, &rank);
    
    if(rank%2 == 0){
        //printf ("Even\n");
        //printf("Sending\n");
        MPI_Send(&rank, 1, MPI_INT, rank+1, 1, MPI_COMM_WORLD);
        printf ("Sending to %d\n", rank+1);
        MPI_Recv(&buf, 1, MPI_INT, rank+1, 2, MPI_COMM_WORLD, &status);
        printf("Received %d\n", buf);
    }
    else if(rank%2 == 1){
        //printf ("Uneven\n");
        //printf("Receiving\n");
        MPI_Recv(&buf, 1, MPI_INT, rank-1, 1, MPI_COMM_WORLD, &status);
        printf("Received %d\n", buf);
        int msg = rank-1+10*rank;
        MPI_Send(&msg, 1, MPI_INT, rank-1, 2, MPI_COMM_WORLD);
        printf ("Sending to %d\n", rank-1);
    }
  
    MPI_Finalize();
    
    
    return 0;
}


