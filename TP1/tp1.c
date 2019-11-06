#include <stdio.h>
#include "mpi.h"

void print(float* y){
    for(int i =0; i<4; i++){
        printf("%f\n", y[i]);    
    }
}

int main(int argc, char * argv[]){
    
    //EX4
    
       
    int rank, world_size;
    int A_size;
    int sub_size;

    float * A;
    float * subA;
    float local_y[4];
    float global_y[4];
    MPI_Status status;
    MPI_Init (&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    MPI_Comm_rank( MPI_COMM_WORLD, &rank);


    if(rank == 0){
/*
        float A[16] = {1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4};
        float x[4] = {1,2,3,4};
    
        MPI_Scatter
        print(global_y);
*/
        A_size = 4;
        sub_size = A_size/world_size;
        
        A = (float *) malloc(sizeof(float)*A_size*A_size);
        for(int i = 0; i< A_size; i++){
            for(int j=0; j < A_size; j++){
                A[i*A_size+j] = i;
            }
        }
    }

    MPI_Bcast(&A_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&sub_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    MPI_Type_vector(sub_size, A_size, A_size, MPI_DOUBLE, &strip);
    MPI_Type_commit(&strip);

    subA = (float *)malloc(sizeof(float)*) 

    for(int i = rank*(4/world_size); i < (rank*+1)*(4/world_size); i++){
        local_y[i] = 0;
        for(int j = 0; j < 4; j++){
              local_y[i] += A[4*i+j] * x[j];
              printf("%f\n", local_y[i]);
        }            
    }

    for(int i = 0; i < 4; i++){
        MPI_Reduce(&local_y, &global_y, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}


