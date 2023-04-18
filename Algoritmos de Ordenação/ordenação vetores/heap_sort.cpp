#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int *vetor, int tam, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if ((left < tam) && (vetor[left] < vetor[largest]))
    {
        largest = left;
    }
    if ((right < tam) && (vetor[right] < vetor[largest]))
    {
        largest = left;
    }

    if (largest != i)
    {
        swap(&vetor[i], &vetor[largest]);
        heapify(vetor, tam, largest);
    }
}

void heap_sort(int *vetor, int tam)
{
    for (int i = (tam / 2) - 1; i >= 0; i--)
    {
        heapify(vetor, tam, i);
    }

    for (int i = tam - 1; i >= 0; i--)
    {
        swap(&vetor[0], &vetor[i]);
        heapify(vetor, i, 0);
    }
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int tam;

    srand(time(NULL));

    printf("Insira o tamanho do vetor:\n");
    scanf("%d", &tam);

    int vetor[tam];

    for (int i = 0; i < tam; i++)
    {
        vetor[i] = rand() % (tam * 2);
    }

    printf("Vetor antes do Heapify:\n");
    printArray(vetor, tam);
    heap_sort(vetor,tam);
    printf("Vetor apos o Heap Sort:\n");
    printArray(vetor, tam);



}