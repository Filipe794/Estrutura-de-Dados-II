#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void selection_sort(int *vetor, int tam){
    int pos;
     for (int i = 0; i < tam; i++){
        pos = i;
        for (int j = i+1; j < tam; j++){
            if (vetor[j] < vetor[pos]){
                pos=j;
            }
        }
        int aux = vetor[i];
        vetor[i] = vetor[pos];
        vetor[pos] = aux;
    }
}


// embaralhar elementos: sortear um numero e trocar com outro numero sorteado

int main(){
    int tam;

    printf("Insira o tamanho do vetor");
    scanf("%d", &tam);
    
    int vetor[tam];

    srand(time(NULL));

    for (int i = 0; i < tam; i++){
        vetor[i] = rand() % 10;
    }

    for (int i = 0; i < tam; i++){
        printf("%d ->", vetor[i]);
    }
    printf("\n");
    
    selection_sort(vetor,tam);

    for (int i = 0; i < tam; i++){
        printf("%d -> ", vetor[i]);
    }
}