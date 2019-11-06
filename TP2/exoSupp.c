#include <stdio.h>
#include "mpi.h"


/*
---------------------------------Commentaires---------------------------------
Mettre mpicc à la place de gcc pour compiler
Pour run le code mpirun -np <nombreDeProcesseur> ./<nomExécutable>
*/

int avg(int list[]){
    int rslt = 0;
    for(int i = 0; i<9;i++){
        rslt += list[i];
    }
    rslt = (int) rslt/9;
    return rslt;
}

int main(int argc, char * argv[]){
    
    //printf("Kill Them All!\n");

/*
    //UNIT TEST
    int test1[9] = {1,2,3,4,5,6,7,8};
    int rslt1 = avg(test1);
    
    printf("%d\n", rslt1);
*/

    //MAIN APP
    int size_x, size_y;
    size_x = 10;
    size_y = 10;
    int picture[size_x*size_y];

    for(int x = 0; x < size_x; x++){
        for(int y = 0; y < size_y; y++){
            picture[x * y] = 0;
        }
    }   
    

    int rank, buf, world_size;
    MPI_Status status;
    MPI_Init (&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    
    //printf("The wolrd size is %d\n", world_size);
    int linesPerProc = size_y/world_size;
    
    MPI_Comm_rank( MPI_COMM_WORLD, &rank);
    
    if(rank == 0){
        //Picture in proc 0
        for(int x = 0; x < size_x; x++){
            for(int y = 0; y < size_y; y++){
                picture[x*y] = x+y;
            }
        }

        int start;
        //Send lines to deal to everyone
        int test1 = 0;
        for(int i = 1; i < world_size; i++){
            //printf("Sending to %d\n", i);
            //Calculating the start and end lines for proc i
            start = 0;
            //MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
            MPI_Send(&picture[start], size_y, MPI_INT, i, 1, MPI_COMM_WORLD);
        }
    }
    
    //Receiving the lines from 0
    if(rank != 0){
        int test1 = 0;
        //printf("Proc %d receiving from 0\n", rank);
        test1 = rank;
        //MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status * status)
        MPI_Recv(&picture[0], linesPerProc*size_y, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
    }

    if(rank == 1){
        for(int x = 0; x < size_x; x++){
            for(int y = 0; y < size_y; y++){
                printf("%d ", picture[x * y]);
            }
            printf("\n");
        }    
    }


    MPI_Finalize();
    return 0;
}
