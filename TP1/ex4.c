#include <stdio.h>
#include "mpi.h"

int main(int argc, char * argv[]){
    //EX4

    int rank, world_size;
    float local_rslt = 0;

    MPI_Status status;
    MPI_Init (&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    MPI_Comm_rank( MPI_COMM_WORLD, &rank);

    int n = 3;

    int x[n][1];
    int A[n][n];
    int rslt[n][1];
    int glbRslt[n][1];
    int tempI = 0;

    int recvLine = 0;
    
    int linePerProc = 3/world_size;
    int localStartLine = 0; //TODO
    int localFinishLine = 0; //TODO

    if(rank == 0){
        //In process 0
        printf("Process 0\n");
        //Initializing A and x
        for(int i = 0; i<n; i++){
            x[i][0] = 1;
            for(int j = 0; j<n; j++){
                A[i][j] = i+j;
            }
        }

        //displaying A
        printf("A is\n");
        for(int i = 0; i<n; i++){
            printf("[");
            for(int j = 0; j<n; j++){
                printf("%d,", A[i][j]);
            }
            printf("]\n");
        }
            

        //displaying x
        printf("x is\n");
        printf("[");
        for(int i = 0; i<n; i++){
            printf("%d,\n", x[i][0]);
        }
        printf("]\n");

        for(int i = 0; i<n; i++){
            rslt[i][0] = 0;
        }
    }

    //broadcasting x to everyone
    //printf("Broadcasting to everyone\n");3
    for(int i = 0; i < n ; i++){
        for(int j = 0; j <n; j++){
            MPI_Bcast(&A[i][j], 1, MPI_INT, 0, MPI_COMM_WORLD);
        }
    }

    for(int i = 0; i < n; i++){
        MPI_Bcast(&x[i][0], 1, MPI_INT, 0, MPI_COMM_WORLD);
    }
    
    if(rank != 0){
        localStartLine = n/(world_size-1) * (rank-1);
        localFinishLine = n/(world_size-1) * (rank);
        printf("Process %d computes from ", rank);
        printf("%d to %d \n", localStartLine, localFinishLine);

        for(int i = localStartLine; i<localFinishLine; i++){
            printf("Calculating reslt ");
            rslt[i][0] = 0;
            for(int j = 0; j<n; j++){
                rslt[i][0] += A[i][j] * x[j][0];
            }
            printf("%d,\n", rslt[i][0]);
            MPI_Send(&rslt[i][0], 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
        }
    }


    //Faut ajouter le Recv pour le 0

    printf("For process %d rslt is \n  ", rank);
    for(int i = 0; i<n; i++){
        printf("%d,\n", rslt[i][0]);
    }
    printf("]\n");

    

    MPI_Finalize();
    return 0;


/*
    ---------------------Correction--------------------------------------
    Vérifier si size divisible par processus
    Sinon Abort
    
    Lloc = L / world_size
    
    Bcast sur x
    et Scatter sur A avec Lloc * C pour envoyer et recevoir A

    mat_vec(Alorc, x, yloc, Lloc, C); //calcul du produit local

    gather sur yloc de taille Lloc 
*/
    
}
