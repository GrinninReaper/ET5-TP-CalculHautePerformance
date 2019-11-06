#include <stdio.h>
#include <omp.h>
#define OMP_NUM_THREADS 5

/*
----------------Commentaires----------------------------
Initialise rslt avec des valeurs sinon t'as des problemes de d'opérations
En openmp la boucle est automatiquement répartie parmi les threads
Pas besoin de préciser le shared variable
*/

int main(int argc, char * argv[]){

    int size = 5;
    
    int rslt[size][1];
    int A[size][size];
    int x[size][1];

    for(int i = 0; i< size; i++){
        x[i][0] = 1;
        rslt[i][0] = 0;
        for(int j =0; j< size; j++){
            A[i][j] = i+j;
        }
    }
        
    #pragma omp parallel for
    for(int i = 0; i <  size; i++){
        for(int j=0; j< size; j++){
            rslt[i][0] += A[i][j] * x[j][0];
        }
    }

    //dsplaying x
    printf("x is\n");
    printf("[");
    for(int i = 0; i<size; i++){
        printf("%d,\n", x[i][0]);
    }
    printf("]\n");

    //displaying A
    printf("A is\n");
    for(int i = 0; i<size; i++){
        printf("[");
        for(int j = 0; j<size; j++){
            printf("%d,", A[i][j]);
        }
        printf("]\n");
    }

    printf("Rslt is \n[\n");
    for(int i = 0; i<size; i++){
        printf("%d,\n", rslt[i][0]);
    }
    printf("]\n");

    return 0;
 
}
