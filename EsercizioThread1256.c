/*
Si realizzi un programma in C e Posix sotto Linux che, con l’ausilio della libreria Pthread, 
lancia n thread per cercare il valore minimo ed il valore massimo in una matrice nxn di interi. La ricerca del minimo e 
del massimo deve essere effettuata simultaneamente su tutte le righe. Individuati i valori cercati, si provvederà a stamparli a video. 
La dimensione della matrice può essere fornita in input al programma in fase di esecuzione o da riga di comando. */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int **matrice;
pthread_mutex_t mutex;
int indice=0;

void* calcolo(){
    int capocchia,temp;
    int max,min;
    
    pthread_mutex_lock(&mutex);
    capocchia=indice;
    indice++;
    
    pthread_mutex_unlock(&mutex);
    
    for(int i=0;i<7;i++){
        temp=matrice[capocchia][i];
        if(i==0){
            min=temp;
        }
        if(temp<min){
            min=temp;
        }
        if(temp>max){
            max=temp;
        }
    }
    printf("\n\n Il massimo è : %d Il minimo è : %d\n\n",max,min);
}



int main(){
int n=7;
pthread_t tid[n];
pthread_mutex_init(&mutex,NULL);

    
matrice=(int **)malloc(n*sizeof(int *));

for(int i=0;i<7;i++){
matrice[i]=(int *)malloc(n*sizeof(int));
}

for(int m=0;m<7;m++){
       for(int n=0;n<7;n++){
        matrice[m][n]=rand()%1000;
    }
}


for(int i=0;i<7;i++){
    pthread_create(&tid[i],NULL,&calcolo,NULL);
}

for(int i=0;i<7;i++){
    pthread_join(tid[i],NULL);
}

pthread_mutex_destroy(&mutex);

}

