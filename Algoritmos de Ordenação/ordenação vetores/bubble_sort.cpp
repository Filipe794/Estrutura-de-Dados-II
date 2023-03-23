//  int n = sizeof(arr) / sizeof(arr[0]);

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// int antes = clock();
// // bubble_sort();
// int depois = clock();
// float diferenca = (depois-antes)/CLOCKS_PER_SEC;

void bubble_sort(int *vetor, int tam){
     for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam - 1; j++){
            if (vetor[j] > vetor[j + 1]){
                int aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

void bubble_sort_otm(int *vetor, int tam){
    int cont_aux;
    for (int i = 1; i < tam; i++){
        cont_aux=0;
        for (int j = 0; j < tam - i; j++){
            if (vetor[j] > vetor[j + 1]){
                int aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
                cont_aux++;
            }
        }
        if(cont_aux==0) return;
    }
}

int main(){
    int tam;
    printf("Insira o tamanho do vetor");
    scanf("%d", &tam);
    int vetor[tam];

    srand(time(NULL));
    for (int i = 0; i < tam; i++){
        vetor[i] = rand() % 10;
    }

    // for (int i = 0; i < tam; i++){
    //     printf("%d ->", vetor[i]);
    // }
    // printf("\n");
   
    // bubble_sort(vetor,tam);
    bubble_sort_otm(vetor,tam);

    // for (int i = 0; i < tam; i++){
    //     printf("%d -> ", vetor[i]);
    // }
}