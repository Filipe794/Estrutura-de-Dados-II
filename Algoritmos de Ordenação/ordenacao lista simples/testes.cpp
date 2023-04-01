#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct No
{
    int valor;
    struct No *proximo;
    struct No *anterior;
} No;

No *cabeca = NULL;
No *fim = NULL;
void menu()
{
    printf("1 - Adicionar elementos\n");
    printf("2 - Imprimir a lista\n");
    printf("3 - Ordenar por Selection Sort\n");
    printf("4 - Ordenar por Insertion Sort\n");
    printf("5 - Ordenar por Bubble Sort\n");
    printf("0 - Sair\n");
}
void imprimir()
{
    No *inicio = cabeca;
    while (inicio != NULL)
    {
        printf("%d ->  ", inicio->valor);
        inicio = inicio->proximo;
    }
    printf("NULL");
    printf("\n\n");
}
void inserir(int valor)
{
    No *Novo = new No;
    if (cabeca == NULL)
    {
        Novo->proximo = NULL;
        Novo->anterior = NULL;
        Novo->valor = valor;
        cabeca = Novo;
        fim = Novo;
        return;
    }
    Novo->valor = valor;
    Novo->proximo = cabeca;
    Novo->anterior = NULL;
    cabeca->anterior = Novo;
    cabeca = Novo;
}
void imprimir_inverso()
{
    No *aux = fim;
    while (aux != NULL)
    {
        printf("%d ->  ", aux->valor);
        aux = aux->anterior;
    }
    printf("NULL");
    printf("\n\n");
}
void troca_posicao(No *elem1, No *elem2)
{
    if (cabeca == NULL || elem1 == NULL || elem2 == NULL)
    {
        return;
    }

    if (elem2 == fim)
        fim = elem1;

    if (cabeca == elem1)
    {
        cabeca = elem2;
    }
    else if (cabeca == elem2)
    {
        cabeca = elem1;
    }

    if (elem1->anterior != NULL)
    {
        elem1->anterior->proximo = elem2;
    }

    if (elem2->anterior != NULL)
    {
        elem2->anterior->proximo = elem1;
    }

    No *temp = elem1->anterior;
    elem1->anterior = elem2->anterior;
    elem2->anterior = temp;

    temp = elem1->proximo;
    elem1->proximo = elem2->proximo;
    elem2->proximo = temp;

    if (elem1->proximo != NULL)
    {
        elem1->proximo->anterior = elem1;
    }

    if (elem2->proximo != NULL)
    {
        elem2->proximo->anterior = elem2;
    }
}
void selection_sort()
{
    if (cabeca == NULL || cabeca->proximo == NULL)
        return;

    No *menor, *inserir = cabeca;
    No *aux = menor->proximo;

    while (inserir->proximo != NULL)
    {
        menor = inserir;
        aux = inserir->proximo;

        while (aux != NULL)
        {
            if (menor->valor > aux->valor)
            {
                menor = aux;
            }
            aux = aux->proximo;
        }
        if (menor != inserir)
        {
            troca_posicao(inserir, menor);
            inserir = menor;
        }
        inserir = inserir->proximo;
    }
}
void insertion_sort()
{
    if (cabeca == NULL || cabeca->proximo == NULL)
        return;

    No *troca = cabeca->proximo;
    No *aux = cabeca;
    No *proximo = troca->proximo;

    while (troca != NULL)
    {
        while (aux != troca)
        {
            if (troca->valor < aux->valor)
            {
                troca_posicao(troca, aux);
                break;
            }
            aux = aux->proximo;
        }
        troca = proximo;
        aux = cabeca;
        if (troca != NULL)
            proximo = troca->proximo;
    }
}
void bubble_sort()
{
    int cont_troca;
    No *aux = NULL;
    No *ultimo = NULL;
    if (cabeca == NULL || cabeca->proximo == NULL)
        return;
    do
    {
        cont_troca = 0;
        aux = cabeca;
        while (aux->proximo != ultimo)
        {
            if (aux->proximo->valor < aux->valor)
            {
                troca_posicao(aux, aux->proximo);
                cont_troca = 1;
            }
            else
            {
                aux = aux->proximo;
            }
        }
        ultimo = aux;
    } while (cont_troca != 0);
}
int main()
{
    int opcao;
    do
    {
        menu();
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            srand(time(NULL));
            int num;
            for (int i = 0; i < 10; i++)
            {
                num = rand() % 8;
                inserir(num);
            }
            break;
        case 2:
            printf("a partir da cabeca\n");
            imprimir();
            printf("a partir do fim\n");
            imprimir_inverso();
            break;
        case 3:
            selection_sort();
            break;
        case 4:
            insertion_sort();
            break;
        case 5:
            bubble_sort();
            break;
        case 0:
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
    return 0;
}
