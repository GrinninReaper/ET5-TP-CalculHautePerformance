#include <stdio.h>
#include <stdbool.h>
#include <omp.h>

//Conjecture de goldbach
/*
----------------Commentaires----------------------------
Paralléliser le trucl le plus haut dans l'appel de fonction 
(le truc que t'appelle en premier pour commmencer ton code).
Souvent dans le main.

Cours sur le scheduling:
http://jakascorner.com/blog/2016/06/omp-for-scheduling.html
static, repartition des threads faite par ordre
    à utiliser pour des opérations qui ont la meme complexité
dynamic, repartition ne suit aucune logique
    à utiliser pour des opérations dont la complexité n'est pas la meme
guided, la taille des blocs pris en compte est égale au nombre de 
   boucle non traitée divisé par le nombre de threads (pas utiliser dans le code)
   (meme syntaxe)
    à utiliser pour un cout diminuant au fur eta à mesure de l'exécution
auto, fait automatiquement par le compilateur
    pour le jours ou t'as la flemme (pas utiliser dans le code)
    (meme syntaxe sans la taille des blocs)
*/


bool isprime(int checked){
    bool rslt = true;
    for(int i = 2; i <= checked / 2; i++) {
       if(checked % i == 0) {
          rslt = false;
          break;
       }
    }
    return rslt;
}

int goldbach(int begin){
    int count = 0;
    int first = 2;
    if(begin % 2 != 0){
        printf("The number %d isn't even \n", begin);
        return count;
    }
    for (int scd = begin - first; scd >= begin/2 ; scd--){
        if(isprime(first) && isprime(scd)){
           //printf("The number %d is equal to %d + %d\n", begin , first, scd); //TEST
            count++;
        }
        first++;
    }
    //printf("%d ",begin);
    return count;
}

int main(int argc, char * argv[]){
/*
    //UNIT TESTS
    printf("Kill Them All!\n");
    
    if(isprime(59)){
        printf("My brain is the best!\n");
    }
    else{
        printf("You suck!\n");        
    }

    //----HAPPY FLOW
    int test1 = 26;
    int rslt1 = goldbach(test1);
    

    //----UNHAPPY FLOW
    int test2 = 25;
    int rslt2 = goldbach(test2);
*/

    //MAIN APP: Code séquentiel / Parallélisation du code
    
    int numpairs[8000];
    for(int i = 0; i <= 4000; i++){
        numpairs[i] =0;
    }
    printf("The main loop kiddos!\n");
    int numThread = omp_get_num_threads();
    printf("Trying with %d threads\n" ,numThread);

/*
    printf("------------------------------------Loop for static default\n");
    #pragma omp parallel for schedule(static)
    for(int i = 4; i <= 8000; i+=2){
        printf("For %d thread number %d\n",i,omp_get_thread_num());
        numpairs[i] = goldbach(i);
    }
    printf("\n");
*/

/*
    printf("------------------------------------Loop for dynamic default\n"); 
    #pragma omp parallel for schedule(dynamic)
    for(int i = 4; i <= 8000; i+=2){
        printf("For %d thread number %d\n",i,omp_get_thread_num());
        numpairs[i] = goldbach(i);
    }
    printf("\n");
*/

    printf("------------------------------------Loop for static for bloc size 4\n");
    #pragma omp parallel for schedule(static, 4)
    for(int i = 4; i <= 8000; i+=2){
        printf("For %d thread number %d\n",i,omp_get_thread_num());
        numpairs[i] = goldbach(i);
    }
    
/*
    printf("------------------------------------Loop for dynamic for bloc size 4\n"); 
    #pragma omp parallel for schedule(dynamic, 4)
    for(int i = 4; i <= 8000; i+=2){
        printf("For %d thread number %d\n",i,omp_get_thread_num());
        numpairs[i] = goldbach(i);
    }
    printf("\n");
*/

    /*
    //APP RSLT: used only for the sequential part, verification of Goldbach
    bool rslt = true;
    for(int i = 4; i <= 8000; i+=2){
        if(numpairs[i] == 0){
            rslt = false;
            printf("Golbach is wrong for %d!\n", i);
            break;
        }
    }
    if(rslt)
        printf("Goldbach, ma man!\n");
    */
}
