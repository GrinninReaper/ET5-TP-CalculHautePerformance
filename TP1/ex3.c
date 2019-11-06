#include <stdio.h>
#include "mpi.h"

float f(float x){
    return 4.0/(1+x*x);
}

int main(int argc, char * argv[]){
    
    //EX3
    
     
    int rank, world_size;
    float local_rslt = 0;
    float glbl_rslt = 0;
    MPI_Status status;
    MPI_Init (&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    MPI_Comm_rank( MPI_COMM_WORLD, &rank);

    float s = 1.0/world_size;

    local_rslt += s*((f(rank*s) + f((rank+1)*s))/2);

    MPI_Reduce(&local_rslt, &glbl_rslt, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0){
        printf("Pi is %f\n", glbl_rslt);    
    }
    
    MPI_Finalize();
    return 0;

/*
    -----------Correction----------------------------------------------------------
    int rank, world_size;
    int i, n, r start, end;
    start = rank * n - + MIN(rank, r);
    end = start + n -1;
    if(rank < r){
        end++;
    }

    printf("processus %d : dtart = %d | end = %d\n", rank, start, end);
    ts = MPI_Wtime();
    tmp = 0.0;
    for(i = start; i< end; i++){
        tmp += (f(double)i/N) + f((i+1.0)/N) /(2*N);    
    }
    
    //MPI_Reduce ensuite avec le résulatat sur le processeur 0
*/
}


