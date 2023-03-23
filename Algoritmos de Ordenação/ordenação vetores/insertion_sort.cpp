#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void move(int *vetor, int start, int end)
{
    for (int p = end; p < start; p--)
    {
        vetor[p] = vetor[p - 1];
    }
}

void insertion_sort(int *vetor, int tam)
{
    for (int i = 1; i < tam; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (vetor[i] <= vetor[j])
            {
                int temp = vetor[i];
                move(vetor,j,i);
                vetor[j] = temp;
                break;
            }
        }
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

    for (int i = 0; i < tam; i++){
        printf("%d ->", vetor[i]);
    }
    printf("\n");
    
    insertion_sort(vetor,tam);

    for (int i = 0; i < tam; i++){
        printf("%d -> ", vetor[i]);
    }
}