#include <stdio.h>
#include <omp.h>
#define OMP_NUM_THREADS 20


/*
----------------Commentaires----------------------------
Syntaxe pour faire des reduce et affecter le nombre de threads en openmp
*/

float f(float x){
    return 4.0/(1+x*x);
}

int main(int argc, char * argv[]){

    float rslt = 0.0f;

    float s = 1.0/OMP_NUM_THREADS;
    
    for(int i = 0; i< OMP_NUM_THREADS; i++){
        

        omp_set_num_threads(i);
        
        rslt = 0.0f;
        double start = omp_get_wtime();
        
        #pragma omp parallel for reduction(+:rslt)
        for (i=0; i < OMP_NUM_THREADS; i++) {
            rslt += s*((f(i*s) + f((i+1)*s))/2);
        }
    }

    printf("Pi is %f\n", rslt);  

    return 0;

}
